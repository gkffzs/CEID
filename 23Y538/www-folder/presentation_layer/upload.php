<?php
	// Συμπερίληψη του lock.php για να είναι ελεγχόμενη η πρόσβαση στη σελίδα αυτή.
	include("../logic_layer/lock.php");
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ΑΝΕΒΑΣΜΑ ΦΩΤΟΓΡΑΦΙΩΝ",0);
	
	// Εκτύπωση πιθανού μηνύματος.
	if(isset($_SESSION['upload_message'])){
		echo '<div id="val_message">'.$_SESSION['upload_message'].'</div><br/>';
		unset($_SESSION['upload_message']);
	}
	
	if(!isset($_SESSION['tmp_path'])) { // Εκτύπωση φορμών για ανέβασμα φωτογραφιών.
		echo '<table id="upload_table"><tr> 
						<td align="center" valign="center">
							<form action="../logic_layer/upload_image.php" method="post" enctype="multipart/form-data" onSubmit="return confirm_upload(this)">
								<label for="file"><b>ΑΡΧΕΙΟ:</b></label></font>
								<input type="file" name="file" id="file"/> 
								<button type="submit" name="submit" value="ΥΠΟΒΟΛΗ"/>ΥΠΟΒΟΛΗ</button>
							</form>
							
							<p style="font-size:12px; width:400px; text-align: center; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
							Από εδώ μπορείτε να ανεβάσετε μια φωτογραφία της επιλογής σας.</p><br/>
						</td></tr>';
		
		echo '	<tr><td align="center" valign="center">
					<form action="../logic_layer/zip_xml.php" method="post" enctype="multipart/form-data" onSubmit="return confirm_upload(this)">
						<label for="file"><b>ΑΡΧΕΙΟ:</b></label></font>
						<input type="file" name="file" id="file" /> 
						<button type="submit" name="submit" value="ΥΠΟΒΟΛΗ"/>ΥΠΟΒΟΛΗ</button>
					</form>
					
					<p style="font-size:12px; width:380px; text-align: justify; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
						Για <b>μαζικό ανέβασμα φωτογραφιών</b> πρέπει να δημιουργήσετε ένα zip αρχείο, το οποίο θα περίεχει όλες τις φωτογραφίες 
						που θέλετε να ανεβάσετε, και ένα XML αρχείο με το όνομα "info.xml", το οποίο πρέπει να περιέχει για κάθε φωτογραφία τις 
						απαραίτητες	πληροφορίες για την εισαγωγή της. Το αρχείο μπορεί να είναι <b>το μέγιστο μέχρι 20 MB</b>. Κατεβάστε το υπόδειγμα κάνοντας δεξί κλικ και «Αποθήκευση ως» <a href="http://localhost/downloads/info.xml" style="color: black; font-family: ‘Trebuchet MS’, Helvetica, sans-serif; text-decoration: none; font-weight: bold;">εδώ</a>.<br/><br/></p>
					</td>
				</tr></table>';
	} else { // Εκτύπωση εικόνας και φόρμας για συμπλήρωση στοιχείων μετά από το ανέβασμα.		
		header("Refresh: 300; url=http://localhost/presentation_layer/upload.php");
		echo '<div id="val_message">Επιτυχές ανέβασμα!</div><br />';
		echo '<img src="'.$_SESSION['tmp_path'].'" onload="resize(this)" style="position: absolute; visibility: hidden;">
					<br/><center><br/>
					<table id="edit_table" border="0" cellspacing="0" width="390px">
						<form method="POST" action="../logic_layer/picture_data.php" accept-charset="UTF-8" onSubmit="return confirm_pic_data(this)">
							<tr><td colspan="4"></td></tr>
							<tr><td colspan="4" align="center"><p style="font-size:12px; width:400px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic;">
								Παρακαλώ, συμπληρώστε οπωσδήποτε τα πεδία με την ένδειξη <font color="#D80000">*</font>.
								</p>
							</td></tr>
							<tr><td><b>ΤΙΤΛΟΣ</b><FONT COLOR="#D80000">*</FONT></td><td><input type="text" name="title" style="width:200px;"></td>
							<td colspan="2" rowspan="4"><div id="map_canvas" style="width: 260px; height: 180px; margin: 0 auto;"></div></td></tr>
							<tr><td><b>ΠΕΡΙΓΡΑΦΗ</b><FONT COLOR="#D80000">*</FONT></td><td align="center"><textarea id="description_area" name="description" style="width:200px;" rows=5></textarea></td></tr>
							<tr><td><b>ΕΤΙΚΕΤΕΣ</b><FONT COLOR="#D80000">*</FONT></td><td align="center"><textarea autocomplete="off" id="tags_autocomplete" name="tags" rows="1" style="width:200px;"></textarea></td></tr>
							<tr><td><b>ΠΡΟΣΒΑΣΗ</b><FONT COLOR="#D80000">*</FONT></td><td width="200px" align="center"><input type="radio" name="publication" value="1" checked="checked">ΔΗΜΟΣΙΑ <input type="radio" name="publication" value="0" >ΙΔΙΩΤΙΚΗ</td></tr>
							<tr><td><b>ΤΟΠΟΘΕΣΙΑ</b></td><td><input type="text" name="geolocation" style="width:200px;"></td><td colspan="2"><p style="font-size:12px; font-family:‘Trebuchet MS’, Helvetica, sans-serif; font-style:italic; text-align: center;">Κάντε κλικ στον χάρτη για να αλλάξετε τις συντεταγμένες της φωτογραφίας.</p></td></tr>
							<tr><td><b>ΠΛΑΤΟΣ</b></td><td><input style="width:200px;" type="text" id="latbox" name="lat"></td><td><b>ΜΗΚΟΣ</b></td><td><input style="width:200px;" type="text" id="lngbox" name="lng"></td></tr>
							<tr><td align="right" colspan="4"><button type="submit" value="ΑΠΟΘΗΚΕΥΣΗ">ΑΠΟΘΗΚΕΥΣΗ</button>&ensp;</td></tr>
							<tr><td colspan="4"></td></tr>
						</form>
					</table>';						
		unset($_SESSION['tmp_path']);
	}
	// Εκτύπωση του υποσέλιδου.
	side_and_footer();
?>