<?php
	// Ξεκινάει μία session, καθώς θέλουμε να είναι προσβάσιμη για όλους η σελίδα.
	session_start();
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(1,"ΚΑΛΩΣ ΗΛΘΑΤΕ ΣΤΗΝ e-kona!",0);
	
	// Εμφανίζονται οι 10 διασημότερες φωτογραφίες.			
	top_10_images();
	
	// Εκτύπωση πιθανού μηνύματος.
	if(isset($_SESSION['inactive_message'])){
		echo '<div id="val_message">'.$_SESSION['inactive_message'].'</div>';
		unset($_SESSION['inactive_message']);
		session_destroy();
	}	
	// Εμφανίζεται ο χάρτης
	echo '<div id="map_canvas" style="width: 620px; height: 450px; margin: 0 auto;"></div><br/>';
	// Εκτύπωση του υποσέλιδου.	
	side_and_footer();
?>