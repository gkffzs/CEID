// Μέθοδος για την εμφάνιση του χάρτη.
function display_map(){
	// Προσδιορισμός των χαρακτηριστικών του χάρτη.
	var myOptions={
		zoom: 13,
		center: latlng,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	
	// Δημιουργία του χάρτη.
	var map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	// Δημιουργία του marker.
	var marker=new google.maps.Marker({
		 position: latlng, 
		 map: map
	});
	
	// Διαχείριση συμπεριφοράς με κλικ πάνω στον χάρτη.
	google.maps.event.addListener(map, 'click', function (event) {
		document.getElementById("latbox").value = event.latLng.lat();
		document.getElementById("lngbox").value = event.latLng.lng();
		marker.setPosition(event.latLng);
	});
}

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
