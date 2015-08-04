<?php
	include("lock.php");
	include("../database_layer/db_functions.php");
	db_connect();
	
	$form_id=$_GET['id']; // Περιέχει το id της φωτογραφίας προς διαγραφή.
	
	$filename = picture_file_name ($form_id);
	
	// Ελέγχει εαν υπάρχει το αρχείο σε μία απο τις 2 τοποθεσίες (ιδιωτική/δημόσια) του album του χρήστη
	// και περνάει την διεύθυνση της στην μεταβλητή $filepath.
	if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/$filename")) {
				$filepath = "C:/wamp/www/users_album/{$_SESSION['login_user']}/$filename";
				$file_exists = 'ok';
	}elseif(file_exists("C:/wamp/private_images/users_album/{$_SESSION['login_user']}/$filename")){
			$filepath = "C:/wamp/private_images/users_album/{$_SESSION['login_user']}/$filename";
			$file_exists = 'ok';
	}
	
	// Εαν τελικά εντοπίσει την φωτογραφία, διαγράφει το αρχείο και δεδομένα του στην βάση δεδομένων.
	if(isset($file_exists)){	
		$filesize = filesize($filepath);		
		if(unlink($filepath)) { // Διεγραψε την φωτογραφια και αν διαγραφεί επιτυχώς...
			image_delete();								
			$_SESSION['delete_message'] = 'Η φωτογραφία σας διαγράφηκε με επιτυχία.' ;						
			header("Location: ../presentation_layer/album.php");		
			exit();
		}
	}	
	else {
			$_SESSION['delete_message'] = 'Παρουσιάστηκε πρόβλημα κατά την διαγραφή.' ;						
			header("Location: ../presentation_layer/album.php");
			exit();
	}	
	
?>