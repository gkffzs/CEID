<?php
	// ������� ��� ��� �������� ������� ��� ����.
	function db_insert_comment($check_form_username, $check_form_comment_text, $check_form_picture_id, $check_form_date){
		mysql_query("	INSERT INTO comments (username, comment, picture_id, date)
						VALUES ('$check_form_username', '$check_form_comment_text', '$check_form_picture_id', '$check_form_date')")
					or die(mysql_error());  
	}
	
	// ������� ��� ������� ��� ���� ���������.
	function db_connect(){
		include("db_config.php");
	
		$db_connection = mysql_connect($db_host, $db_user, $db_pass)
						or die("��� ����������� � �������.");
						
		mysql_select_db("ekona", $db_connection) or die("��� ����������� � ������� �� ��� ������.");
			
		mysql_query('SET NAMES utf8');
	}
	
	// ������� ��� ��� ������ ������� �� �� �� ������� �� ����� ��� ������ ��� ���� ���������.
	function db_user_check($check_form_username){
		$result = mysql_query("	SELECT *
								FROM user 
								WHERE username='$check_form_username'")
							or die(mysql_error());  
										
		$user_num = mysql_num_rows($result);
		return $user_num;
	}

	// ������� ��� ��� ������ ������� �� �� �� ������� �� email ��� ���� ���������.
	function db_email_check($check_form_email){
		$result = mysql_query("	SELECT * 
								FROM user 
								WHERE email='$check_form_email'")
							or die(mysql_error());  
										
		$email_num = mysql_num_rows($result);
		return $email_num;
	}

	// ������� ��� ��� �������� ��� ��������� ���� ���� ������.
	function db_reg_input($check_form_username, $check_form_password, $check_form_email){
		mysql_query("	INSERT INTO user (username, password, email)
						VALUES ('$check_form_username', SHA1('$check_form_password'), '$check_form_email')")
					or die(mysql_error());  
	}
	
	// ������� ��� ��� ��������� ��� ������.
	function validate_user($username,$password){	
		$result = mysql_query("	SELECT * 
								FROM user
								WHERE username = '$username'
								AND password = '$password'")
							or die(mysql_error());
		
		$user_data = mysql_fetch_array($result);				
		return $user_data;
	}
	
	// ������� ��� �������� ��� ��������� ���� ������.
	function db_profile_update($form_user_id, $form_new_email, $form_new_password){
		mysql_query("	UPDATE user 
						SET email = '".$form_new_email."',
							password = '".SHA1($form_new_password)."'
						WHERE user_id=".$form_user_id)
					or die(mysql_error());
	}
	
	// ������� ��� ���������� ��� ���� ��� ������������ ���� �������.
	function quota(){
		$result = mysql_query("	SELECT quota 
								FROM user
								WHERE user_id={$_SESSION['user_id']}")
							or die(mysql_error());
	
		$row = mysql_fetch_array($result);
		return($row['quota']);			
	}
	
	// ������� ��� ��� �������� ��� ��������� ���� �����������.
	function db_picture_insert($picture_title, $picture_description, $picture_publication, $picture_geolocation, $session, $filename, $picture_size, $picture_tags, $lat, $lng){	
		$user_id = $_SESSION['user_id'];
		$quota = quota(); 		
		$quota_new = $quota+$picture_size;
		$strToken = strtok($picture_tags ,",");  
	
		mysql_query("	INSERT INTO picture (user_id, file_name, title, description, publication, geolocation, lat, lng) 
						VALUES ('$user_id', '$filename', '$picture_title', '$picture_description', '$picture_publication', '$picture_geolocation', '$lat', '$lng')")
					or die(mysql_error());  
	
		mysql_query("	UPDATE user
						SET quota = '$quota_new'
						WHERE user_id = '$user_id'")
					or die(mysql_error());  
	
		// ������� ������ ��� ��� �������� ��� ��������.		
		$result = mysql_query("	SELECT picture_id 
								FROM picture
								WHERE user_id = '$user_id'
								AND file_name = '$filename'")
							or die(mysql_error());  
										
		$row = mysql_fetch_array($result);
		$picture_id = $row['picture_id'];			

		while($strToken){
			// ������� ��� �� �� ������� � �������.
			$tag = trim($strToken);
			$result = mysql_query("	SELECT tag_name  
									FROM picture_tags
									WHERE tag_name = '$tag'")
								or die(mysql_error());	
								
			$num_rows = mysql_num_rows($result);
			
			// �� ��� ������� � �������, ��������� ��� ����.			
			if(!$num_rows > 0){ 
				mysql_query("	INSERT INTO picture_tags(tag_name, num_pictures)
								VALUES ('$tag', '1')")
							or die(mysql_error());  																			
			}else{	// ������, ��������� � ������� ����������� ���.
				mysql_query("	UPDATE picture_tags 
								SET num_pictures = num_pictures+1
								WHERE tag_name = '$tag'")
							or die(mysql_error());  
			}	
			
			$result = mysql_query("	SELECT tag_id 
									FROM picture_tags
									WHERE tag_name = '$tag'")
								or die(mysql_error());  										
			
			$row = mysql_fetch_array($result);
			$tag_id = $row['tag_id'];													
		
			mysql_query("	INSERT INTO picture_tagged(tag_id, picture_id) 
							VALUES ('$tag_id', '$picture_id')")
						or die(mysql_error()); 	
			
			$strToken=strtok(",");  		
		} 
	}
	
	
	// ������� ��� �������� ��� ��������� ���� �����������.
	function db_picture_update($form_title, $form_description, $form_publication, $form_geolocation, $login_session, $form_tags, $form_id, $form_lat, $form_lng){
		mysql_query("	UPDATE picture 
						SET title = '".$form_title."',
							description = '".$form_description."',
							geolocation = '".$form_geolocation."',
							publication = '".$form_publication."',
							lat = '".$form_lat."',
							lng = '".$form_lng."'
						WHERE picture_id=".$form_id)
					or die(mysql_error());
		
		$strToken = strtok($form_tags ,",");
		
		$result = mysql_query("	SELECT tag_id 
								FROM picture_tagged
								WHERE picture_id = '$form_id'")
							or die(mysql_error());
		
		while ($row = mysql_fetch_array($result)){
			$old_Photo_tags[] = $row['tag_id'];
		}
									
		while($strToken){   	
			$tag = trim($strToken);
		
			// ������� ��� ��� ������ ��� ��������� �������� ��� ���� ���������.					
			$result = mysql_query("	SELECT tag_name
									FROM picture_tags
									WHERE tag_name = '$tag'")
								or die(mysql_error());
			
			// �� �� $num_rows ���������� 0 ���� ��� ������� �� tag.
			$num_rows = mysql_num_rows($result);
			
			// �� ��� ������� � �������, ��������� ��� ����.
			if($num_rows==0){			
				mysql_query("	INSERT INTO picture_tags(tag_name, num_pictures)
								VALUES ('$tag', '1')")
							or die(mysql_error()); 
			}			
			
			$result = mysql_query("	SELECT tag_id
									FROM picture_tags
									WHERE tag_name = '$tag'")
								or die(mysql_error());
			
			$row = mysql_fetch_array($result); 
			$tag_id = $row['tag_id'];
			$new_Photo_tags[] = $tag_id;
			
			// ������� ��� �� �� ���� � ���������� ��� �������� �������		
			$result = mysql_query("	SELECT tag_id
									FROM picture_tagged
									WHERE tag_id = '$tag_id'
									AND picture_id = '$form_id'") 
								or die(mysql_error());	
													
			$tag_ok = mysql_num_rows($result); // ���� � ���������� ���� ��� �������;
				
			if(!$tag_ok > 0){
				mysql_query("	INSERT INTO picture_tagged(tag_id, picture_id) 
								VALUES ('$tag_id', '$form_id')")
							or die(mysql_error());  
			}
			
			$strToken=strtok(",");  		
		}
		
		// ����������� ��� �������� ������ �������� ��� �����������
		foreach($old_Photo_tags as $old){
			$delete_old = 1;

			foreach($new_Photo_tags as $new){
				if($old == $new){
					$delete_old = 0;
					break;
				}
			}
			
			if($delete_old == 1){
				echo 'ENTER DELETE for tag_id='.$old.' </br>';
				mysql_query("	DELETE FROM picture_tagged
								WHERE picture_id = '$form_id'
								AND tag_id = '$old'")
							or die(mysql_error());
										
				// ��������� � �������� ��������
				$result = mysql_query("	SELECT tag_id, 
										COUNT(picture_id) as Num_of_use
										FROM picture_tagged
										WHERE tag_id = '$old'")
									or die(mysql_error());
				
				$row = mysql_fetch_array($result); // ����� ����� ��������������� � �������;
				$num_pictures = $row['Num_of_use'];
				echo 'Number of pictures for '.$row['tag_id'].': '.$num_pictures.'<br/>'; 
				
				if($num_pictures > 0){
					mysql_query("	UPDATE picture_tags 
									SET num_pictures = '$num_pictures'
									WHERE tag_id = '$old'")
								or die(mysql_error());  
				} else {
					mysql_query("	DELETE FROM picture_tags 
									WHERE tag_id = '$old'")
								or die(mysql_error());
				}															
			}
		}				
	}
	
	// ������� ��� ��� ��������� ��� �������� ��� �������� �����������.
	function tag_info(){
		$result = mysql_query("	SELECT picture_tagged.tag_id
								FROM picture_tagged
								INNER JOIN picture
								ON picture_tagged.picture_id = picture.picture_id
								AND picture.publication = '1'")
							or die(mysql_error());
							
		while($row = mysql_fetch_array($result)){
			$public_tags[]= $row['tag_id'];
		}	
			
		foreach($public_tags as $p_tags){
				$result = mysql_query("	SELECT *
										FROM picture_tags 
										WHERE tag_id='$p_tags'
										GROUP BY tag_id 
										ORDER BY num_pictures DESC")
									or die(mysql_error());  
										
			while($row = mysql_fetch_array($result)) {
				$arr[$row['tag_name']] = $row['num_pictures'];
			}
		}
		
		ksort($arr);
		return $arr;
	}
	
	// ������� ��� ���������� �� ����� ��� ������� ��� �����������.
	function picture_file_name ($picture_id) {
		$result = mysql_query("	SELECT file_name 
								FROM picture
								WHERE picture_id = '$picture_id'")
							or die(mysql_error());
							
		$row = mysql_fetch_array($result);
		return $row['file_name'];
	}
	
	// ������� ��� ��� �������� ���� �����������.
	function image_delete() {
		$result = mysql_query("	SELECT tag_id
								FROM picture_tagged
								WHERE picture_id = '$form_id'")
							or die(mysql_error());
											
		// ���������� �� id ��� �������� ��� ����� ����������� �� ��� ����������.
		while($row = mysql_fetch_array($result)){ 
			$photo_tags_id[] = $row['tag_id'];
		}

		foreach($photo_tags_id as $tag_id){
			// ����� ����� ��������������� � �������.
			$result = mysql_query("	SELECT tag_id,
									COUNT(picture_id) as Num_of_use
									FROM picture_tagged
									WHERE tag_id = '$tag_id'")
								or die(mysql_error());  
												
			$row = mysql_fetch_array($result);
			$num_pictures = $row['Num_of_use'];
			$num_pictures--;
			
			// �� ��������������� � ������� ��� ���� �� �������� ��� ����������� �������� �� ��������.			
			if($num_pictures > 0){ 
				mysql_query("	UPDATE picture_tags 
								SET num_pictures = '$num_pictures'
								WHERE tag_id = '$tag_id'")
							or die(mysql_error());  
			} else {
				mysql_query("	DELETE FROM picture_tags 
								WHERE tag_id = '$tag_id'")
							or die(mysql_error());
			}
		}
		
		// �������� ��� �� �������� ��� ��� ����.	
		mysql_query("	DELETE FROM picture 
						WHERE picture_id = '$form_id'")
					or die(mysql_error()); 
			
		$quota = quota();
		$quota = $quota - $filesize;
		mysql_query("	UPDATE user
						SET quota = '$quota'
						WHERE user_id = {$_SESSION['user_id']}")
					or die(mysql_error());								
	}
	
	// ������� ��� ���������� ���� ��� �������� ��������.
	function public_tags() {
		$result = mysql_query("	SELECT DISTINCT picture_tags.tag_name
								FROM picture_tagged
								INNER JOIN picture
								ON picture_tagged.picture_id = picture.picture_id
								AND picture.publication = '1'
								INNER JOIN picture_tags
								ON picture_tagged.tag_id = picture_tags.tag_id
								ORDER BY picture_tags.num_pictures DESC")
							or die(mysql_error());
		
		while($row = mysql_fetch_array($result)){
			$public_tags[] = $row['tag_name'];
		}
		return $public_tags;
	}
	
	// ������� ��� ���������� ��� ������ ��� ����������� ��� ������.
	function user_num_pictures($user) {
		$result = mysql_query("	SELECT picture.picture_id 
								FROM picture 
								INNER JOIN user ON picture.user_id=user.user_id
								AND user.user_id='$user'")
							or die(mysql_error());
							
		$num_row = mysql_num_rows($result);
		return $num_row;
	}
	
	// ������� ��� ��������������� ��� ��� �������� ��� ��������� ���� ��� ����������� ��� ������.
	function user_pictures($user, $start, $display) {
		$result = mysql_query("	SELECT picture.picture_id, picture.user_id, picture.file_name, picture.title, picture.publication, picture.description, user.username
								FROM picture
								INNER JOIN user
								ON picture.user_id = user.user_id
								AND user.user_id='$user'
								ORDER BY picture_id
								ASC 
								LIMIT $start, $display")
							or die(mysql_error());
							
		return $result;
	}

	// ������� ��� ���������� �� ������ ��� �����������.
	function picture_comments($picture_id) {
		$result = mysql_query("	SELECT comment, username, date 
								FROM comments
								WHERE picture_id='$picture_id'")
							or die(mysql_error());
							
		return $result;
	}
	
	// ������� ��� ���������� ��� ��������� 10 �����������.
	function top_10() {
		$result = mysql_query("	SELECT picture.picture_id, picture.file_name, picture.user_id, user.username, picture.total_hits
								FROM picture
								INNER JOIN user
								ON picture.user_id=user.user_id
								WHERE picture.publication=1
								ORDER BY total_hits
								DESC LIMIT 10")
							or die(mysql_error());
							
		return $result;
	}
	
	// ������� ��� ���������� ����������� ���� ����������� �� ������������ id
	function image_info($picture_id) {
		$result = mysql_query("	SELECT picture.picture_id, picture.user_id, picture.file_name, picture.title, picture.publication, picture.description, user.username, picture.total_hits, picture.geolocation, picture.lat, picture.lng
								FROM picture
								INNER JOIN user
								ON picture.user_id=user.user_id
								WHERE picture.picture_id='$picture_id'")
							or die(mysql_error());
							
		$row = mysql_fetch_array($result);
		return $row;
	}
	
	// ������� ��� ���������� ��� �������� ���� �����������.
	function picture_tags($picture_id) {
		$tag_result = mysql_query("	SELECT picture_tags.tag_name
									FROM picture_tags
									INNER JOIN picture_tagged
									ON picture_tags.tag_id=picture_tagged.tag_id
									WHERE picture_tagged.picture_id='$picture_id'")
								or die(mysql_error());
								
		return $tag_result;
	}
	
	// ������� ��� ������� ��� ����������� ���� �����������.
	function increase_picture_hits($picture_id, $total_hits) {
		mysql_query("	UPDATE picture SET total_hits = '".$total_hits."' 
						WHERE picture_id=".$picture_id);
	}
	
	// ������� ��� ���������� �� id ��� ����������� ��� ����� ��������������� �� ��� ������� ��� �������� �� ������.
	function search_on_tags($strToken) {
		$result = mysql_query("	SELECT picture_tagged.picture_id 						
								FROM picture_tagged
								INNER JOIN picture_tags
								ON  picture_tags.tag_name LIKE '%$strToken%'
								AND picture_tags.tag_id = picture_tagged.tag_id")
							or die(mysql_error());
		return $result;		
	}
	
	function search_on_everyfield($strToken) {
		$result = mysql_query("	SELECT picture_tagged.picture_id AS pic_id		
								FROM picture_tagged
								INNER JOIN picture_tags
								ON  picture_tags.tag_name LIKE '%$strToken%'
								AND picture_tags.tag_id = picture_tagged.tag_id
								UNION 
								SELECT picture_id AS pic_id
								FROM picture
								WHERE title LIKE '%$strToken%'
								OR description LIKE '%$strToken%'")
							or die(mysql_error());
							
		return $result;
	}
	
	// ������� ��� ������� ���� ������ �� �� id ��� ����������� ��� ���������� ����������� ��� �����.
	function get_picture_info ($ar, $start, $display) {
		foreach($ar as $val){
			if(!isset($query)){
				$query = "	SELECT picture.picture_id, picture.title, picture.description, picture.publication, picture.file_name, user.username, picture.total_hits
							FROM picture
							INNER JOIN user ON picture.user_id=user.user_id
							WHERE picture.picture_id='$val'";	
			} else {
				$query = $query . " OR picture.picture_id='$val'";
			}
		}		
		$query = $query."	ORDER BY picture.total_hits
							DESC 
							LIMIT $start, $display";
		$result = mysql_query($query) or die(mysql_error());
		
		return $result;
	}	
?>