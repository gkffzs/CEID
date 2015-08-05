<?php
	// Συμπερίληψη του αρχείου db_functions.php για να υπάρχει η δυνατότητα κλήσης των μεθόδων του.
	include("../database_layer/db_functions.php");
	// Σύνδεση με τη βάση δεδομένων.
	db_connect();
	
	// Μέθοδος για τη μετατροπή των δεδομένων σε μορφή XML.
	function parseToXML($htmlStr) { 
		$xmlStr=str_replace('<','&lt;',$htmlStr); 
		$xmlStr=str_replace('>','&gt;',$xmlStr); 
		$xmlStr=str_replace('"','&quot;',$xmlStr); 
		$xmlStr=str_replace("'",'&#39;',$xmlStr); 
		$xmlStr=str_replace("&",'&amp;',$xmlStr); 
		return $xmlStr; 
	} 
	
	// Εύρεση όλων των δημόσιων φωτογραφιών.
	$query = "	SELECT * FROM picture
				WHERE publication=1";
				
	$result = mysql_query($query);
	
	if (!$result) {
		die('Invalid query: ' . mysql_error());
	}

	// Προσδιορισμός του αρχείου που δημιουργείται.
	header("Content-type: text/xml");

	// Εκτύπωση των δεδομένων σε μορφή XML με κλήση της μεθόδου parseToXML.
	echo '<markers>'; 

	while ($row = @mysql_fetch_assoc($result)){
		echo '<marker ';
		echo 'file_name="' . parseToXML($row['file_name']) . '" ';
		echo 'pic_id="'.parseToXML($row['picture_id']).'" ';
		
		$temp_user_id = parseToXML($row['user_id']);
		$user_result = mysql_query("SELECT username FROM user
					WHERE user_id='$temp_user_id'");
		$username = mysql_fetch_assoc($user_result);

		echo 'username="' . parseToXML($username['username']) . '" ';
		echo 'lat="' . $row['lat'] . '" ';
		echo 'lng="' . $row['lng'] . '" ';
		echo '/>';
	}

	echo '</markers>';
?>
