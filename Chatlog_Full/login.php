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
	<?php
	    $usr = $_GET['username'];
		$msg = $_GET['msg'];
		if(strlen($usr)==0){
			$usr='anonymous';
			$upd=1;
		} else{
			$upd = $_GET['upd'];
		}
		error_reporting(0);
		$servername = 'dbhome.cs.nctu.edu.tw';
	    $username = 'huangyh9999_cs';
		$password =  'password';
	    $dbname = 'huangyh9999_cs';
	    $link = mysql_connect($servername,$username,$password) or
	        die('Fail to connect: '.mysql_error(0));
	    mysql_select_db($dbname) or die('Fail to select database');
		$content=mysql_query("SELECT * FROM Chat WHERE time<now()") or
			die('Fail to select');
		if($upd==0){
			mysql_query("INSERT INTO Chat values('$usr',now(),'$msg')") or
				die('Fail to insert');
		} else if($upd==2){
			mysql_query("INSERT INTO Chat values('$usr',now(),'$msg')") or
				die('Fail to insert');
			$upd=1;
		}
		mysql_close($link);
	?>
	<h1>Greetings, <?php echo $usr ?></h1>
	<div id='mainLog'>
		<!--<table type='text' id='mainLog'> -->
		<?php
			while($row = mysql_fetch_assoc($content)){
				//echo '<tr>';
				echo $row['username'].': '.
					$row['word'].'...at '.$row['time'].'<br/>';
				//echo '</tr>';
			}
		?>
		<!--</table>-->
		<form action='login.php'>
			<input type='hidden' name='username' value="<?php echo $usr;?>">
			<input type='hidden' name='upd' value='2'>
			<input
				name='msg'
				type='text'
				id='chatInput'
				oninput='save(this);'>
			<script>
				chatInput = document.getElementById('chatInput');
				chatInput.value=getSavedValue('chatInput');
				//chatInput.disabled=false;
				chatInput.focus();
				function submit(){
					console.log('onsubmit');
					localStorage.clear();//removeItem('chatInput');
					chatInput.value='';
				}
				function save(elem){
					localStorage.setItem(elem.id, elem.value);
				}
				function getSavedValue(id){
					if(localStorage.getItem(id)===null) return '';
					else return localStorage.getItem(id);
				}
			</script>
			<button id='sendButton' type='submit'>Send</button>
		</form>

	</div>
		
	<script>
	function update(){
		scrUpdate();
		location.replace('login.php?'+
			'username='+'<?php echo $usr;?>'+'&'+
			'msg='+'<?php echo $msg;?>'+'&'+
			'upd='+'1');
	}
	function getScrollTop(){
		if(localStorage.getItem('scrPos')===null)
			return document.body.scrollTop;
		else return localStorage.getItem('scrPos');
	}
	function scrUpdate(){
		localStorage.setItem('scrPos',document.body.scrollTop);
	}
	function load(){
		window.onscroll = scrUpdate;
		document.body.scrollTop=getScrollTop();
		setTimeout(update,1000);
	}
	window.onload=load
	</script>

</body>
</html>
