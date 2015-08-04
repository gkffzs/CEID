<?php
	include("lock.php");

	include("../presentation_layer/header.php");
	
	$quota = quota();	
	$allowedExts = array("jpg", "jpeg", "png");
	$extension = end(explode(".", $_FILES["file"]["name"])); // Παίρνει την κατάληξη του αρχείου μετα την τελεία κοκ.
	if (((!$_FILES["file"]["type"] == "image/jpeg") // Ελέγχει αν το αρχείου είναι τύπου JPG/JPEG/PNG.
	   || (!$_FILES["file"]["type"] == "image/png") 
	   || (!$_FILES["file"]["type"] == "image/pjpeg")) 
	   && (!in_array($extension, $allowedExts))) { // Ελέγχει εαν η κατάληξει του αρχείου είναι αποδεκτή.
		echo '<div id="description_upload">ΣΦΑΛΜΑ: το αρχείο δεν είναι κατάλληλου τύπου (JPEG ή PNG).</div>';
    } elseif ($_FILES["file"]["size"]+$quota > 52428800) {
		echo '<div id="description_upload">ΣΦΑΛΜΑ: υπερβαίνετε το αποθηκευτικό σας όριο.</div> ';
	} elseif ($_FILES["file"]["size"] > 4194304) {
		echo '<div id="description_upload">ΣΦΑΛΜΑ: το αρχείο είναι πολύ μεγάλο, το ανώτατο όριο είναι <b>4 MB</b>.</div>';
    } elseif ($_FILES["file"]["error"] > 0) {
		echo '<div id="description_upload">'. $_FILES["file"]["error"] . '</div><br />';
		} else {		

			$file_name = uniqid()."-".$_FILES["file"]["name"]; // Με την χρήση της uniqid() δίνουμε ένα μοναδίκο όνομα σε κάθε αρχείο φωτογραφίας.
			
			$_SESSION['file_name'] = $file_name;
			
			move_uploaded_file($_FILES["file"]["tmp_name"], "C:/wamp/www/tmp/" . $file_name); // Το μετακινούμε απο την προσωρινή μνήμη στον φάκελο tmp.
			
			$input_image = "C:/wamp/www/tmp/" . $file_name; // Η διεύθυνση του αρχείου.
		
			$max_width = 1280;
			$max_height = 1024;
			
			list($original_width, $original_height) = getimagesize($input_image);
			
			if (($original_width > $max_width) OR ($original_height > $max_height)) {
				// Αν τo μέγιστο πλάτος ξεπερνίεται, μείωσε το πραγματικό πλάτος στο μέγεθος του ορίου.
				// Υπολόγισε το ύψος σύμφωνα με το πλάτος.
				if(($original_width > $max_width) AND ($original_height <= $max_height)) {   
					$percent = $max_width/$original_width;  
					$new_width = $max_width;
					$new_height = round ($original_height * $percent);
				}

				// Αν το μέγιστο ύψος ξεπερνίεται, μείωσε το πραγματικά ύψος στο μέγεθος του ορίου.
				// Υπολόγισε το πλάτος σύμφωνα με το ύψος.
				if(($original_width <= $max_width) AND ($original_height > $max_height)) {
					$percent = $max_height/$original_height;
					$new_height = $max_height;
					$new_width = round ($original_width * $percent);
				}

				// Και τα 2 όρια ξεπερνιούνται
				// αλλά η φωτογραφία μπορεί να είναι οριζόντια ή κάθετα.
				if(($original_width > $max_width) AND ($original_height > $max_height)){
					// Εαν η φωτογραφία έχει μεγαλύτερο πλάτος από ύψος
					// τότε όρισε το πλάτος στο μέγιστο πλάτος.
					if ($original_width > $original_height) {
						$percent = $max_width/$original_width;
						$new_width = $max_width;
						$new_height = round ($original_height * $percent );
					}

					// Η φωτογραφία είναι κάθετη ή τετράγωνη. Το ύψος ξεπερνάει το πλάτος
					// άρα όρισε το ύψος στο μέγιστο ύψος.
					else {
					$new_height = $max_height;
					$percent = $max_height/$original_height;
					$new_height = $max_height;
					$new_width = round ($original_width * $percent);
					}
				}			
				// Δημιουργία μιας καινούριας true color εικόνας στην μνήμη.
				$thumbnail = ImageCreateTrueColor( $new_width, $new_height );
				// Δημιουργία μιας καινούριας εικόνας απο το αρχείο.
				$src_img = ImageCreateFromJPEG( $input_image );
				// Δημιουργία εικόνας με προσαρμοσμένες διαστάσεις.
				ImageCopyResampled( $thumbnail, $src_img, 0, 0, 0, 0, $new_width, $new_height, $original_width, $original_height);
				// Αποθήκευση εικόνας.
				ImageJPEG( $thumbnail, 'C:/wamp/www/tmp/' . $file_name);
				// Καθαρισμός της μνήμης της προσωρινής εικόνας.
				ImageDestroy( $thumbnail );
			}
			
			$_SESSION['picture']=$_FILES["file"]["name"];
			$_SESSION['picture_size']= filesize("C:/wamp/www/tmp/". $file_name);
			$_SESSION['tmp_path'] = 'http://localhost/tmp/' .$file_name;			
			header("Location: ../presentation_layer/upload.php"); // Ανακατεύθυνση στην upload.php για την εισαγωγή των δεδομένων στην βάση δεδομένων.
			exit();
		}	
			
?>