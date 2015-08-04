<?php
	session_start(); 
	
	//Καταστρέφεται αυτό το session και επιστρέφουμε στην αρχική σελίδα.	
	session_destroy(); 
	header("Location: ../presentation_layer/index.php");
	exit();
?>