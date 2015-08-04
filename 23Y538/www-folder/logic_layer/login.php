<?php
	session_start();
	include("../database_layer/db_functions.php");
	db_connect();

	$form_username = $_POST["username"];
	$form_password = SHA1($_POST["password"]);

	$user_data = validate_user($form_username, $form_password);  // Έλεγχος εγκυρότητας του χρήστη.
	
	// Εαν υπάρχει ο χρήστης, αποθηκεύουμε κάποια δεδομένα του σε μεταβλητές τυπου $_SESSION
	// για μελλόντικες χρήσεις. Διαφορετικά εμφανίζεται το κατάλληλο μήνυμα.
	if(count($user_data['username'])){		
		$_SESSION['login_user']=$form_username;	
		$_SESSION['user_id'] = $user_data['user_id'];	
		$_SESSION['user_email'] = $user_data['email'];
		header("location: ../presentation_layer/index.php");
		exit();
	}else{
		$_SESSION['validation_log']='false';
		header("location: ../presentation_layer/index.php");
		exit();
	}
?>