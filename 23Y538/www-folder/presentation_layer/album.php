<?php
	// Συμπερίληψη του lock.php για να είναι ελεγχόμενη η πρόσβαση στη σελίδα αυτή.
	include("../logic_layer/lock.php");
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Σύνδεση με τη βάση δεδομένων.
	db_connect();
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ALBUM",0);
	
	// Πιθανά μηνύματα.
	if(isset($_SESSION['delete_message'])){
		echo '<div id="val_message">'.$_SESSION['delete_message'].'</div><br/>';
		unset($_SESSION['delete_message']);
	}
	
	if(isset($_SESSION['upload_message'])){
		echo '<div id="val_message">'.$_SESSION['upload_message'].'</div><br/>';
		unset($_SESSION['upload_message']);
	}

	$display=12; // Αριθμός που προσδιορίζει το πόσες εικόνες θα εμφανίζονται ανά σελίδα.
	$user=$_SESSION['user_id'];
	$records=1;
	
	// Η μεταβλητή p περιέχει την σελίδα του album.
	if (isset($_GET['p']) && is_numeric($_GET['p'])){ 
		$pages = $_GET['p'];
	} else {
		// Παίρνουμε τον αριθμό των φωτογραφιών του χρήστη. 
		$records = user_num_pictures($user);  

		// Υπολογιζουμε πόσες σελίδες θα χρειαστούμε για το album.
		if ($records > $display) {			
			$pages = ceil($records/$display); // Η ceil στρογγυλοποιεί προς τα πάνω.
		} else {
			$pages = 1;
		}
	}
	
	if($records==0) {
		echo '<div style="width: 600px; font-family: ‘Trebuchet MS’, Helvetica, sans-serif; font-size: 12px;">Δεν έχετε ακόμα φωτογραφίες! Παρακαλώ ακολουθήστε τον επόμενο σύνδεσμο για να
			<a href="http://localhost/presentation_layer/upload.php">ανεβάσετε</a>.</div>';
	} else {
		// Καθορίζουμε ποιες φωτογραφίες θα εμφανίζονται. Αυτό γίνεται με την μεταβλητή s που χρησιμοποιείται στο MySQL ερώτημα.
		if (isset($_GET['s']) && is_numeric($_GET['s'])) {
			$start = $_GET['s'];
		} else {
			$start  = 0;
		}
		// Επιστρέφονται οι φωτογραφίες ως αποτέλεσμα ερωτήματος MySQL.
		$result = user_pictures ($user, $start, $display); 
		
		echo '<table align="center" width="650px">';
		$counter=0;
		
		// Γίνεται η κατάλληλη προσπέλαση του πίνακα, και εμφάνιζονται οι φωτογραφίες.
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			if($counter % 4 == 0){
				echo '<tr>';
			}
			
			if($row['publication'] == 0){
				echo '<td align="center"><a class="thumbnail" href="image.php?id=' . $row['picture_id'] . '"><img src="../logic_layer/imagelocator.php?dir=' . $row['username'] .'&img='. $row['file_name'].'&logged_user='.$_SESSION['login_user'];
			} else{
				echo '<td align="center"><a class="thumbnail" href="image.php?id=' . $row['picture_id'] . '"><img src="http://localhost/users_album/' . $row['username'] . '/' . $row['file_name'];
			}
			
			echo '" alt="'. $row['file_name'] .'" border="0" /></a>
			<table id="album_images" width="156px"><tr><td align="center"><a href="image.php?id=' . $row['picture_id'] . '"><b><div class="text_to_shorten" style="width: 96px; text-overflow:ellipsis;">' . $row['title'] . '</div></b></a></td>
			<td width="23%" align="center"><a class="menu_images" href="image_edit.php?id=' . $row['picture_id'] . '"><img src="../images/edit_icon_29x29.png" alt="ΕΠΕΞΕΡΓΑΣΙΑ" title="Επεξεργασία Φωτογραφίας" width="13px"></a>
			<a class="menu_images" href="../logic_layer/image_delete.php?id=' . $row['picture_id'] . '"><img src="../images/delete_icon_24x24.png" alt="ΔΙΑΓΡΑΦΗ" title="Διαγραφή Φωτογραφίας" width="12px"></a></td></tr></table></td>';
		
			if($counter%4==3){
				echo '</tr>';
			}
			
			$counter++;
		} // Τέλος while.
		echo '</table><br/>';

		mysql_free_result($result);

		// Δημιουργία συνδέσμων για άλλες σελίδες αν χρειαστεί.
		if ($pages > 1) {
			// Προσθέτουμε κενά διαστήματα και καινούρια παράγραφο.
			echo '<center><table id="pagination_links" cellspacing="0"><tr>';
			
			// Υπολογισμός σελιδών για εμφάνιση.
			$current_page=($start/$display)+1;
			
			if($current_page != 1) { 
				echo '<td><a href="album.php?s=' . ($start - $display) . '&p=' . $pages . ' "><<</a></td><td>';
			} else {
				echo '<td></td><td>';
			}

			// Δημιουργία όλων των αριθμημένων σελιδών.
			for($i = 1; $i <= $pages; $i++) {
				if ($i != $current_page) {
					echo '<a href="album.php?s=' . (($display * ($i - 1))) . '&p=' . $pages . ' ">' . $i . '</a> ' ;
				} else {
					echo  $i . ' ';
				}
			} // Τέλος for.

			// Αν όχι η τελευταία σελίδα.
			if ($current_page !=$pages) { 
				$next = $start + $display;
				echo '</td><td><a href="album.php?s=' . $next . '&p=' . $pages . ' ">>></a></td>';
			} else {
				echo '</td><td></td>';
			}

			echo '</tr></table></center>';
		}
	}
	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>