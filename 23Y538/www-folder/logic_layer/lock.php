<?php
	session_start();
	
	// Κάθε φορά που ανοίγει μια καινούρια σελίδα ελέγχεται αν ο χρόνος που πέρασε απο την τελευταία ενέργεια είναι μεγαλύτερος
	// των 10 λεπτών. Σε αυτή την περίπτωση αποσυνδέει τον χρήστη και τον ανακατευθύνει στην αρχική σελίδα.
	
	// Θέτουμε το όριο της περιόδου (σε δευτερόλεπτα).
	$inactive = 600;
	
	// Ελέγχουμε αν έχει τεθεί η μεταβλητή $_SESSION["timeout"].
	// Εαν ναι, τότε σημαίνει ότι ο χρόνος έχει ξεπεραστεί.
	if (isset($_SESSION["timeout"])) {
	// Υπολογίζουμε τον «χρόνο ζωής» της περιόδου.
		$sessionTTL = time() - $_SESSION["timeout"];
		if ($sessionTTL > $inactive) {
			unset($_SESSION['login_user']);
			$_SESSION['inactive_message'] = 'Πέρασε αρκετός χρόνος που ήσασταν αδρανείς στον ιστότοπο μας, παρακαλώ συνδεθείται ξανά. ';
			header("Location: ../presentation_layer/index.php");
		}
	}
	
	$_SESSION["timeout"] = time();
	
	// Εαν δεν είναι συνδεδεμένος ο χρήστης, ανακατεύθυνση στην αρχική σελίδα.
	if(!isset($_SESSION['login_user'])){ 
		header("Location: ../presentation_layer/index.php");
	}
?>