// ������� ��� ��� �������� ��� �����.
function display_map(){
	// ������������� ��� ��������������� ��� �����.
	var myOptions={
		zoom: 13,
		center: latlng,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	
	// ���������� ��� �����.
	var map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	// ���������� ��� marker.
	var marker=new google.maps.Marker({
		 position: latlng, 
		 map: map
	});
	
	// ���������� ������������ �� ���� ���� ���� �����.
	google.maps.event.addListener(map, 'click', function (event) {
		document.getElementById("latbox").value = event.latLng.lat();
		document.getElementById("lngbox").value = event.latLng.lng();
		marker.setPosition(event.latLng);
	});
}

var latlng;

// ������� ��� ��� ������������ ��� ���������� ��� ������� ��� �����.
if (navigator.geolocation){
	function displayPosition(position) {
		latlng=new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
		display_map();
	}

	function errorFunction(position){
		latlng=new google.maps.LatLng(38.247482, 21.733662); // ������������� ��� ������.
		display_map();
	}

	navigator.geolocation.getCurrentPosition(displayPosition, errorFunction);
}else{
	latlng=new google.maps.LatLng(38.247482, 21.733662); // ������������� ��� ������.
	display_map();
}