// Ελεγχος κατά την εγγραφή ενός χρήστη.
function confirm_register(form){
	if(form.username.value==""){
		alert("Παρακαλούμε εισάγετε ένα όνομα χρήστη.");
		return false;
	}
	
	if(form.email.value==""){
		alert("Παρακαλούμε εισάγετε μια διεύθυνση email.");
		return false;
	}
	
	if(form.password.value==""){
		alert("Παρακαλούμε εισάγετε έναν κωδικό.");
		return false;
	}
}

// Έλεγχος κατά την σύνδεση ενός χρήστη.
function confirm_login(form){
	if(form.username.value==""){
		alert("Παρακαλούμε εισάγετε ένα όνομα χρήστη.");
		return false;
	}
	
	if(form.password.value==""){
		alert("Παρακαλούμε εισάγετε έναν κωδικό.");
		return false;
	}
}

// Έλεγχος για τα σχόλια.
function confirm_comment(form){
	if(form.comment_text.value==""){
		alert("Το σχόλιό σας είναι κενό. Παρακαλούμε εισάγετε ένα αποδεκτό σχόλιο.");
		return false;
	}
}

// Έλεγχος για το ανέβασμα.
function confirm_upload(form){
	if(form.file.value==""){
		alert("Παρακαλούμε επιλέξτε ένα αρχείο για ανέβασμα.");
		return false;
	}
}

// Έλεγχος για την επεξεργασία των στοιχείων του χρήστη.
function confirm_profile_edit(form){
	if(form.new_email.value==""){
		alert("Παρακαλούμε εισάγετε μια διεύθυνση email.");
		return false;
	}
	
	if(form.new_password.value==""){
		alert("Παρακαλούμε εισάγετε έναν νέο κωδικό.");
		return false;
	}
	
	if(form.old_password.value==""){
		alert("Παρακαλούμε εισάγετε τον παλιό σας κωδικό για επιβεβαίωση.");
		return false;
	}
}

// Έλεγχος για τα στοιχεία μιας φωτογραφίας.
function confirm_pic_data(form){
	if(form.title.value==""){
		alert("Παρακαλούμε εισάγετε έναν τίτλο φωτογραφίας.");
		return false;
	}
	
	if(form.description.value==""){
		alert("Παρακαλούμε εισάγετε μια περιγραφή για τη φωτογραφία.");
		return false;
	}
	
	if(form.tags.value==""){
		alert("Παρακαλούμε βάλτε μία τουλάχιστον ετικέτα.");
		return false;
	}
}

// Έλεγχος για το checkbox και το autocomplete των ετικετών κατά την αναζήτηση.
function check_checkbox(check){
	if(check.checked==1){
		alert("Το autocomplete λειτουργεί.");
	} else if (check.checked==0) {
		alert("Το autocomplete δε λειτουργεί.");
	}
}

// Κώδικας για σμίκρυνση φωτογραφίας αν το μήκος της ξεπερνά τα 600 pixel.
function resize(img){
	if(img.width>606){
		img.style.height=parseInt(img.height*606/img.width);
		img.style.width=606;
	}

	img.style.position="static";
	img.style.visibility="visible";
}