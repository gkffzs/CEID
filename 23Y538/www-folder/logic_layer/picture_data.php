<?php
	include("lock.php");
	include("../database_layer/db_functions.php");
	db_connect();
	
	// Δεδομένα της φωτογραφίας που παίρνονται απο την φόρμα.
	$form_title = $_POST["title"];
	$form_description = $_POST["description"];
	$form_publication = $_POST["publication"];
	$form_geolocation = $_POST["geolocation"];
	$form_lat=$_POST["lat"];
	$form_lng=$_POST["lng"];
	$form_tags = $_POST["tags"];
	$form_name = $_SESSION['file_name'];
	$form_size = $_SESSION['picture_size'];

	// Εισάγουμε τα δεδομένα της φωτογραφίας στην βάση δεδομένων.
	db_picture_insert($form_title, $form_description, $form_publication, $form_geolocation,
										$_SESSION['login_user'], $form_name, $form_size, $form_tags, $form_lat, $form_lng);

	// Μεταφέρουμε το αρχείο της φωτογραφίας στο κατάλληλο χώρο του αλμπουμ του χρήστη (ιδιωτικό/δημόσιο).
	// Mε 0 είναι ιδιωτική και με 1 δημόσια. Η μεταφορά του αρχείου από τον προσωρινό χώρο αποθήκευσης 
	// γίνεται με την χρήση της συνάρτηση rename.
	if($form_publication==0){ 
		if(!is_dir("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/")) {
			mkdir("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/");
		}	
		rename("C:/wamp/www/tmp/$form_name", 
				"C:/wamp/private_images/users_album/{$_SESSION['login_user']}/$form_name");
		}		
		else{ 
			if(!is_dir("C:/wamp/www/users_album/".$_SESSION['login_user']."/")) {
			mkdir("C:/wamp/www/users_album/".$_SESSION['login_user']);
		}
		rename("C:/wamp/www/tmp/$form_name", 
				"C:/wamp/www/users_album/{$_SESSION['login_user']}/$form_name");
	}
	
	// Σε περίπτωση που ο χρήστης δεν αποθηκεύσει την φωτογραφία ή παρουσιαστεί κάποιο άλλο πρόβλημα, οι φωτογραφίες μένουν στον
	// φάκελο tmp. Έτσι γίνεται ένας έλεγχος στα αρχεία του φακέλου. Όσες εικόνες έχουν «ζωή» μεγαλύτερη των 10 λεπτών (χρόνος που 
	// είναι και ο μέγιστος για έναν  χρήστη να βρίσκεται αδρανής στον ιστότοπο) διαγράφονται από τον φάκελο tmp.
	$dir = 'C:/wamp/www/tmp';
	$files = scandir($dir);
	$life_time = 600; // 10 λεπτά.
	
	foreach($files as $temp){
		if($temp === ".." || $temp === "."){continue;} // Ο έλεγχος αυτός γίνεται για τα κρυφά αρχεία του φακέλου, που επιθυμούμε την εξαίρεση τους
			if (time() -  filemtime($dir.'/'.$temp) >= $life_time) { // από την διαγραφή.  Υπολόγισμός «ζωής» αρχείου.
				unlink($dir.'/'.$temp);
			}
	}
	
	header("Location: ../presentation_layer/album.php");
	exit();
?>