<?php
	//  Αποστολή του σχολίου και άλλων πληροφορίων προς την βάση δεδομένων.
	session_start();	
	include("../database_layer/db_functions.php");
	db_connect();
	
	$form_username = $_GET["username"];
	$form_comment_text = $_POST["comment_text"];
	$form_picture_id = $_GET['id'];
	$form_date = date('Y-m-d H:i:s');
	
	db_insert_comment($form_username, $form_comment_text, $form_picture_id, $form_date);  // Μέθοδος που επικοινωνεί με την βάση δεδομένων
	
	// Ανακατεύθυνση στην εικόνα που προστέθηκε το σχόλιο.
	header("location: ../presentation_layer/image.php?id=$form_picture_id");
	exit;
?>