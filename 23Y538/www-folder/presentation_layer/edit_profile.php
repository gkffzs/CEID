<?php
// Συμπερίληψη του lock.php για να είναι ελεγχόμενη η πρόσβαση στη σελίδα αυτή.
	include("../logic_layer/lock.php");
	// Συμπερίληψη του αρχείου header.php για δυνατότητα κλήσης των μεθόδων που περιέχει.
	include("header.php");
	// Εκτύπωση του μέρους <head> του αρχείου HTML, μαζί με τα javascript, το πάνω μέρος και τον τίτλο της σελίδας.
	header_print(0,"ΕΠΕΞΕΡΓΑΣΙΑ ΣΤΟΙΧΕΙΩΝ ΛΟΓΑΡΙΑΣΜΟΥ",0);
	
	$username = $_SESSION['login_user'];
	$user_id = $_SESSION['user_id'];
	$user_email = $_SESSION['user_email'];
	
	// Εκτύπωση φόρμας για αλλαγή των στοιχείων του χρήστη.
	echo '	<table id="edit_table" cellspacing="0" border="0">
				<form method="POST" action="../logic_layer/edit_profile_data.php?user_id='.$user_id.'" accept-charset="UTF-8" onSubmit="return confirm_profile_edit(this)">
					<tr><td colspan="2"></td></tr>
					<tr><td><b>ΟΝΟΜΑ ΧΡΗΣΤΗ</b></td><td align="center"><b><i>'.$username.'</b></i></td></tr>
					<tr><td><b>EMAIL</b></td><td align="right"><input type="text" name="new_email" value="'.$user_email.'"></td></tr>
					<tr><td><b>ΝΕΟΣ ΚΩΔΙΚΟΣ</b></td><td align="right"><input type="password" name="new_password"></td></tr>
					<tr><td><b>ΕΠΙΒΕΒΑΙΩΣΗ ΝΕΟΥ ΚΩΔΙΚΟΥ</b></td><td align="right"><input type="password" name="new_password_val"></td></tr>
					<tr><td colspan="2"></td></tr>
					<tr><td colspan="2" align="center"><i>Για να πραγματοποιηθούν οι αλλαγές εισάγετε τον παλιό σας κωδικό.</i></td></tr>
					<tr><td><b>ΠΑΛΙΟΣ ΚΩΔΙΚΟΣ</b></td><td align="right"><input type="password" name="old_password"></td></tr>
					<tr><td align="center" colspan="2"><button type="submit" value="ΑΠΟΘΗΚΕΥΣΗ ΑΛΛΑΓΩΝ">ΑΠΟΘΗΚΕΥΣΗ ΑΛΛΑΓΩΝ</button>&ensp;</td></tr>
					<tr><td colspan="2"></td></tr>
				</form>
			</table>';
	
	// Εκτύπωση πιθανού μηνύματος κατά την επεξεργασία.
	if(isset($_SESSION['pro_edit_message'])){
		echo '<br/><center><table id="info_message" cellspacing="0" width="220px"><tr><td valign="center"><img src="http://localhost/images/info_icon.png" width="22px"></td><td valign="center">'.$_SESSION['pro_edit_message'].'</td></tr></table></center>';
		unset($_SESSION['pro_edit_message']);
	}
	
	// Εκτύπωση του υποσέλιδου.		
	side_and_footer();
?>