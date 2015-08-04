<?php
	// Ξεκινάει μία session, καθώς θέλουμε να είναι προσβάσιμη για όλους η σελίδα.
	session_start();
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ΣΧΕΤΙΚΑ ΜΕ ΤΟ SITE",0);
	
	// Εκτύπωση κειμένου σχετικά με την ιστοσελίδα.
	echo '	<div style="width: 580px; font-family: ‘Trebuchet MS’, Helvetica, sans-serif; font-size: 12px; text-align: justify;">
			<img src="http://localhost/images/only_logo.png" width="30px" align="left" style="padding: 12px 12px 10px 0px;">
			Το παρόν site αποτελεί ένα πλήρες σύστημα on-line διαμοιρασμού εικόνων σύμφωνα με την εργασία στα πλαίσια του μαθήματος 
			<b>«Προγραμματισμός και Συστήματα στον Παγκόσμιο Ιστό»</b> για το ακαδημαϊκό έτος 2011-2012. Για την υλοποίηση του χρησιμοποιήθηκαν
			γλώσσες και τεχνολογίες όπως PHP, HTML, JavaScript, AJAX και XML, ενώ υποστηρίζεται πλήρως η ελληνική γλώσσα.</div>';

	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>