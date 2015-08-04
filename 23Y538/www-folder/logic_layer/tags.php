<?php
	include("../database_layer/db_functions.php");
	db_connect();
	
	// Πάιρνουμε όλες τις δημόσιες ετικέτες απο την βάση δεδομένων, και τις τοποθετούμε σε ένα string σε μορφή λίστας, 
	// για να χρησιμοποιηθεί για το autocomplete.
	$public_tags = public_tags();
	
	$i = 0;
	$c = count($public_tags);
	
	echo '[';
	
	foreach($public_tags as $tag){
		if($i++ < $c -1 ){
			echo '"'.$tag.'",';
		}
		else echo '"'.$tag.'"';
	}	
	
	echo ']';
?>