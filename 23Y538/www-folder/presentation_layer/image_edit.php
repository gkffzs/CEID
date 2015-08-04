<?php
// Συμπερίληψη του lock.php για να είναι ελεγχόμενη η πρόσβαση στη σελίδα αυτή.
	include("../logic_layer/lock.php");
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(2,"ΕΠΕΞΕΡΓΑΣΙΑ ΕΙΚΟΝΑΣ",2);
	
	$picture_id=$_GET['id'];
										
	$row = image_info($picture_id);
	
	// Αν ο χρήστης δεν είναι ίδιος με τον κάτοχο της φωτογραφίας, επιστροφή στην αρχική σελίδα.
	if($row['username']!=$_SESSION['login_user']){
		header("Location: /index.php");
	}
	
	// Εμφανίζεται στον χρήστη που έχει ανεβάσει την φωτογραφία μια φόρμα με όλες τις πληροφορίες προς επεξεργασία.
	if($row['publication'] == 0){
		echo '<a href="imagelocator.php?dir=' . $row['username'] .'&img='. $row['file_name'].'&logged_user='.$_SESSION['login_user'].'">';
		echo '<img src="imagelocator.php?dir=' . $row['username'] .'&img='. $row['file_name'].'&logged_user='.$_SESSION['login_user']. '"alt="'. $row['file_name'] .'" onload="resize(this)" style="position: absolute; visibility: hidden;" /></a>';;
	} else{
		echo '<a href="http://localhost/users_album/' . $row['username'] . "/" . $row['file_name'] . '">';
		echo '<img src="http://localhost/users_album/' . $row['username'] . "/" . $row['file_name'] . '"alt="'. $row['file_name'] .'" onload="resize(this)" style="position: absolute; visibility: hidden;" /></a>';
	}

	// Εκτύπωση φόρμας για αλλαγή των στοιχείων.
	echo '	</center><br/><br/><center>
			<table id="edit_table" border="0" cellspacing="0" width="390px">
				<form method="POST" action="../logic_layer/edit_pic_data.php?id='.$picture_id.'" accept-charset="UTF-8" onSubmit="return confirm_pic_data(this)">
				<tr><td colspan="4"></td></tr>
				<tr><td colspan="4" align="center"><p style="font-size:12px; width:400px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
				Από εδώ μπορείτε να αλλάξετε τα στοιχεία της φωτογραφίας σας.<br/>
				Παρακαλώ, συμπληρώστε οπωσδήποτε τα πεδία με την ένδειξη <font color="#D80000">*</font>.
				</p>
				</td></tr>
				<tr><td><b>ΤΙΤΛΟΣ</b><font color="#D80000">*</font></td><td align="right"><input type="text" name="title" style="width:200px;" value="'.$row['title'].'"></td>
				<td colspan="2" rowspan="4"><div id="map_canvas" style="width: 260px; height: 180px; margin: 0 auto;"></div></td></tr>
				<tr><td ><b>ΠΕΡΙΓΡΑΦΗ</b><font color="#D80000">*</FONT></td><td align="center"><textarea id="description_area" name="description" style="width:200px; font-family: ‘Trebuchet MS’, Helvetica, sans-serif;" rows=5>'.$row['description'].'</textarea></td></tr>
				<tr><td><b>ΕΤΙΚΕΤΕΣ</b><font color="#D80000">*</FONT></td><td align="center"><textarea autocomplete="off" id="tags_autocomplete" rows="1" name="tags" style="width:200px;">';
	
	// Παίρνουμε όλες τις ετικέτες της φωτογραφίας.	
	$tag_result = picture_tags($picture_id);
	$tag_number = mysql_num_rows($tag_result);
	
	// Εμφανίζουμε τις ετικέτες της φωτογραφίας. 
	while($tag_row = mysql_fetch_array($tag_result)){
		echo $tag_row['tag_name'];
		
		// Παρακάτω γίνεται ο διαχωρισμός τους με την εισαγωγή κομμάτων.	
		if($tag_number>1){
			echo ',';
			$tag_number--;
		}else{
			echo '';
		}
	}
		
	echo '		</textarea></td></tr>
				<tr><td><b>ΠΡΟΣΒΑΣΗ</b><font color="#D80000">*</FONT></td><td width="200px" align="center"><input type="radio" name="publication" value="1"';
	
	// Εάν η φωτογραφία ειναι δημόσια είναι προεπιλεγμένο το «ΔΗΜΟΣΙΑ», διαφορετικα το «ΙΔΙΩΤΙΚΗ».	
	if($row['publication']==1){
		echo 'checked="checked">ΔΗΜΟΣΙΑ <input type="radio" name="publication" value="0">ΙΔΙΩΤΙΚΗ</td></tr>';
	}else{
		echo '>ΔΗΜΟΣΙΑ <input type="radio" name="publication" value="1" checked="checked">ΙΔΙΩΤΙΚΗ</td></tr>';
	}
		
	echo '		<tr><td><b>ΤΟΠΟΘΕΣΙΑ</b></td><td align="right"><input type="text" name="geolocation" value="'.$row['geolocation'].'" style="width:200px;"></td><td colspan="2"><p style="font-size:12px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic; text-align: center;">Κάντε κλικ στον χάρτη για να αλλάξετε τις συντεταγμένες της φωτογραφίας.</p></td></tr>
				<tr><td><b>ΠΛΑΤΟΣ</b></td><td><input style="width:200px;" type="text" id="latbox" name="lat" value="'.$row['lat'].'"></td><td><b>ΜΗΚΟΣ</b></td><td><input style="width:200px;" type="text" id="lngbox" name="lng" value="'.$row['lng'].'"></td></tr>
				<tr><td align="right" colspan="4"><button type="submit" value="ΑΠΟΘΗΚΕΥΣΗ">ΑΠΟΘΗΚΕΥΣΗ</button>&ensp;</td></tr>
				<tr><td colspan="4"></td></tr>
			</form>
		</table><br/>';
	
	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>