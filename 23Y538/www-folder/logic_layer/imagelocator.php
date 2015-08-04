<?php
	session_start();
	
	// Το αρχείο αυτό «σερβίρει» τις ιδιωτικές φωτογραφίες. 
	if(isset($_SESSION['login_user'])){
		$fname = $_GET['img']; 
		$dir = $_GET['dir'];
		$logged_user=$_GET['logged_user'];
		$logged_user_check=$_SESSION['login_user'];

		if(($dir==$logged_user) AND ($logged_user_check==$logged_user)){
			$basedir = 'C:/wamp/private_images/users_album/'.$dir.'/'; 

			if (!file_exists($basedir.$fname)){
				header("Location: ../presentation_layer/index.php");
				exit();
			}
			
			ob_start(); // Eκκίνηση προσωρινής αποθήκευσης.
			$img = file_get_contents($basedir.$fname,TRUE); // Διάβαζουμε το αρχείο σε string.
			$im = imagecreatefromstring ($img); // Επιστρέφει ενα αναγνωριστικό εικόνας διαβάζοντας δεδομένα εικόνας από ένα string.
			ob_end_clean(); // Διαγραφή δεδομένων απο την προσωρινή μνήμη.
			
			if($im !== false) { // Εαν επιστράφηκε το αναγνωριστικό εικόνας επιτυχώς.
				echo $img;					
				echo $im;
				header ("Content-Type: image/jpeg"); 
				imageJPEG ($im);
				imageDestroy ($im);

			} else {
				header("Location: ../presentation_layer/index.php");
				exit();
			}
		}
	} else {
		header("Location: ../presentation_layer/index.php");
		exit();
	}
?>