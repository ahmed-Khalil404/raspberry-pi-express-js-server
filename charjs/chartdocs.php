<!DOCTYPE html>
<html>
	<head>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.3/Chart.min.js"></script>
		<link rel="stylesheet" type="text/css" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
	</head>
<body>

<h1 class="center">Hardware IOT Project</h1>

<table class="center" width="230px" border="1">

	<tr>
		<td  width="100px"><b>Température: </b></td>
		<td  width="50px"><b id="temp"></b></td>
		<td  width="100px"><b> °C </b></td>

	</tr>

	<tr>
		<td width="100px"><b>Humidité: </b></td>
		<td width="50px"><b id="humid"></b></td>
		<td width="100px"><b> % </b></td>
	</tr>

	<tr>
		<td width="100px"><b>Angle x: </b></td>
		<td width="50px"><b id="x"></b></td>
		<td width="100px"><b> rad </b></td>
	</tr>

	<tr>
		<td  width="100px"><b>Angle y: </b></td>
		<td  width="50px"><b id="y"></b></td>
		<td  width="100px"><b> rad </b></td>
	</tr>
	<tr>
		<td  width="100px"><b>Angle z: </b></td>
		<td  width="50px"><b id="z"></b></td>
		<td  width="100px"><b> rad </b></td>
	</tr>


</table>


<table width="80%" >

	<tr>
		<td  width="33%"><canvas id="tempChart"></canvas></td>
		<td  width="33%"><canvas id="humidChart"></canvas></td>
	</tr>
	<tr>
		<td  width="33%"><b>Température</b></td>
		<td  width="33%"><b>Humidite</b></td>
	</tr>
</table>

<table width = 100%>
	<tr>
	<td  width="34%"><canvas id="xChart"></canvas></td>
	<td  width="34%"><canvas id="yChart"></canvas></td>
	<td  width="34%"><canvas id="zChart"></canvas></td>
	</tr>
	<tr>
	<td  width="34%"><b>angle x</b></td>
	<td  width="34%"><b>angle y</b></td>
	<td  width="34%"><b>angle z</b></td>

	</tr>

</table>

	


</body>
</html>


<script>

var maxValues=5;
var tempUpdateCount=0;
var humidUpdateCount=0;
var xUpdateCount=0;
var yUpdateCount=0;
var zUpdateCount=0;



	let tempChartDisplay=document.getElementById('tempChart').getContext('2d');
	tempConfig={
		type:'line',
		data:{
			datasets:[{
				label:"Temperature",
				data:[],
				backgroundColor:'red'

				}],

		},
		options:{}
	}

	let temperatureChart= new Chart(tempChartDisplay,tempConfig) ; 



humidConfig={
		type:'line',
		data:{
			datasets:[{
				label:"humidite",
				data:[
				],
				backgroundColor:'blue',
				
			}],

		},
		options:{}
	}

	let humidChart= new Chart(document.getElementById('humidChart').getContext('2d'),humidConfig) ;
	
	xConfig={
		type:'line',
		data:{
			datasets:[{
				label:"Angle x",
				data:[
				],
				backgroundColor:'gold',
				fill:'true'
			}],

		},
		options:{}
	}

	let xChart= new Chart(document.getElementById('xChart').getContext('2d'),xConfig) ;


	yConfig={
		type:'line',
		data:{
			datasets:[{
				label:"y",
				data:[
				],
				backgroundColor:'pink',
				fill:'true'
			}],

		},
		options:{}
	}

	let yChart= new Chart(document.getElementById('yChart').getContext('2d'),yConfig) ;


	zConfig={
		type:'line',
		data:{
			datasets:[{
				label:"z",
				data:[
				],
				backgroundColor:'silver',
				fill:'false'
			}],

		},
		options:{}
	}

	let zChart= new Chart(document.getElementById('zChart').getContext('2d'),zConfig) ;
</script>



<script>


function updateTempChart(newValue){
	let today = new Date();
	tempConfig.data.labels.push(today.getHours() 
	    			+ ":" + today.getMinutes()
	    			+" : "+today.getSeconds());

				tempConfig.data.datasets.forEach(function(dataset) {
						
						dataset.data.push(newValue);
					});

				if(tempUpdateCount>maxValues){
					temperatureChart.data.labels.shift();
					temperatureChart.data.datasets[0].data.shift();
				}
				else
					tempUpdateCount++;
				temperatureChart.update();
}



function updateHumidChart(newValue){
	let today = new Date();
	humidConfig.data.labels.push(today.getHours() 
	    			+ ":" + today.getMinutes()
	    			+" : "+today.getSeconds());

				humidConfig.data.datasets.forEach(function(dataset) {
						
						dataset.data.push(newValue);
					});

				if(humidUpdateCount>maxValues){
					humidChart.data.labels.shift();
					humidChart.data.datasets[0].data.shift();
				}
				else
				humidUpdateCount++;
				humidChart.update();
}

function updatexChart(newValue){
	let today = new Date();
	xConfig.data.labels.push(today.getHours() 
	    			+ ":" + today.getMinutes()
	    			+" : "+today.getSeconds());

				xConfig.data.datasets.forEach(function(dataset) {
						
						dataset.data.push(newValue);
					});

				if(xUpdateCount>maxValues){
					xChart.data.labels.shift();
					xChart.data.datasets[0].data.shift();
				}
				else
				xUpdateCount++;
				xChart.update();
}

function updateyChart(newValue){
	let today = new Date();
	yConfig.data.labels.push(today.getHours() 
	    			+ ":" + today.getMinutes()
	    			+" : "+today.getSeconds());

					yConfig.data.datasets.forEach(function(dataset) {
						
						dataset.data.push(newValue);
					});

				if(yUpdateCount>maxValues){
					yChart.data.labels.shift();
					yChart.data.datasets[0].data.shift();
				}
				else
				yUpdateCount++;
				yChart.update();
}
function updatezChart(newValue){
	let today = new Date();
	zConfig.data.labels.push(today.getHours() 
	    			+ ":" + today.getMinutes()
	    			+" : "+today.getSeconds());

					zConfig.data.datasets.forEach(function(dataset) {
						
						dataset.data.push(newValue);
					});

				if(zUpdateCount>maxValues){
					zChart.data.labels.shift();
					zChart.data.datasets[0].data.shift();
				}
				else
				zUpdateCount++;
				zChart.update();
}

	function loadDoc(link,id) {
		
		
		


	  var xhttp = new XMLHttpRequest();
	  xhttp.onreadystatechange = function() {
	    if (this.readyState == 4 && this.status == 200) {
	    	var s = this.responseText;
	    	var result;
	    	if (s.indexOf('.')>0)
	    		result=s.split('.')[0]+"."+s.split('.')[1].substring(0,2);
	    	else 
	    		result=s;


		//Refresh charts
	    	if(id=="temp"){
	    		updateTempChart(result);
	    	}
	    	if(id=="humid"){
	    		updateHumidChart(s);
	    	}
			if(id=="x"){
	    		updatexChart(s);
	    	}
			if(id=="y"){
	    		updateyChart(s);
	    	}
			if(id=="z"){
	    		updatezChart(s);
	    	}


		document.getElementById(id).innerHTML = result;


	    }
	  };
	  xhttp.open("GET", link, true);
	  xhttp.send();
	}

	setInterval(function(){
	    loadDoc("http://127.0.0.1:3000/getTemp","temp")
	}, 800);



	setInterval(function(){
	    loadDoc("http://127.0.0.1:3000/getHumid","humid")
	}, 2000);

	setInterval(function(){
	    loadDoc("http://127.0.0.1:3000/getx","x")
	}, 2000);

	setInterval(function(){
	    loadDoc("http://127.0.0.1:3000/gety","y")
	}, 2000);

	setInterval(function(){
	    loadDoc("http://127.0.0.1:3000/getz","z")
	}, 2000);
	

	///
	
</script>
