// Μέθοδος για την εμφάνιση του χάρτη.
function display_map(){
	// Προσδιορισμός των χαρακτηριστικών του χάρτη.
	var myOptions={
		zoom: 12,
		center: latlng,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	
	// Δημιουργία του χάρτη και ενός infoWindow.
	var map=new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	var infoWindow = new google.maps.InfoWindow;
	
	// Κάλεσμα μεθόδου για την εισαγωγή των στοιχείων των δημόσιων φωτογραφιών από ένα αρχείο XML.
	downloadUrl("gen_xml.php", function(data) {
		var xml = data.responseXML;
		var markers = xml.documentElement.getElementsByTagName("marker");
	
		for (var i=0; i < markers.length; i++) {
			var file_name = markers[i].getAttribute("file_name");
			var pic_id = markers[i].getAttribute("pic_id");
			var username = markers[i].getAttribute("username");
			var point = new google.maps.LatLng(
				parseFloat(markers[i].getAttribute("lat")),
				parseFloat(markers[i].getAttribute("lng")));
			var html = "<a href='http://localhost/presentation_layer/image.php?id=" + pic_id + "'><img src='http://localhost/users_album/" + username + "/"+ file_name +"' width='100px' height='100px'></a>";
			var marker = new google.maps.Marker({
				map: map,
				position: point,
				icon: 'http://localhost/images/icon_map.png'
			});
			
			// Σύνδεση marker με infoWindow.
			bindInfoWindow(marker, map, infoWindow, html);
		}
	});
}

// Μέθοδος για την λήψη στοιχείων από αρχείο XML.
function downloadUrl(url, callback) {
	var request = window.ActiveXObject ?
		new ActiveXObject('Microsoft.XMLHTTP') :
		new XMLHttpRequest;

	request.onreadystatechange = function() {
		if (request.readyState == 4) {
			request.onreadystatechange = doNothing;
			callback(request, request.status);
		}
	};

	request.open('GET', url, true);
	request.send(null);
}

// Μέθοδος για την ένωση marker και infoWindow.
function bindInfoWindow(marker, map, infoWindow, html) {
	google.maps.event.addListener(marker, 'click', function() {
		infoWindow.setContent(html);
		infoWindow.open(map, marker);
	});
}

// Κενή μέθοδος.
function doNothing() {}

var latlng;

// Έλεγχοι για τον προσδιορισμό της τοποθεσίας του κέντρου του χάρτη.
if (navigator.geolocation){
	function displayPosition(position) {
		latlng=new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
		display_map();
	}

	function errorFunction(position){
		latlng=new google.maps.LatLng(38.247482, 21.733662); // Συντεταγμένες της Πάτρας.
		display_map();
	}

	navigator.geolocation.getCurrentPosition(displayPosition, errorFunction);
}else{
	latlng=new google.maps.LatLng(38.247482, 21.733662); // Συντεταγμένες της Πάτρας.
	display_map();
}
