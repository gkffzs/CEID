<?php
	include("lock.php");
	include("../database_layer/db_functions.php");
	db_connect();


	// Έλεγχος τύπου αρχείου ZIP
	if ($_FILES["file"]["type"] != "application/zip")	{
		echo "Το αρχείο δεν είναι κατάλληλου τύπου";
	} else {
		$size = 0;			
		$zip = zip_open($_FILES["file"]["tmp_name"]);		
		if ($zip)	{ // Διάβασμα αρχείου zip
			while ($zip_entry = zip_read($zip))	// Προσθέτει το μεγεθος κάθε αρχείου που περιέχεται στο συμπιεσμένο αρχείο.
			{
				$size=$size + zip_entry_filesize($zip_entry);
			}
			zip_close($zip);	

			$quota = quota(); // Παίρνουμε το μέγεθος του χώρου που χρησιμοποιεί ο χρήστης από την βάση δεδομένων.
		}
		if ($size > 20971520)  { // Ο χρήστης μπορεί να ανεβάσει μέχρι αρχείο 20MB.																					
			$_SESSION['upload_message'] = "Το αρχείο υπερβαίνει το όριο ανεβάσματος. ";
			header("Location: ../presentation_layer/upload.php");
			exit();
		}	
		elseif($size+$quota > 52428800) { // Ελέγχει αν υπερβένει το όριο του διαθέσιμου χώρου.
			$_SESSION['upload_message'] = "Υπερβένεται το όριο του διαθέσιμου χώρου σας.(".round($quota/1024/1024 , 2) ."/50 MB) --- Μέγεθος αρχείου: ".round($size , 3)." MB";
			header("Location: ../presentation_layer/upload.php");
			exit();
		}
		elseif ($_FILES["file"]["error"] > 0) {	// Για οποιοδήποτε άλλο προβλημα με το συμπιεσμένο αρχείο.
			$_SESSION['upload_message'] = "Παρουσιάστηκε κάποιο πρόβλημα στο αρχείο[**".$_FILES["file"]["error"].'**]. Παρακαλώ προσπαθείστε ξανά.';
			header("Location: ../presentation_layer/upload.php");
			exit();
		}	
		else { // Eαν δεν υπάρχει πρόβλημα.
			// Mετακίνησε προσωρινά το zip αρχείο στο άλμπουμ του χρήστη για να γίνουν οι εσωτερικοί έλεγχοι του συμπιεσμένου αρχείου.
			move_uploaded_file($_FILES["file"]["tmp_name"], "C:/wamp/www/users_album/".$_SESSION['login_user']."/".$_FILES["file"]["name"]);
		
			$delete_zip = $_FILES["file"]["name"]; // Διαγραφή του συμπιεσμένου απο την προσωρινή μνήμη.
			$zip = new ZipArchive;
			$res = $zip->open("C:/wamp/www/users_album/".$_SESSION['login_user']."/".$_FILES["file"]["name"]);

			// Έλεγχος των αρχείων του ZIP
			$file_type = 1;
			$num_of_files =  $zip->numFiles;
			for ($i=0; $i<$num_of_files; $i++) {
				$entry = $zip->statIndex($i); 			
				if (!preg_match('#\.(jpg|jpeg|png|xml)$#i', $entry['name'])) {	// Ο τύπος του αρχείου είναι διαφορετικός από τους επιτρεπτούς.
					$file_type = 0;
					if(!isset($er_files)){ // Κρατάμε την ονομασία των εσφαλμένων αρχείων για να τα χρησιμοποιήσουμε 
						$er_files = $entry['name'];	// στο ενημερωτικό μήνυμα παρακάτω.
					} else $er_files = $er_files.', '. $entry['name'];
				} 
				if (strcmp('info.xml',$entry['name'])){	// Υπάρχει το αρχείο info.xml ;
					$info_exist = 1;
				}
			}
			
			// Αν κάποιο απο τα αρχεία δεν είναι έγκυρα.
			if ($file_type == 0) {											
				if ( strstr($er_files, ',') !== false){
					$_SESSION['upload_message'] = "Τα αρχεία ".$er_files." που περιέχονται στο αρχείο zip δεν είναι έγκυρα. Παρακαλώ προσπαθείστε ξανά.";
				} else $_SESSION['upload_message'] = "Τo αρχείo ".$er_files." που περιέχεται στο αρχείο zip δεν είναι έγκυρo. Παρακαλώ προσπαθείστε ξανά.";
			}
			
			// Αν δεν περιέχεται το αρχείο info.xml.
			if (!$info_exist == 1) {		
				if ($file_type == 0) {	
					$_SESSION['upload_message'] =  $_SESSION['upload_message'] .'<br />Το info.xml δεν περιέχεται στο αρχείο zip. Παρακαλώ προσπαθείστε ξανά.';
				}
				$_SESSION['upload_message'] =  'Το info.xml δεν περιέχεται στο αρχείο zip. Παρακαλώ προσπαθείστε ξανά.';
			}
			
			// Σε περίπτωση που κάτι απο τα παραπάνω ισχύει, το συμπιεσμένο αρχείο διαγράφεται.
			if($file_type == 0 || $info_exist != 1){		
				unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$_FILES["file"]["name"]}");
				
				for ($i=0; $i<$num_of_files; $i++) {
					$entry = $zip->statIndex($i);
					if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}")) {
						unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}");
					}	
				}
				
				$zip->close();
				// Επιστρέφουμε στην σελίδα ανεβάσματος.
				header("Location: ../presentation_layer/upload.php");
				exit();
			}	
			
			// Διαφορετικα συνεχίζουμε και αποσυμπιέζουμε το αρχείο.
			if ($res === TRUE) {		
				$zip->extractTo("C:/wamp/www/users_album/".$_SESSION['login_user']);				

				$user_name = $_SESSION['login_user'];
				$user_id = $_SESSION['user_id'];
				
				// Ξεκινάει η ανάγνωση του αρχείου xml.
				if (file_exists("C:/wamp/www/users_album/".$_SESSION['login_user']."/info.xml")){			
					$xml = simplexml_load_file("C:/wamp/www/users_album/".$_SESSION['login_user']."/info.xml");
				}else { // Αν κάτι δεν πάει καλά διαγράφουμε όλα τα αρχεία που αποσυμπιέστηκαν.
					$_SESSION['upload_message'] = 'Παρουσιάστηκε κάποιο πρόβλημα κατά την επεξεργασία του αρχείου xml. Παρακαλώ προσπαθείστε ξανά.'.$entry['name'];
					unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$_FILES["file"]["name"]}");
					
					for ($i=0; $i<$num_of_files; $i++) {
						$entry = $zip->statIndex($i);
						if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}")) {
							unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}");
						}	
					}
					
					$zip->close();
					header("Location: ../presentation_layer/upload.php");
					exit();
				}


	// Έλεγχος εγκυρότητας αρχείου XML.	
				$info_found = 0;
				$i =0;
				foreach($xml->children() as $pictures){ // Έλεγχος πληροφορίων για κάθε αρχείο
					$i = $i+1; // Η μεταβλητή info_found μετράει κάθε πληροφορία που βρίσκει.
					if($pictures->getName() == 'file_name'){			
						$filename = $pictures;	
						$info_found++;			
						if(strlen($filename) == 0) $data_error = "yes";	// Υπάρχει το file_name αλλά είναι κενό. 					
					} // Αντίστοιχα γίνονται κα τα παρακάτω.
					elseif($pictures->getName() == 'title'){
						$title = $pictures;
						$info_found++;
						if(strlen($title) == 0) $data_error = "yes";				
					}
					elseif ($pictures->getName() == 'publication'){
						$publication=$pictures;
						$info_found++;
						if(strlen($publication) == 0 || !($publication ==0 || $publication ==1) ) $data_error = "yes";
					}
					elseif ($pictures->getName()=='description'){
						$info_found++;
						$description=$pictures;
						if(strlen($description) == 0) $data_error = "yes";
					}
					elseif ($pictures->getName()=='tags'){
						$tags=$pictures;
						$info_found++;
						if(strlen($tags) == 0)	$data_error = "yes"; 
					}
					elseif ($pictures->getName() == 'geolocation'){
						$info_found++;
					}
					elseif ($pictures->getName() == 'latitude'){
						$info_found++;
					}
					elseif ($pictures->getName() == 'length'){
						$info_found++;
					}																								
				}
				// Η info_found στο τέλος της λούπας θα πρέπει να έχει έναν συγκεκριμένο αριθμό για να ειναι έγκυρο το αρχείο
				// που προκύπτει αναλόγως με τον αριθμό των φωτογραφιών που είναι προς αποθήκευση.
				// Κάθε φωτογραφια πρεπει να εχει 8 πεδια. Π.χ. αν ο χρηστης ανεβάσει 2 εικόνες η info_found πρεπει να ειναι 16 κοκ.
				if($info_found == ($num_of_files - 1)*8 && !isset($data_error)){		
					$i = 0;	
					foreach( $xml->children() as $pictures){
						$i = $i + 1;
						if ($pictures->getName() == 'file_name'){
							$filename=$pictures;							
						}
						elseif ($pictures->getName() == 'title'){
							$title=$pictures;		
						}
						elseif ($pictures->getName() == 'publication'){
							$publication=$pictures;
						}
						elseif ($pictures->getName() == 'description'){
							$description=$pictures;
						}
						elseif ($pictures->getName() == 'tags'){
							$tags=$pictures;
						}
						elseif ($pictures->getName() == 'geolocation'){
							$geolocation=$pictures;
						}
						elseif ($pictures->getName() == 'latitude'){
							$lat=$pictures;
						}
						elseif ($pictures->getName() == 'length'){
							$len=$pictures;
						}
						if ($i == 8 && !isset($data_error)){ // Εχει προσπελάσει 8 στοιχεία άρα περνάει τα δεδομένα της φωτογραφίας στην βάση.
							$i = 0;									
							$input_image = "C:/wamp/www/users_album/".$_SESSION['login_user']."/".$filename;
			
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
								$uniqid_filename = uniqid()."-".$filename;
								ImageJPEG( $thumbnail, "C:/wamp/www/users_album/".$_SESSION['login_user']."/".	$filename);
								// Καθαρισμός της μνήμης της προσωρινής εικόνας.
								rename("C:/wamp/www/users_album/".$_SESSION['login_user']."/".$filename, 
										"C:/wamp/www/users_album/".$_SESSION['login_user'].'/'.$uniqid_filename);
								ImageDestroy( $thumbnail );
							}
							if(!isset($uniqid_filename)){
								$uniqid_filename = uniqid()."-".$filename;
								rename("C:/wamp/www/users_album/".$_SESSION['login_user']."/".$filename, 
										"C:/wamp/www/users_album/".$_SESSION['login_user'].'/'.$uniqid_filename);										
							}			
							$file_size = filesize("C:/wamp/www/users_album/".$_SESSION['login_user']."/".$uniqid_filename);	// Περνάμε τα δεδομένα στην βάση.	
							db_picture_insert($title,
														$description, 
														$publication, 
														$geolocation,
														$_SESSION['login_user'],
														$uniqid_filename,
														$file_size,
														$tags,
														$lat, 
														$len);
							
							if($publication==0){ // Αν ειναι ιδιωτικές τις μετακινούμε στον αντίστοιχο φάκελο.
								if(!is_dir("C:/wamp/private_images/users_album/".$_SESSION['login_user'])) {
									mkdir("C:/wamp/private_images/users_album/".$_SESSION['login_user']);
								}
								rename("C:/wamp/www/users_album/".$_SESSION['login_user']."/".$uniqid_filename, 
								"C:/wamp/private_images/users_album/".$_SESSION['login_user']."/".$uniqid_filename);
							}		
							
							unset($uniqid_filename);
							
						}elseif (isset($data_error) && $i == 8) { // Κραταάμε τα αρχεία που έχουν σφάλμα.
							$i = 0;
							if (isset($error_files)){
								$error_files = $error_files.','.$filename;
								
								unset($data_error);							
							}elseif ($i == 8) {
								$error_files = $filename;		
							}
						}	
					}
				} else { // Εάν παρουσιαστεί λάθος διαγράφουμε τα αρχεία.
					$_SESSION['upload_message'] = "Παρουσιάστηκε κάποιο πρόβλημα με το αρχείο xml. Παρακαλώ προσπαθείστε ξανά.";

					for ($i=0; $i<$num_of_files; $i++) {												
						$entry = $zip->statIndex($i);
						if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}")) {
						unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}");
						}	
					}
						
					$zip->close();
					unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$_FILES["file"]["name"]}");
					header("Location: ../presentation_layer/upload.php");
					exit();
				}	
			}	
		}	
	}
	
	// Παρακάτω συντάσσονται τα κατάλληλα μυνήματα και διαγράφονται τα κατάλληλα αρχεία.
	if (isset($error_files)){		
		if ( strstr($error_files, ',') !== false) { $upload_message = "Οι ακόλουθες φωτογραφίες ".$error_files."
								δεν περιέχουν όλες τις απαραίτητες πληροφορίες στο αρχείο xml (όνομα αρχείου,τίτλος, ετικέτες, περιγραφή, δημοσιότητα). 
								Παρακαλώ συμπληρώστε τις πληροφορίες και προσπαθείστε ξανά."; 
		}else {
				$upload_message = "Η ακόλουθη φωτογραφία ".$error_files." δεν περιέχει όλες τις απαραίτητες πληροφορίες 
												στο αρχείο xml (όνομα αρχείου, τίτλος, ετικέτες, περιγραφή, δημοσιότητα).
												Παρακαλώ συμπληρώστε τις πληροφορίες και προσπαθείστε ξανά."; 
		}	
		$_SESSION['upload_message'] = $upload_message; 
	} else {
		$_SESSION['upload_message'] = "Το ανέβασμα ήταν επιτυχές.";
		if (file_exists('C:/wamp/www/users_album/'.$_SESSION['login_user'].'/info.xml')){
		unlink('C:/wamp/www/users_album/'.$_SESSION['login_user'].'/info.xml');
		}
		$zip->close();
		if (file_exists('C:/wamp/www/users_album/'.$_SESSION['login_user'].'/'.$delete_zip)){
		unlink('C:/wamp/www/users_album/'.$_SESSION['login_user'].'/'.$delete_zip);
		}
	}
	
	if(isset($error_files)){
		for ($i=0; $i<$num_of_files; $i++) {
			$entry = $zip->statIndex($i);
			if(file_exists("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}")) {
			unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$entry['name']}");
			}	
		}
		
		$zip->close();
		unlink("C:/wamp/www/users_album/{$_SESSION['login_user']}/{$_FILES["file"]["name"]}");
		header("Location: ../presentation_layer/upload.php");
		exit();
	} else {
		header("Location: ../presentation_layer/album.php");
		exit();
	}

?>