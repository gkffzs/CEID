<?php
	// Ξεκινάει μία session, καθώς θέλουμε να είναι προσβάσιμη για όλους η σελίδα.
	session_start();
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Συμπερίληψη του αρχείου search_for_picture.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("../logic_layer/search_for_picture.php");
	// Σύνδεση με τη βάση δεδομένων.
	db_connect();
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ΑΝΑΖΗΤΗΣΗ",0);
	
	$display=10; // Αριθμός εικόνων ανά σελίδα.
	$ok_to_proceed=0;
	
	// Γίνεται η αναζήτηση είτε με βάση τις ετικέτες, είτε σε όλα τα πεδιά αναλόγα με την τιμή των μεταβλητών.
	// Σε περιπτώση που δεν βρεθεί κάποιο αποτέλεσμα ή παρουσιαστεί κάποιο άλλο πρόβλημα επιστρέφεται το αντίστοιχο μήνυμα.	
	if (isset($_GET['tags_search'])){
		$tags_check=$_GET['tags_search'];
	}
	
	// Έλεγχοι για το είδος της αναζήτησης και για τα ορίσματα.
	if (isset($_GET['terms']) && ($tags_check==1)) {
		$ar = search_terms($_GET['terms']);		
		$ok_to_proceed = 1;
	} elseif (isset($_GET['terms']) && ($tags_check==0)) {
		$ar = search_all($_GET['terms']);		
		$ok_to_proceed = 1;
	} elseif (isset($_GET['not_found']) && $_GET['not_found']==1) {
		echo '<p style="font-size:12px; width:620px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
		(δε βρέθηκε κανένα αποτέλεσμα)</p>';
	} elseif (isset($_GET['not_found']) && $_GET['not_found']==2) {
		echo '<p style="font-size:12px; width:620px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
		(δεν υπάρχει αυτή η ετικέτα)</p>';
	} else {
		echo '<p style="font-size:12px; width:620px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
		(παρακαλώ εισάγετε τουλάχιστον έναν όρο για την πραγματοποίηση της αναζήτησης)</p>';
	}
	
	// Αν βρεθεί αποτέλεσμα γίνεται η σελιδοποίηση και εμφανίζονται τα αποτελέσματα.
	if($ok_to_proceed == 1) {
		// Παίρνουμε τον αριθμό των αποτελεσμάτων.
		$records = found_pictures($ar);
		// Η μεταβλητή p περιέχει την σελίδα των αποτελεσμάτων
		if (isset($_GET['p']) && is_numeric($_GET['p'])) {
			$pages = $_GET['p'];
		// Υπολογιζουμε πόσες σελίδες θα χρειαστούμε για το album.
		} elseif ($records > $display) {
			$pages = ceil($records/$display); // Η ceil στρογγυλοποιεί προς τα πάνω.
		} else {
			$pages =1;
		}

		if (isset($_GET['s']) && is_numeric($_GET['s'])) {
			$start = $_GET['s'];
		} else {
			$start=0;
		}
		
		// Παίρνουμε τις πληροφορίες της φωτογραφίας.
		$result = get_picture_info($ar, $start, $display);
		
		$bg = '#FFECB3';
		
		echo '<table id="search_images" align="center" cellspacing="0" cellpading="0" width="650px">';
		
		// Εμφάνιση των φωτογραφιών που βρέθηκαν.
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			if($row['publication']==0){
				continue;
			}
		
			$bg = ($bg=='#FFECB3' ? '#CCD9FF' : '#FFECB3');
			
			echo '	<tr bgcolor="'.$bg.'">
					<td align="center"><a class="thumbnail_search" href="image.php?id=' . $row['picture_id'] . '"><img src="http://localhost/users_album/' . $row['username'] . "/" . $row['file_name'] . '"alt="'. $row['file_name'] .'"/></a></td>
					<td align="center"><b>' . $row['title'] . '</b></td><td align="center">' . $row['description'] . '</td>';
			
			$pic_id=$row['picture_id'];

			$result_tags = picture_tags($pic_id);
			
			$tag_number = mysql_num_rows($result_tags);
			
			echo '<td align="center">';
			
			while($pic_tags = mysql_fetch_array($result_tags)){
				echo '<a href="http://localhost/presentation_layer/search.php?tags_search=1&terms='.$pic_tags['tag_name'].'">'.$pic_tags['tag_name'].'</a>';
				
				if($tag_number>1){
					echo ', ';
					$tag_number--;
				}else{
					echo '';
				}
			}
			
			echo '</td></tr>';
		}
		
		echo '</table>';
		
		mysql_free_result($result);
		
		// Δημιουργία συνδέσμων για άλλες σελίδες αν χρειαστεί.
		if ($pages > 1) {
			// Προσθέτουμε κενά διαστήματα και καινούρια παράγραφο.
			echo '<br /><center><table id="pagination_links" cellspacing="0"><tr><td>';
			// Υπολογισμός σελιδών για εμφάνιση.
			$current_page=($start/$display)+1;
			
			if($current_page != 1) { 
				echo '<a href="search.php?terms='.$terms.'&s=' . ($start - $display) . '&p=' . $pages . ' &tags_search='.$tags_check.'"><<</a></td><td>';
			} else {
				echo '</td><td>';
			}
			// Δημιουργία όλων των αριθμημένων σελιδών.
			for($i = 1; $i <= $pages; $i++) {
				if ($i != $current_page) {
					echo '<a href="search.php?terms='.$terms.'&s=' . (($display * ($i - 1))) . '&p=' . $pages . '&tags_search='.$tags_check.' ">' . $i . '</a> ' ;
				} else {
					echo  $i . ' ';
				}
			}
			// Αν όχι, η τελευταία σελίδα.
			if ($current_page !=$pages) { 
				$next = $start + $display;
				echo '</td><td><a href="search.php?terms='.$terms.'&&s=' . $next . '&p=' . $pages . ' &tags_search='.$tags_check.'">>></a></td>';
			} else {
				echo '</td><td></td>';
			}

			echo '</tr></table>';
		}else{
			echo '<br/>';
		}
		
		echo '</center></td>';
	}
	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>