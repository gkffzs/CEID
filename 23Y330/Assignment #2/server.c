#include <sys/types.h> /* Δήλωση βιβλιοθηκών που χρησιμοποιούνται στο πρόγραμμα. */
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

#define UNIXSTR_PATH "/tmp/unix.str" /* Καθορισμός του path που θα χρησιμοποιηθεί για την επικοινωνία μεταξύ server-client. */
#define SHM_SIZE 1000*sizeof(struct client_account)+200*sizeof(struct parking)+2 /* Προσδιορισμός του μεγέθους της κοινής μνήμης που θα χρησιμοποιηθεί σύμφωνα με τα δεδομένα της εκφώνησης της άσκησης. Από τη στιγμή που μπορούν να υπάρχουν το πολύ 1000 οδηγοί τότε για να εξυπηρετηθούν όλοι απαιτούνται τουλάχιστον 200 parking. */
#define SHM_KEY IPC_PRIVATE /* Προσδιορισμός του αριθμητικού κλειδιού για τη δημιουργία της κοινής μνήμης. */
#define LISTEN_QUEUE 5 /* Προσδιορισμός αριθμού client που μπορούν να περιμένουν για εξυπηρέτηση στο socket. */
#define SEM_NAME "os_project" /* Προσδιορισμός ονόματος του σημαφόρου που χρησιμοποιείται. */

void kill_server(); /* Δήλωση καθορισμένων συναρτήσεων που χρησιμοποιούνται για τις διάφορες επιθυμητές λειτουργίες. */
void *create_new_driver(void *);
void *make_new_reservation(void *);
void *deposit_money(void *);
void *view_driver_information(void *);
void *view_drivers_last_reservation(void *);
void *create_new_parking(void *);
void *view_parkings_last_reservation(void *);

struct thread_struct{ /* Δήλωση του struct για τα thread. */
	int thread_id; /* Δήλωση μεταβλητής για την αποθήκευση του ID αριθμού του thread. */
	int thread_free; /* Δήλωση μεταβλητής για ένδειξη διαθεσιμότητας του thread ή όχι. */
};

struct parking{ /* Δήλωση του struct για τα parking. */
	char parking_name[15]; /* Δήλωση μεταβλητής για την αποθήκευση του ονόματος του parking. */
	char description[80]; /* Δήλωση μεταβλητής για την αποθήκευση της περιγραφής του parking. */
	float price; /* Δήλωση μεταβλητής για την αποθήκευση της τιμής του parking. */
	char last[40]; /* Δήλωση μεταβλητής για την αποθήκευση της οδηγού που έκανε την τελευταία κράτηση. */
	int empty; /* Δήλωση μεταβλητής για την αποθήκευση του αριθμού των οδηγών που έχουν κάνει κράτηση στο parking. */
	int free; /* Δήλωση μεταβλητής που δείχνει τον αριθμό των ελεύθερων θέσεων στο parking. */
} parking[200];	/* Δήλωση ενός πίνακα από parking με 200 κελιά. */

struct client_account{ /* Δήλωση του struct για τις οδηγούς. */
	char name[40]; /* Δήλωση μεταβλητής για την αποθήκευση του ονόματος της οδηγού. */
	float money; /* Δήλωση μεταβλητής για την αποθήκευση των χρημάτων που διαθέτει η οδηγός. */
	char reservations[15]; /* Δήλωση μεταβλητής για την αποθήκευση του ονόματος parking στο οποίο έγινε από την οδηγό η τελευταία κράτηση. */
	int parked; /* Δήλωση μεταβλητής που χρησιμοποιείται για να διευκρινιστεί αν η οδηγός έχει κάνει ήδη κράτηση ή όχι. */
	int counter_park; /* Δήλωση μεταβλητής για την αποθήκευση του αριθμού των υπάρχοντων parking, ώστε να πραγματοποιείται η εκτύπωση τους πριν μια κράτηση και να διευκολύνεται η επιλογή μεταξύ αυτών. */
} client[1000]; /* Δήλωση ενός πίνακα από client_account με 1000 κελιά. */

char tempname[40]; /* Δήλωση μεταβλητής για την προσωρινή αποθήκευση ονόματος οδηγού. */
float tempmoney; /* Δήλωση μεταβλητής για την προσωρινή αποθήκευση του ποσού των χρημάτων. */
int shm_id, sock_des, pid, error;
int count; /* Δήλωση δείκτη που θα δείχνει στον αριθμό των λογαριασμών, που θα βρίσκεται στην πρώτη θέση της κοινής μνήμης. */
struct client_account *d_account; /* Δήλωση δείκτη στην πρώτη θέση της κοινής μνήμης όπου θα αποθηκεύονται οι οδηγοί. */
struct parking *p_account; /* Δήλωση δείκτη στην πρώτη θέση της κοινής μνήμης όπου θα αποθηκεύονται τα parking. */
struct sockaddr sock_add, fsock_add;
int new_handle;
socklen_t cln_len;
pthread_mutex_t mymutex;
int operation; /* Δήλωση μεταβλητής για τη διευκόλυνση επιλογής μεταξύ των λειτουργιών. */
int length; /* Δήλωση μεταβλητής για την αποθήκευση του μήκους που θα αναγνώσει η συνάρτηση bind(). */
int name_found; /* Δήλωση μεταβλητών που λειτουργούν ως flags σε ελέγχους. */
int name_found2;
int i; /* Δήλωση μετρητών που χρησιμοποιούνται σε βρόχους. */
int i2;
int count=0;
int count2=0;
int array_position(struct thread_struct *, const int);

int main(){ /* Κύριο πρόγραμμα. */
	pthread_t thread[1000]; /* Δήλωση πίνακα thread. */
	struct thread_struct thread_array[1000]; /* Δήλωση πίνακα που ελέγχει όλα τα thread. */
	pthread_mutex_init(&mymutex, NULL); /* Αρχικοποίηση του mutex. */
	int t=0; /* Δήλωση βοηθητικής μεταβλητής για αναζητήσεις. */
	int return_value; /* Δήλωση μεταβλητής για την επιστρεφόμενη τιμή από τις δημιουργίες νέων thread και όχι μόνο. */
	unsigned thread_count_id=1;

	if((sock_des=socket(AF_UNIX, SOCK_STREAM, 0))<0){ /* Δημιουργία του socket επικοινωνίας και έλεγχος αποτυχίας της προσπάθειας. */
		perror("Failure to create a socket.\n"); /* Εκτύπωση σφάλματος σε περίπτωση αποτυχίας δημιουργίας του socket επικοινωνίας. */
		exit(1); /* Έξοδος από το πρόγραμμα. */
	}
	
	for(i=0; i<1000; i++)
		thread_array[i].thread_free=0; /* Άλλαζουμε την τιμή της μεταβλητής thread_free που δείχνει πως όλα τα thread είναι έτοιμα για να δημιουργηθούν. */
	
	unlink(UNIXSTR_PATH); /* Προληπτική διαγραφή προηγούμενου socket. */
	bzero(&sock_add, sizeof(sock_add)); /* Αντίστοιχος μηδενισμός της διεύθυνσης του socket. */
	sock_add.sa_family=AF_UNIX; /* Προσδιορισμός πρωτοκόλλου για επικοινωνία server-client στο ίδιο σύστημα. */
	strcpy(sock_add.sa_data, UNIXSTR_PATH); /* Προσδιορισμός του path που θα χρησιμοποιηθεί για τη σύνδεση. */

	length=sizeof(sock_add.sa_family)+sizeof(sock_add.sa_data); /* Προσδιορισμός μήκους του string που θα διαβάσει στη συνέχεια η συνάρτηση bind(). */

	signal(SIGINT, kill_server); /* Ρύθμιση και προσδιορισμός του signal handler για το κλείσιμο της διεργασίας και αποδέσμευση της κοινής μνήμης με τον συνδυασμό CTRL+C. */

	printf("The server has been successfully initialized.\n"); /* Εκτύπωση μηνύματος επιτυχούς έναρξης του server. */

	if(bind(sock_des, &sock_add, length)<0){ /* Δέσμευση (bind) του socket επικοινωνίας που δημιουργήθηκε. */
		perror("Failure to bind the socket.\n"); /* Εκτύπωση σφάλματος σε περίπτωση αποτυχίας δέσμευσης του socket επικοινωνίας που δημιουργήθηκε. */
		exit(1); /* Έξοδος από το πρόγραμμα. */
	}

	if(listen(sock_des, LISTEN_QUEUE)<0){ /* Καθορισμός του socket επικοινωνίας ως listening socket. */
		perror("Failure to listen for clients.\n"); /* Εκτύπωση σφάλματος σε περίπτωση αποτυχίας καθορισμού του socket επικοινωνίας ως listening socket. */
		exit(1); /* Έξοδος από το πρόγραμμα. */
	}

	while(1){ /* Βρόχος για την εξυπηρέτηση των client. */
		if((new_handle=accept(sock_des, &fsock_add, &cln_len))<0){ /* Αποδοχή επικοινωνίας μέσω του socket επικοινωνίας new_handle και μερικός έλεγχος επιτυχίας της προσπάθειας. */
			perror("Failure to accept a new client.\n"); /* Εκτύπωση μηνύματος αποτυχίας αποδοχής αίτησης σύνδεσης από client. */
			exit(1); /* Έξοδος από το πρόγραμμα. */
		}

		pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */
		t=array_position(thread_array, 1000); /* Εντοπίζουμε ποιο thread έχει την πρώτη ελεύθερη θέση στον πίνακα των thread. */
		thread_array[t].thread_id=thread_count_id++; /* Κατάληψη διαθέσιμης θέσης από το thread και αύξηση του μετρητή για το επόμενο thread που θα δημιουργηθεί.*/

		pthread_mutex_unlock(&mymutex); /* Ξεκλείδωμα του mutex. */ 

		if(read(new_handle, &operation, sizeof(operation))<0){ /* Ανάγνωση της επιλεγμένης λειτουργίας από τον client και μερικός έλεγχος για την επιτυχία της ανάγνωσης. */
			perror("Failure to read the selected operation from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης της λειτουργίας. */
			exit(1); /* Έξοδος από το πρόγραμμα. */
		}

		switch(operation){ /* Δομή επιλογής switch για τον προσδιορισμό της επιθυμητής λειτουργίας. */
			case 1: /* Περίπτωση δημιουργίας νέου λογαριασμού οδηγού. */
				if(count<1000){ /* Έλεγχος του αριθμού των υπάρχοντων οδηγών. */
					return_value=pthread_create(&thread[t], NULL, create_new_driver, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας δημιουργίας νέου λογαριασμού οδηγού. */
					pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				}
				else /* Αλλιώς επιστροφή σφάλματος. */
					return_value=1;
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */
			case 2: /* Περίπτωση πραγματοποίησης νέας κράτησης σε parking. */
				return_value=pthread_create(&thread[t], NULL, make_new_reservation, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας δημιουργίας νέας κράτησης. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */
			case 3: /* Περίπτωση εμφάνισης πληροφοριών ενός λογαριασμού. */
				return_value=pthread_create(&thread[t], NULL, view_driver_information, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας εμφάνισης των πληροφοριών ενός λογαριασμού. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */                                   
			case 4: /* Περίπτωση κατάθεσης χρημάτων σε υπάρχοντα λογαριασμό. */
				return_value=pthread_create(&thread[t], NULL, deposit_money, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας κατάθεσης χρημάτων. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */
			case 5: /* Περίπτωση δημιουργίας νέου parking. */
				return_value=pthread_create(&thread[t], NULL, create_new_parking, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας δημιουργίας νέου parking. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */ 	
			case 6: /* Περίπτωση εμφάνισης της τελευταίας κράτησης μιας οδηγού. */
				return_value=pthread_create(&thread[t], NULL, view_drivers_last_reservation, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας εμφάνισης της τελευταίας κράτησης μιας οδηγού. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */
			case 7: /* Περίπτωση εμφάνισης τελευταίας καταχώρησης στο parking. */
				return_value=pthread_create(&thread[t], NULL, view_parkings_last_reservation, &thread_array[t]); /* Δημιουργία καινούργιου thread για τη διαχείριση της λειτουργίας εμφάνισης τελευταίας καταχώρησης στο parking. */
				pthread_detach(thread[t]); /* Αποδέσμευση μνήμης μετά τον τερματισμό του thread. */
				break; /* Έξοδος από τη δομή επιλογής switch για τις επιμέρους λειτουργίες. */
			}

			if(return_value){ /* Έλεγχος για την ύπαρξη σφάλματος κατά τη δημιουργία ενός thread. */
				printf("Sorry, the program can not accept more drivers.\n"); /* Εκτύπωση μηνύματος σφάλματος. */
				exit(1); /* Έξοδος από το πρόγραμμα. */
			}
	}
}

void *create_new_driver(void *threadarg){ /* Συνάρτηση δημιουργίας νέου λογαριασμού οδηγού. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */

	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */

	while(1){ /* Βρόχος αναζήτησης ονόματος οδηγού. */
		name_found=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found για τον επόμενο έλεγχο ύπαρξης του ονόματος. */

		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		for(i=0; i<count; i++){ /* Βρόχος συγκρίσεων. */
			if (!strcmp(d_account[i].name, tempname)){ /* Σύγκριση του προσωρινού ονόματος με τα αποθηκευμένα. */ 
				name_found=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found η τιμή 0. */
				break; /* Έξοδος από το βρόχο συγκρίσεων. */
			}
		}

		if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας της αποστολής της τιμής. */ 
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		if(name_found==-1) /* Αν δεν υπάρχει το όνομα. */
			break; /* Έξοδος από το βρόχο αναζήτησης. */
	}
	
	pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */ 
	d_account=(struct client_account *) realloc(d_account, sizeof(struct client_account)*(count+1)); /*Δυναμική δέσμευση για τον προσδιορισμό του δείκτη των οδηγών μία θέση μετά τη θέση του μετρητή λογαριασμών. */
	
	if(read(new_handle, &d_account[count], sizeof(struct client_account))<0){ /* Ανάγνωση των στοιχείων του λογαριασμού από τον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to read the account from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης των στοιχείων. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
	}

	d_account[count].counter_park=0; /* Μηδενίζουμε το μετρητή των parking. */
	d_account[count].parked=0; /* Αρχικοποιούμε με 0 τη μεταβλητή που δείχνει αν έχει παρκάρει κάπου η οδηγός. */
				
	if(write(new_handle, &d_account[count], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων του λογαριασμού στον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
		pthread_exit(NULL); /* Τερματισμός του thread. */	
	}

	count++; /* Αύξηση του μετρητή οδηγών. */
	pthread_mutex_unlock(&mymutex); /* Ξεκλείδωμα του mutex. */
	printf("Thread #%d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */
}

void *make_new_reservation(void *threadarg){ /* Συνάρτηση πραγματοποίησης νέας κράτησης σε parking. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */

	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */

	while(1){ /* Βρόχος εισαγωγής στοιχείων οδηγού και επιλογής parking. */
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		i=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
		name_found=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found για τον επόμενο έλεγχο ύπαρξης του ονόματος. */

		while((i<count)&&(name_found==-1)){ /* Βρόχος συγκρίσεων. */
			if(!strcmp(d_account[i].name, tempname)){ /* Σύγκριση του προσωρινού ονόματος με τα αποθηκευμένα. */ 
				name_found=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found η τιμή 0. */

				if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας της αποστολής της τιμής. */ 
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}

				if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων του λογαριασμού στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}
			}
			else /* Αν δεν είναι ίδια τα ονόματα της σύγκρισης. */
				i++; /* Αύξηση του μετρητή για να προχωρήσει. */
		}

		if(name_found==0) /* Αν υπάρχει το όνομα της οδηγού. */
			break; /* Έξοδος από τον κύριο βρόχο. */
		else{ /* Αν δεν υπάρχει. */
			if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
			}
		}
	} 
	
	if(write(new_handle, &count2, sizeof(count2))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
	}

	for(i2=0; i2<count2; i2++){ /* Βρόχος εκτύπωσης διαθέσιμων parking. */
		if(write(new_handle, &p_account[i2], sizeof(struct parking))<0){ /* Ανάγνωση των στοιχείων του parking και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the parking to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης των στοιχείων του parking. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}
	}

	while(1){ /* Βρόχος αναζήτησης του ονόματος του parking. */
		name_found2=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found2 για τον επόμενο έλεγχο ύπαρξης του ονόματος. */
		i2=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
					
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
			}

		while((i2<count2)&&(name_found2==-1)){ /* Βρόχος συγκρίσεων. */
			if(!strcmp(p_account[i2].parking_name, tempname)) /* Σύγκριση του προσωρινού ονόματος με τα αποθηκευμένα. */     
				name_found2=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found2 η τιμή 0. */
			else /* Αν δεν είναι ίδια τα ονόματα της σύγκρισης. */
				i2++; /* Αύξηση του μετρητή για να προχωρήσει. */
		}

		if(write(new_handle, &name_found2, sizeof(name_found2))<0){ /* Αποστολή της τιμής της name_found2 στον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the parking confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}
					
		if(name_found2==0) /* Αν το όνομα του parking υπάρχει. */
			break; /* Έξοδος από το βρόχο αναζήτησης. */	
	}

	if(write(new_handle, &p_account[i2], sizeof(struct parking))<0){ /* Αποστολή των στοιχείων του parking στον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to write the parking to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
		}

	if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων του λογαριασμού στον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
		}

	pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */

	if((d_account[i].money>=p_account[i2].price)&&(p_account[i2].free>=1)&&(d_account[i].parked==0)){
		strcpy(p_account[i2].last , d_account[i].name); /* Αποθήκευση ονόματος οδηγού για την εμφάνιση του ως τελευταία κράτηση πελάτη που πραγματοποιήθηκε στο parking. */
		strcpy(d_account[i].reservations, p_account[i2].parking_name); /* Αποθήκευση ονόματος parking για την εμφάνιση του ως τελευταίο parking στο οποίο έκανε κράτηση η οδηγός. */					

		if(p_account[i2].empty>=0) /* Έλεγχος για την ορθότητα της τιμής του μετρητή. */
			p_account[i2].empty++; /* Αύξηση του μετρητή των οδηγών που έχουν κάνει κράτηση κατά ένα. */

		if(d_account[i].counter_park>=0) /* Έλεγχος για την ορθότητα της τιμής του μετρητή. */
			d_account[i].counter_park++; /* Αύξηση του μετρητή των κρατήσεων της οδηγού κατά ένα. */

		d_account[i].parked=1; /* Ένδειξη ότι πλέον έχει παρκάρει κάπου η οδηγός. */
		p_account[i2].free--; /* Μειώνουμε τις ελεύθερες θέσεις του parking κατά μία. */
	}

	pthread_mutex_unlock(&mymutex); /* Ξεκλείδωμα του mutex. */

	sleep(120); /* Ο server (child process) τίθεται σε κατάσταση ύπνου για 2 λεπτά, όσο επιτρέπεται να διαρκεί η κράτηση μιας οδηγού σε μια θέση parking. */

	pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */

	if((p_account[i2].free>=0)&&(p_account[i2].free<5)&&(d_account[i].parked==1)){ /* Έλεγχος ικανοποίησης πολλαπλών συνθηκών, αν υπάρχουν θέσεις στο parking κι αν έχει παρκάρει η οδηγός. */
		d_account[i].money-=p_account[i2].price; /* Αφαίρεση του κόστους κράτησης του parking από τα χρήματα της οδηγού. */
		d_account[i].parked=0; /* Ένδειξη ότι η οδηγός δεν έχει παρκάρει κάπου τώρα. */
		p_account[i2].free++; /* Αυξάνουμε πάλι τις ελεύθερες θέσεις του parking κατά μία. */
	}

	pthread_mutex_unlock(&mymutex); /* Ξεκλείδωμα του mutex. */
	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */
}


void *view_driver_information(void *threadarg){ /* Συνάρτηση εμφάνισης πληροφοριών ενός λογαριασμού. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */

	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */

	while(1){ /* Βρόχος εισαγωγής ονόματος οδηγού. */
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		i=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
		name_found=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found για τον επόμενο έλεγχο ύπαρξης του ονόματος. */

		while((i<count)&&(name_found==-1)){ /* Βρόχος αναζήτησης του ονόματος. */
			if(!strcmp(d_account[i].name, tempname)){ /* Σύγκριση του προσωρινού ονόματος με τα αποθηκευμένα. */
				name_found=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found η τιμή 0. */

				if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}

				if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων της οδηγού στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων της οδηγού. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}   
			}
			else /* Αν δε βρεθεί το όνομα από τη σύγκριση. */
				i++; /* Αύξηση του μετρητή για να προχωρήσει παρακάτω. */
		}

		if(name_found==0) /* Αν υπάρχει το όνομα. */
			break; /* Έξοδος από το βρόχο αναζήτησης. */
		else{ /* Αν δεν υπάρχει το όνομα. */
			if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
				perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
				pthread_exit(NULL); /* Τερματισμός του thread. */
			}
		}
	}

	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */
}

void *deposit_money(void *threadarg){ /* Συνάρτηση κατάθεσης χρημάτων σε υπάρχοντα λογαριασμό. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */

	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */
  
	while(1){ /* Βρόχος εισαγωγής ονόματος οδηγού. */
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		i=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
		name_found=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found για τον επόμενο έλεγχο ύπαρξης του ονόματος. */

		while((i<count)&&(name_found==-1)){ /* Βρόχος αναζήτησης του ονόματος. */
			if(!strcmp(d_account[i].name, tempname)){ /* Σύγκριση του προσωρινού ονόματος parking με τα αποθηκευμένα. */
				name_found=0; /* Αν βρεθεί υπάρχουσα καταχώρηση parking, τότε εκχωρείται στη name_found2 η τιμή 0. */

				if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
					pthread_exit(NULL); /* Τερματισμός του thread. */ 
				}

				if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων της οδηγού στον client και μερικός έλεγχος επιτυχίας. */
					perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων της οδηγού. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}
			}
			else /* Αν δε βρεθεί το όνομα από τη σύγκριση. */
				i++; /* Αύξηση του μετρητή για να προχωρήσει παρακάτω. */
		}

		if(name_found==0) /* Αν υπάρχει το όνομα. */
			break; /* Έξοδος από το βρόχο αναζήτησης. */
		else{ /* Αν δεν υπάρχει το όνομα. */
			if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client. και μερικός έλεγχος επιτυχίας. */
				perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
				pthread_exit(NULL); /* Τερματισμός του thread. */ 
			}
		}
	}

	if(read(new_handle, &tempmoney, sizeof(tempmoney))<0){ /* Ανάγνωση του ποσού χρημάτων από τον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to read the money from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ποσού. */
		exit(1); /* Έξοδος από το πρόγραμμα. */
	}

	pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */
	d_account[i].money+=tempmoney; /* Προσθήκη του επιθυμητού ποσού σ' αυτό του λογαριασμού. */
	pthread_mutex_unlock(&mymutex); /* Ξεκλείδωμα του mutex. */

	if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){
		perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων της οδηγού. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
	}

	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL);
}

void *create_new_parking(void *threadarg){ /* Συνάρτηση δημιουργίας νέου parking. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */
  
	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */

	while(1){ /* Βρόχος καθορισμού ονόματος του parking. */
		name_found2=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found2 για τον επόμενο έλεγχο ύπαρξης parking. */

		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος του parking από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος του parking. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		for(i=0; i<count2; i++){ /* Βρόχος αναζήτησης ονόματος. */
			if (!strcmp(p_account[i].parking_name, tempname)){ /* Σύγκριση του προσωρινού ονόματος parking με τα αποθηκευμένα. */      
				name_found2=0; /* Αν βρεθεί υπάρχουσα καταχώρηση parking, τότε εκχωρείται στη name_found2 η τιμή 0. */
				break; /* Έξοδος από το βρόχο αναζήτησης. */
			}
		}

		if(write(new_handle, &name_found2, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found2 στον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the parking confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		if(name_found2==-1) /* Αν δεν υπάρχει το parking. */
			break; /* Έξοδος από το βρόχο καθορισμού. */
	}
	
	pthread_mutex_lock(&mymutex); /* Κλείδωμα του mutex για να αλλάξουμε δεδομένα στη μνήμη. */
	p_account=(struct parking *) realloc(p_account, sizeof(struct parking)*(count2+1)); /* Προσδιορισμός του δείκτη των parking 1001 θέσεις μετά τη θέση του μετρητή λογαριασμών. */
	
	if(read(new_handle, &p_account[count2], sizeof(struct parking))<0){ /* Ανάγνωση των στοιχείων του parking από τον client και μερικός έλεγχος επιτυχίας. */
		perror("Failure to read the parking from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης των στοιχείων του parking. */
		pthread_exit(NULL); /* Τερματισμός του thread. */
	}

	p_account[count2].free=5; /* Προσδιορισμός ελεύθερων θέσεων parking. */
	p_account[count2].empty=0; /* Προσδιορισμός μη ύπαρξης κρατήσεων στο parking. */

				
	if(write(new_handle, &p_account[count2], sizeof(struct parking))<0){ /* Αποστολή των στοιχείων του parking και μερικός έλεγχος επιτυχίας. */
		perror("Failure to write the parking to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων του parking. */
		pthread_exit(NULL); /* Τερματισμός του thread. */	
	}

	count2++; /* Αύξηση του μετρητή των πάρκινγκ. */
	pthread_mutex_unlock( &mymutex ); /* Ξεκλείδωμα του mutex. */
	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */
}

void *view_drivers_last_reservation(void *threadarg){ /* Συνάρτηση εμφάνισης της τελευταίας κράτησης μιας οδηγού. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */
	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */
  
	while(1){ /* Βρόχος εισαγωγής και ελέγχου ονόματος. */
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		i=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
		name_found=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found για τον επόμενο έλεγχο ύπαρξης του ονόματος. */

		while((i<count)&&(name_found==-1)){ /* Βρόχος αναζήτησης του ονόματος. */
			if(!strcmp(d_account[i].name, tempname)){ /* Σύγκριση του προσωρινού ονόματος με τα αποθηκευμένα. */
				name_found=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found η τιμή 0. */
				if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος. */
					perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}
		
				if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων της οδηγού και μερικός έλεγχος επιτυχίας της. */
					perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων του λογαριασμού. */
					pthread_exit(NULL); /* Τερματισμός του thread. */
				}
			}
			else /* Αν δεν υπάρχει αποθηκευμένο το όνομα. */
				i++; /* Αύξηση μετρητή για να προχωρήσει στην επόμενη καταχώρηση. */
		}

		if(name_found==0) /* Έλεγχος για το αν υπάρχει ή όχι το όνομα και αντίστοιχες ενέργειες. */
			break; /* Έξοδος από το βρόχο εισαγωγής και ελέγχου ονόματος. */
		else{/* Αν δεν υπάρχει το όνομα. */
			if(write(new_handle, &name_found, sizeof(name_found))<0){ /* Αποστολή της τιμής της name_found στον client και μερικός έλεγχος επιτυχίας της. */
				perror("Failure to write the name confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της name_found. */
				pthread_exit(NULL); /* Τερματισμός του thread. */ 
			}
		}
	}

	if(d_account[i].counter_park==0){ /* Έλεγχος για το αν υπάρχουν parking. */
		if(write(new_handle,&d_account[i].counter_park, sizeof(d_account[i].counter_park))<0){ /* Αποστολή του μετρητή parking και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the parking counter to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής του μετρητή parking. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}
	}
	else{ /* Αν υπάρχουν parking. */
		if(write(new_handle,&d_account[i].counter_park, sizeof(d_account[i].counter_park))<0){ /* Αποστολή του μετρητή parking και μερικός έλεγχος επιτυχίας. */
			perror("Failure to write the parking counter to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής του μετρητή parking. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		if(write(new_handle, &d_account[i], sizeof(struct client_account))<0){ /* Αποστολή των στοιχείων της οδηγού στον client και μερικός έλεγχος επιτυχίας της προσπάθειας. */
			perror("Failure to write the account to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}
	}

	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */
}

void *view_parkings_last_reservation(void *threadarg){ /* Συνάρτηση εμφάνισης τελευταίας καταχώρησης στο parking. */
	struct thread_struct *my_thread; /* Δήλωση δείκτη τύπου thread_struct για εκχώρηση του ορίσματος της συνάρτησης. */

	my_thread=(struct thread_struct *) threadarg; /* H my_thread είναι ένας δείκτης στα structs που περιέχουν τα στοιχεία των thread. */ 
  
	while(1){
		i2=0; /* Αρχικοποίηση της μεταβλητής για τη χρήση της στον ακόλουθο βρόχο. */ 
		name_found2=-1; /* Εκχώρηση τιμής -1 στη μεταβλητή name_found2 για τον επόμενο έλεγχο ύπαρξης του parking. */
		if(read(new_handle, tempname, sizeof(tempname))<0){ /* Ανάγνωση του ονόματος του parking από τον client και μερικός έλεγχος επιτυχίας. */
			perror("Failure to read the name from the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας ανάγνωσης του ονόματος. */ 
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		while((i2<count2)&&(name_found2==-1)){ /* Βρόχος αναζήτησης του ονόματος του parking. */
			if (!strcmp(p_account[i2].parking_name, tempname)) /* Σύγκριση του προσωρινού ονόματος parking με τα αποθηκευμένα. */     
				name_found2=0; /* Αν βρεθεί υπάρχουσα καταχώρηση, τότε εκχωρείται στη name_found2 η τιμή 0. */					
			else
				i2++; /* Αύξηση μετρητή για να προχωρήσει στην επόμενη καταχώρηση parking. */
		}

		if(write(new_handle, &name_found2, sizeof(name_found2))<0){ /* Αποστολή της τιμής της name_found2 στον client και μερικός έλεγχος επιτυχίας της προσπάθειας. */
			perror("Failure to write the parking confirmation to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής της τιμής. */
			pthread_exit(NULL); /* Τερματισμός του thread. */
		}

		if(name_found2==0) /* Έλεγχος αν το όνομα parking υπάρχει. */
			break; /* Έξοδος από το βρόχο αναζήτησης. */	
	}
	
	if(write(new_handle, &p_account[i2], sizeof(struct parking))<0){ /* Αποστολή στον client των στοιχείων του parking που ζητήθηκε και μερικός έλεγχος επιτυχίας. */
		perror("Failure to write the parking to the client.\n"); /* Εκτύπωση μηνύματος σφάλματος σε περίπτωση αποτυχίας αποστολής των στοιχείων. */
		pthread_exit(NULL); /* Τερματισμός του thread. */	
	}

	printf("Thread %d was terminated.\n", my_thread->thread_id); /* Eκτύπωση μηνύματος τερματισμού του thread. */
	my_thread->thread_free=0; /* Αλλάζουμε την τιμή της thread_free σε 0 για να μπορούμε να δημιουργήσουμε νέο thread. */
	pthread_exit(NULL); /* Τερματισμός του thread. */	
}

void kill_server(){ /* Συνάρτηση για τον τερματισμό του server. */
	pthread_mutex_destroy(&mymutex);/*αποδέσμευση mutex*/
	free(d_account);/* Αποδέσμευση της μνήμης που χρησιμοποιείται από τα structs των οδηγών. */
	free(p_account);/* Αποδέσμευση της μνήμης που χρησιμοποιείται από τα structs των parking. */
	close(sock_des); /* Κλείσιμο των ανοικτών sockets. */
	close(new_handle); /* Κλείσιμο του socket επικοινωνίας. */
	printf("\nThe server was terminated.\n"); /* Εκτύπωση μηνυματος τερματισμού του server. */
	exit(0); /* Έξοδος από το πρόγραμμα. */
}

int array_position(struct thread_struct *thread_array, const int array_size){ /* Συνάρτηση για αναζήτηση του πρώτου διαθέσιμου thread. */
	int i; /* Δήλωση μεταβλητής για την αποθήκευση του αριθμού του κελιού. */

	for(i=0; i<array_size; i++){ /* Βρόχος αναζήτησης. */
		if(thread_array[i].thread_free==0){ /* Έλεγχος αν το thread χρησιμοποιείται. */
			thread_array[i].thread_free=1; /* Εκχώρηση της τιμής 1 στη thread_free καθώς είναι πλέον δεσμευμένο το thread. */
			return i; /* Επιστροφή του αριθμού κελιού όπου βρίσκεται το πρώτο διαθέσιμο thread. */
			break; /* Έξοδος από το βρόχο. */
		}
	}

	return -1; /* Σε περίπτωση που δε βρει κάποιο ελεύθερο, τότε επιστρέφει την τιμή -1. */
}
