<?php
	include("lock.php");
	include("../database_layer/db_functions.php");
	db_connect();
	
	// Δεδομένα που στέλνονται απο την φόρμα.
	$form_id=$_GET['id'];
	$form_title = $_POST["title"];
	$form_description = $_POST["description"];
	$form_publication = $_POST["publication"];
	$form_geolocation = $_POST["geolocation"];
	$form_tags = $_POST["tags"];
	$form_lat = $_POST["lat"];
	$form_lng = $_POST["lng"];
	
	// Μέθοδος που ενημερώνει τα δεδομένα της φωτογραφίας.
	db_picture_update($form_title, $form_description, $form_publication, $form_geolocation,
						$_SESSION['login_user'], $form_tags, $form_id, $form_lat, $form_lng);
	
	// Επιστρέφει το όνομα του αρχείου της φωτογραφίας.
	$filename = picture_file_name ($form_id);  
	
	// Ελέγχει έαν υπάρχει το αρχείο στις δημόσιες του χρήστη.
	// Εάν έχει αλλάξει από δημόσια σε ιδιωτική (publication=0) μεταφέρει την φωτογραφία στο album του χρήστη με τις ιδιωτικές φωτογραφίες. 
	// Αντίστοιχα κάνει την αλλαγή στη περίπτωση που είναι ιδιωτική και αλλάζει σε δημόσια (publication=1).
	if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/$filename")){
		if($form_publication==0){ 
			if(!is_dir("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/")) {
				mkdir("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/");
			}
			rename("C:/wamp/www/users_album/{$_SESSION['login_user']}/$filename", 
				 "C:/wamp/private_images/users_album/{$_SESSION['login_user']}/$filename");
		}
	} else { 
		if($form_publication==1){
			rename("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/$filename",
					"C:/wamp/www/users_album/{$_SESSION['login_user']}/$filename");
		}
	}
	
	// Μήνυμα επιτυχίας.
	$_SESSION['edit_message'] = 'Η επεξεργασία των στοιχείων της εικόνας ολοκληρώθηκε με επιτυχία.';
	
	// Ανακατεύθυνση στην εικόνα που μορφοποιήθηκε.
	header("Location: ../presentation_layer/image.php?id=$form_id");
?>