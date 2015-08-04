<?php
	session_start();
	include("../database_layer/db_functions.php");
	db_connect();

	$form_username = $_POST["username"];
	$form_password = $_POST["password"];
	$form_password_val = $_POST["password_val"];
	$form_email = $_POST["email"];

	if($form_password != $form_password_val){ // Έλεγχος εγκυρότητας κωδικού.
		$_SESSION['message_reg'] ="Ο κωδικός που πληκτρολογήσατε είναι λανθασμένος.";
	}
	elseif(db_user_check($form_username) != 0){	// Ελέγχει έαν χρησιμοποιείται το όνομα του χρήστη.
		$_SESSION['message_reg']="Το όνομα του χρήστη που εισάγατε χρησιμοποιείται ήδη, παρακαλούμε προσπαθείστε ξανά.";
	}
	elseif(db_email_check($form_email) != 0 ){ // Έλεγχος του email.
		$_SESSION['message_reg']= "Το email που εισάγατε χρησιμοποιείται ήδη, παρακαλούμε προσπαθείστε ξανά.";
	}
	else{ // Δημιουργεί τους κατάλληλους φακέλους για κάθε εγγραφή χρήστη.
		if(!is_dir("C:/wamp/www/users_album/$form_username/")) {
			mkdir("C:/wamp/www/users_album/$form_username/") or die("Εμφανίστηκε σφάλμα κατα τη δημιουργία φακέλου.");
		}		
		if(!is_dir("C:/wamp/private_images/users_album/$form_username/")) {
			mkdir("C:/wamp/private_images/users_album/$form_username/") or die("Εμφανίστηκε σφάλμα κατα τη δημιουργία φακέλου."); 
		}
		
		// Εισάγουμε τα δεδομένα του χρήστη στην βάση δεδομένων.
		db_reg_input($form_username, $form_password, $form_email); 
	
		$_SESSION['message_reg']= "Η εγγραφή σας ολοκληρώθηκε επιτυχώς.";
	}	
	header("location: ../presentation_layer/index.php");
	exit();
?>	