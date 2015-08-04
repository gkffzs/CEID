<?php
	// Συμπερίληψη του αρχείου db_functions.php για να υπάρχει η δυνατότητα κλήσης των μεθόδων του.
	include("../database_layer/db_functions.php");
	// Σύνδεση με τη βάση δεδομένων.
	db_connect();
	
	// Εκτύπωση του περιεχομένου του head.
	function head_content($tags_autocomplete){
		echo '		<script type="text/javascript" src="http://localhost/javascripts/jquery.min.js"></script>
					<script type="text/javascript" src="http://localhost/javascripts/javascript_functions.js"></script>
					<script type="text/javascript" src="http://localhost/javascripts/jquery.smart_autocomplete.js"></script>
					
					<script id="autocomplete-function" type="text/javascript">
						$(function(){
							$("#search_autocomplete").smartAutoComplete({source: "http://localhost/logic_layer/tags.php", maxResults: 5, delay: 200});
							
							$("#search_autocomplete").bind({
								keyIn: function(ev){
									var tag_list = ev.smartAutocompleteData.query.split(","); 
									//pass the modified query to default event
									ev.smartAutocompleteData.query = $.trim(tag_list[tag_list.length - 1]);
								},

								itemSelect: function(ev, selected_item){ 
									var options = $(this).smartAutoComplete();

									//get the text from selected item
									var selected_value = $(selected_item).text();
									var cur_list = $(this).val().split(","); 
									cur_list[cur_list.length - 1] = selected_value;
									$(this).val(cur_list.join(",") + ","); 

									//set item selected property
									options.setItemSelected(true);

									//hide results container
									$(this).trigger("lostFocus");
								  
									//prevent default event handler from executing
									ev.preventDefault();
								},
							});
						});
					</script>';
					
		if($tags_autocomplete==2){ // Λειτουργία autocomplete για την συμπλήρωση ετικετών κατά το ανέβασμα ή την επεξεργασία κάποιας εικόνας.
			echo '	<script type="text/javascript">
						$(function(){
							$("#tags_autocomplete").smartAutoComplete({source: "http://localhost/logic_layer/tags.php", maxResults: 5, delay: 200});
							
							$("#tags_autocomplete").bind({
								keyIn: function(ev){
									var tag_list = ev.smartAutocompleteData.query.split(","); 
									//pass the modified query to default event
									ev.smartAutocompleteData.query = $.trim(tag_list[tag_list.length - 1]);
								},

								itemSelect: function(ev, selected_item){ 
									var options = $(this).smartAutoComplete();

									//get the text from selected item
									var selected_value = $(selected_item).text();
									var cur_list = $(this).val().split(","); 
									cur_list[cur_list.length - 1] = selected_value;
									$(this).val(cur_list.join(",") + ","); 

									//set item selected property
									options.setItemSelected(true);

									//hide results container
									$(this).trigger("lostFocus");
								  
									//prevent default event handler from executing
									ev.preventDefault();
								},
							});
						});
					</script>';
		}
					
		echo '		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
					<link href="../css/styles.css" rel="stylesheet" type="text/css">
					<link rel="icon" type="image/png" href="../images/top_icon.png">
					<title>e-kona</title>
				</head>';
	}
	
	// Για τη λειτουργία του χάρτη.
	// #1
	function index_geolocation(){
		echo '	<script src="http://localhost/javascripts/geolocation.js"></script>
				<script src="http://maps.google.com/maps/api/js?sensor=false"></script>';
	}
	// #2
	function image_geolocation(){
		echo '	<script src="http://localhost/javascripts/image_geolocation.js"></script>
				<script src="http://maps.google.com/maps/api/js?sensor=false"></script>';
	}
		
	// Δύο μπάρες αναζήτησης στο πλευρικό μενού.
	function search_fields(){
		echo '	<table id="search_form" cellspacing="0" cellpadding="0">
					<tr>
					<form name="input" action="http://localhost/presentation_layer/search.php" method="get">
					<td valign="center"><textarea name="terms" id="simple_search" placeholder="Αναζήτηση..."></textarea>&ensp;</td>
					<td valign="center"><button type="submit" name="tags_search" value="0"/>>></button></td></form>
					</tr>
					<tr>
					<form name="input" action="http://localhost/presentation_layer/search.php" method="get">
					<td valign="center"><textarea name="terms" autocomplete="off" id="search_autocomplete" placeholder="Αναζήτηση στις ετικέτες..."></textarea>&ensp;</td>
					<td valign="center" width="8%"><button type="submit" name="tags_search" value="1"/>>></button></td></form>
					</tr>
				</table>';
	}
		
	// Εικόνα στο πάνω μέρος της σελίδας και λογότυπο.
	function top_image(){
		echo '	<div id="header">
					<div id="logo"><a href="http://localhost/presentation_layer/index.php"><img src="../images/logo.png" width="230px"></a></div>
				</div>';
	}

	// Μπάρα με μενού κάτω από την εικόνα.
	function menu_bar(){
		echo '<div id="main_menu">
				<table cellspacing="0" cellpadding="0"><tr>
					<td><a href="index.php">ΑΡΧΙΚΗ</a></td>
					<td><a href="http://localhost/presentation_layer/about.php">ΣΧΕΤΙΚΑ</a></td>
				</tr></table>
			</div>';
	}

	// Μενού χρηστών πριν & μετά τη σύνδεσή τους.
	function user_menu(){
		if(!isset($_SESSION['login_user'])){ // Χωρίς σύνδεση.
			echo '	<div id="log_form" style="padding-top: 1px;">
						<form method="POST" action="http://localhost/logic_layer/login.php" accept-charset="UTF-8" onSubmit="return confirm_login(this)">';
						
			if(isset($_SESSION['validation_log']) && $_SESSION['validation_log']=='false'){
				echo  '<font color="#A32900"><i>Λάθος όνομα χρήστη ή κωδικός! Εισάγετε εκ νέου τα στοιχεία σας.</i></font>&ensp;&ensp;&ensp;';
				unset($_SESSION['validation_log']);
			}
			
			echo '			ΟΝΟΜΑ ΧΡΗΣΤΗ <input type="text" name="username">&nbsp;
							ΚΩΔΙΚΟΣ <input type="password" name="password">
							<button type="submit" value="ΣΥΝΔΕΣΗ">ΣΥΝΔΕΣΗ</button>&ensp;
						</form>
					</div>';
			
			
		} else { // Με σύνδεση.
			echo'	<div id="log_form" style="padding-top: 5px; margin-bottom: -4px;"> 
						<form action="http://localhost/logic_layer/logout.php" method="post" name="logout"  accept-charset="UTF-8">
									<a href="http://localhost/presentation_layer/album.php">ALBUM</a>
									<a href="http://localhost/presentation_layer/upload.php">ΑΝΕΒΑΣΜΑ</a>
									<a href="http://localhost/presentation_layer/edit_profile.php">ΕΠΕΞΕΡΓΑΣΙΑ ΣΤΟΙΧΕΙΩΝ</a>&ensp;&ensp;
								Έχετε συνδεθεί ως '. $_SESSION['login_user'] .'.&ensp;<button type="submit" name="Submit" value="ΑΠΟΣΥΝΔΕΣΗ"/>ΑΠΟΣΥΝΔΕΣΗ</button>&ensp;
						</form>
					</div>';
		}
	}
	
	// Εκτύπωση του πάνω μέρους της σελίδας και του τίτλου.
	function body_header($title){
		echo '	<div id="main_body"><center>
				<br/><table width="980px" align="center" cellspacing="0">
					<tr><td width="710px" align="center" valign="top">
					<div id="main_header">'.$title.'</div><br/>';
	}
	
	// Εκτύπωση του tag cloud.
	function tag_cloud() {
		// Καθορισμός μικρότερου και μεγαλύτερου μεγέθους γραμματοσειράς.
		$min_size = 10;
		$max_size = 17;

		// Λήψη των ετικετών των δημόσιων εικόνων.
		$tags = tag_info();

		$minimum_count = min(array_values($tags));
		$maximum_count = max(array_values($tags));
		$spread = $maximum_count - $minimum_count;

		if($spread == 0) {
			$spread = 1;
		}

		$cloud_html = '';
		$cloud_tags = array();

		foreach ($tags as $tag => $count) {
			$size = $min_size + ($count - $minimum_count) * ($max_size - $min_size) / $spread;
			$cloud_tags[] = '<a style="font-size: '. floor($size) . 'px" class="tag_cloud" href="http://localhost/presentation_layer/search.php?tags_search=1&terms='.$tag.'" title="Η ετικέτα \''.$tag.'\' υπάρχει σε '.$count.' φωτογραφίες">'.htmlspecialchars(stripslashes($tag)).'</a>';
		}
 
		$cloud_html = join("\n", $cloud_tags) . "\n";
		return $cloud_html;
	}
	
	// Εκτύπωση σχολίων.
	function print_comments($picture_id) {
		$printed=0;
	
		$result = picture_comments($picture_id);

		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			echo '	<table id="comments" width="610px">
					<tr><th width="280px">' . $row["username"] . '</th><td align="right"><i>' . $row["date"] . '</i></td></tr>
					<tr><td colspan="2">' . $row["comment"] . '</td></tr></table>';
			$printed=1;
		}
		
		if($printed==1){
			echo '<br/>';
		}
	}
	
	// Εκτύπωση 10 δημοφιλέστερων φωτογραφιών.
	function top_10_images() {
								
		$result = top_10();
	
		echo '<table id="top_10_table" align="center" cellpadding="0" cellspacing="3">';
		echo '<tr>';
		
		$counter=0;
	
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			echo '<td align="center"><a class="thumbnail_top_10" href="image.php?id=' . $row['picture_id'] . '">
			<img src="http://localhost/users_album/' . $row['username'] . '/' . $row['file_name'].'" alt="'. $row['file_name'] .'" border="0"/></a></td>';
			
			if($counter<9){
				echo '<td bgcolor="black" width="2px"></td>';
				$counter++;
			}
		}
		echo '</tr></table><br/>';
	}
	
	// Εκτύπωση του header.
	function header_print($type, $title, $tags_autocomplete){
		echo '<html><head>';
		
		if($type==1){
			index_geolocation();
		} else if($type==2){
			image_geolocation();
		}
		
		head_content($tags_autocomplete);
		echo '<body>';
		top_image();
		menu_bar();
		user_menu();
		body_header($title);
	}
	
	// Εκτύπωση του πλευρικού μενού.
	function side_menu(){
		echo '	<table width="240px">
					<tr><td align="center" valign="center"><br/>';
					
		search_fields();
					
		echo '		</td></tr>
					<tr><td align="center"><br/>';
		
		if(!isset($_SESSION['login_user'])){
			echo '	<table id="register_form" border="0" cellspacing="0" width="246px">
						<form method="POST" action="../logic_layer/register.php" accept-charset="UTF-8" onSubmit="return confirm_register(this)">
							<tr><th colspan="2">ΕΓΓΡΑΦΗ</th></tr>
							<tr><td colspan="2">&ensp;</td></tr>
							<tr><td>ΟΝΟΜΑ</td><td align="right"><input type="text" name="username" size="15"></td></tr>
							<tr><td>EMAIL</td><td align="right"><input type="text" name="email" size="15"></td></tr>
							<tr><td>ΚΩΔΙΚΟΣ</td><td align="right"><input type="password" name="password" size="15"></td></tr>
							<tr><td>ΕΠΙΒΕΒΑΙΩΣΗ</td align="right"><td align="right"><input type="password" name="password_val" size="15"></td></tr>
							<tr><td align="right" colspan="2"><button type="submit" value="ΕΓΓΡΑΦΗ"/>ΕΓΓΡΑΦΗ</button>&ensp;</td></tr>
							<tr><td colspan="2">&ensp;</td></tr>
						</form>
					</table>';
			
			if(isset($_SESSION["message_reg"])){
				echo '<br/><center><table id="info_message" cellspacing="0" width="220px"><tr><td valign="center"><img src="http://localhost/images/info_icon.png" width="22px"></td><td valign="center">'.$_SESSION["message_reg"].'</td></tr></table></center>';
				unset($_SESSION['message_reg']);
			}
		} else {
			$quota = quota();
			$percentage=(100*$quota)/52428800;
			$round_percentage=round($percentage, 2);

			echo '	<table width="240px" class="graph"><tr>
						<td><img src="../images/space_usage_icon.png" width="15px"></td><td><b>'.$round_percentage.'%</b></td>
						<td class="bar"><div style="width: '.$round_percentage.'%"></div></td>
					</tr></table>';
		}
		
		echo '</td></tr><tr><td align="center"><br/><div id="wrapper">';
		
		print tag_cloud(); 
		
		echo '</div><br/></td></tr></table>';
	}
	
	// Εκτύπωση του πλευρικού μενού και του footer.
	function side_and_footer(){
		echo '			</td>
						<td bgcolor="black" width="1px"></td>
						<td align="center" valign="top" bgcolor="#D3A77E">';
	
		side_menu();
		
		echo '			</td></tr>
					</table></center></br>
				</div>
				<div id="footer">ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΚΑΙ ΣΥΣΤΗΜΑΤΑ ΣΤΟΝ ΠΑΓΚΟΣΜΙΟ ΙΣΤΟ &bull; PROJECT 2012<br/>
					<a href="http://www.ceid.upatras.gr/">ΤΜΗΜΑ ΜΗΧΑΝΙΚΩΝ Η/Υ & ΠΛΗΡΟΦΟΡΙΚΗΣ</a><br/>
					<a href="mailto:magripis@ceid.upatras.gr">magripis</a> &bull; <a href="mailto:kaffezas@ceid.upatras.gr">kaffezas</a> &bull; <a href="mailto:siaflekis@ceid.upatras.gr">siaflekis</a>
				</div>
			</body>
		</html>';
	}
?>