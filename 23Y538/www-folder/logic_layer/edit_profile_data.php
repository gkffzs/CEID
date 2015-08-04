<?php
	include("lock.php");
	include("../database_layer/db_functions.php");
	db_connect();

	$form_user_id=$_GET['user_id'];
	$form_username=$_SESSION['login_user'];
	$form_new_email=$_POST["new_email"];
	$form_new_password=$_POST["new_password"];
	$form_new_password_val=$_POST["new_password_val"];
	$form_old_password=SHA1($_POST["old_password"]);	
	
	$user_data = validate_user($form_username, $form_old_password); // Έλεγχος εγκυρότητας του χρήστη.

	if(count($user_data['username'])){ // Εαν βρεθεί χρήστης συνέχισε.	
		if($form_new_password != $form_new_password_val){ // Έλεγχος σωστής εισαγωγής νέου κωδικού.
			$_SESSION['pro_edit_message'] ="Ο νέος κωδικός που πληκτρολογήσατε είναι λανθασμένος.";
			header("location: ../presentation_layer/edit_profile.php");
			exit();
		}
		
		db_profile_update($form_user_id, $form_new_email, $form_new_password); // Ενημερώνει τα στοιχεία του χρήστη στην βάση δεδομένων.
		
		$_SESSION['pro_edit_message']= "Η ανανέωση των στοιχείων σας ολοκληρώθηκε επιτυχώς.";
		header("location: ../presentation_layer/album.php");
		exit();
	} else {
		$_SESSION['pro_edit_message'] ="Ο παλιός κωδικός που πληκτρολογήσατε είναι λανθασμένος.";
		header("location: ../presentation_layer/edit_profile.php");
		exit();
	}
?>