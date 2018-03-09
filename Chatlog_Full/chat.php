<html>
<head>
	<style>
	#mainLog{
		background-color: black;
		color: lime;
		font-size: 20px;
		font: Microsoft JhengHei;
		text-align: left;
		margin: 0px;
		width: 100%;
		//height: 80%;
	}
	#chatInput{
		background-color: gray;
		color: lime;
		font-size: 15px;
		font: Microsoft JhengHei;
		width: 93%;
		float: left;
		align: bottom;
		padding: 0px;
	}
	#sendButton{
		//margin: 0px;
		width: 7%;
		//float: left;
		//padding: 0px;
	}	
	</style>
</head>
<body>
	<h1>Welcome, <?php
		//error_reporting(0);
		$usr = strip_tags($_GET['usr']);
		if($usr=='') $usr = 'anonymous';
		else{	
			$servername = 'dbhome.cs.nctu.edu.tw';
	    	$username = 'huangyh9999_cs';
			$password =  'password';
	    	$dbname = 'huangyh9999_cs';
	    	try{
				$conn = new PDO("mysql:host=$servername;dbname=$dbname",
					$username,$password);
				$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
				$conn->prepare("INSERT INTO Chat values(?,now(),'login')")
					->execute(array($usr));
				$conn=null;
			} catch(PDOException $e){
				die('Fail to connect');
			}
		}
		echo $usr;
	?></h1>
	<div>
	<div id='mainLog'></div>
	<div>
		<input type='text' id='chatInput' name='msg'
			onkeydown="if(event.keyCode==13) submit();">
		<button id='sendButton' onclick='submit();'>Enter</button>
	</div>
	</div>
	<script>
	usr = "<?php echo $usr;?>";
	chatLog = document.getElementById('mainLog');
	function submit(){
		var msg = document.getElementById('chatInput').value;
		if(msg.length==0) return;
		var xhttp = new XMLHttpRequest();
		query = 'msg='+msg+'&usr='+usr;
		xhttp.open('GET','submit.php?'+query,true);
		xhttp.send();
		document.getElementById('chatInput').value='';
	}
	function update(){
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function(){
			if(this.readyState==4 && this.status==200){
				chatLog.innerHTML = this.responseText;
			}
		}
		xhttp.open('GET','refresh.php',true);
		xhttp.send();
		setTimeout(update,1000);
	}
	
	window.onload=update;
	</script>

</body>
</html>
