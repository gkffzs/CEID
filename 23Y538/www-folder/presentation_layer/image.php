<?php
	// Ξεκινάει μία session, καθώς θέλουμε να είναι προσβάσιμη για όλους η σελίδα.
	session_start();
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ΠΡΟΒΟΛΗ ΦΩΤΟΓΡΑΦΙΑΣ",0);
	
	// Εκτύπωση πιθανού μηνύματος.
	if(isset($_SESSION['edit_message'])){
		echo '<div id="val_message">'.$_SESSION['edit_message'].'</div><br/>';
		unset($_SESSION['edit_message']);
	}
	
	$picture_id = $_GET['id'];
	
	// Παίρνουμε τα απαραίτητα δεδομένα για την φωτογραφία.
	$row = image_info($picture_id);
	
	$username = $row['username'];
	$total_hits = $row['total_hits'];
	$publication  = $row['publication'];
	
	if(isset($_SESSION['login_user'])){
		$comment_username = $_SESSION['login_user'];
	}
	
	// Εμφανίζεται στη σελίδα image η φωτογραφία (δημόσια/ιδιωτική) με το όνομα του χρήστη που την έχει ανεβάσει 
	// τον τίτλο και τον αριθμό των προβολών της φωτογραφίας.
	if($publication == 0){
			echo '<a href="../logic_layer/imagelocator.php?dir=' . $row['username'] . '&img=' . $row['file_name'] . '&logged_user='.$_SESSION['login_user'].'">';
			echo '<img src="../logic_layer/imagelocator.php?dir=' . $row['username'] . "&img=" . $row['file_name'] . '&logged_user='.$_SESSION['login_user'].'" alt="'. $row['file_name'] .'" onload="resize(this)" style="position: absolute; visibility: hidden;" /></a><br/>';
	}else{
		echo '<a href="http://localhost/users_album/'. $row['username'] . '/' . $row['file_name'] . '">';
		echo '<img src="http://localhost/users_album/' . $row['username'] . "/" . $row['file_name'] . '" alt="'. $row['file_name'] .'" onload="resize(this)" style="position: absolute; visibility: hidden;" /></a><br/>';
	}
	echo '<br/><table id="album_images" width="610px"><tr><td align="center"><b>'.$row['title'].'</b></td>';
	echo '<td width="22%" align="center"><b><i>~/'.$username.'</b></i></td>';
	echo '<td width="17%" align="center"><b>Προβολές:</b> '.$total_hits.'</td>';
	echo '<td width="7%" align="center">';
	
	// Αν ο χρήστης είναι αυτός της φωτογραφίας παρέχεται η δυνατότητα επεξεργασίας και διαγραφής της εικόνας.
	if(isset($_SESSION['login_user'])){
		if($username==$_SESSION['login_user']){
			echo '<a class="menu_images" href="image_edit.php?id=' . $row['picture_id'] .'"><img src="../images/edit_icon_29x29.png" alt="ΕΠΕΞΕΡΓΑΣΙΑ" title="Επεξεργασία Φωτογραφίας" width="13px"></a>
			<a class="menu_images" href="../logic_layer/image_delete.php?id=' . $row['picture_id'] .'"><img src="../images/delete_icon_24x24.png" alt="ΔΙΑΓΡΑΦΗ" title="Διαγραφή Φωτογραφίας" width="12px"></a>';
		}
	}
	
	echo '</td></tr></table>';
	echo '<table id="desc_table" width="610px"><tr><td align="justify"><b>Περιγραφή:</b> '.$row['description'].'</td></tr>';
	
	// Παίρνουμε τις ετικέτες της φωτογραφίας.
	$tag_result = picture_tags($picture_id);
	
	$tag_number = mysql_num_rows($tag_result);
	
	echo '<tr><td><b>Ετικέτες:</b> ';
	
	// Εμφανίζουμε τις ετικέτες της φωτογραφίας. 
	while($tag_row = mysql_fetch_array($tag_result)){
		echo '<a href="http://localhost/presentation_layer/search.php?tags_search=1&terms='.$tag_row['tag_name'].'">'.$tag_row['tag_name'].'</a>';
		
		// Παρακάτω γίνεται ο διαχωρισμός τους με την εισαγωγή κομμάτων.
		if($tag_number>1){
			echo ', ';
			$tag_number--;
		}else{
			echo '';
		}
	}
	
	echo '</td></tr></table><br/>';
	
	// Εάν δεν είναι ο χρήστης ο κάτοχος της φωτογραφιάς τότε η δημοσίοτητα της αυξάνεται κατά 1.
	if((!isset($_SESSION['login_user'])) || ($_SESSION['login_user']!=$row['username'])){
		$total_hits++;
	}
	
	// Το αντίστοιχο ερώτημα στη βάση δεδομένων για την δημοσίοτητα της.
	increase_picture_hits($picture_id, $total_hits);
	
	// Εδώ εκτυπώνοται τα σχόλια που ήδη έχει η φωτογραφία.
	print_comments($picture_id);
	
	// Εάν κάποιος χρήστης του ιστοτόπου είναι συνδεδεμένος, τότε έχει την επιλογή να σχολιάσει την φωτογραφία.
	if(isset($_SESSION['login_user'])){
		echo '	<form method="POST" action="../logic_layer/comment.php?id=' . $picture_id . '&username=' . $comment_username . '" accept-charset="UTF-8" onSubmit="return confirm_comment(this)">
						<table width="250px" border="0" cellspacing="0" cellpadding="0">
							<tr><td><textarea name="comment_text" cols="30" rows="6" style="width:250px; font-family: ‘Trebuchet MS’, Helvetica, sans-serif;"></textarea></td></tr>
							<tr><td>&ensp;</td></tr>
							<tr><td align="center"><button type="submit" name="Submit" value="ΥΠΟΒΟΛΗ ΣΧΟΛΙΟΥ">ΥΠΟΒΟΛΗ ΣΧΟΛΙΟΥ</button></td></tr>
						</table>
				</form>';
	}
	
	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>