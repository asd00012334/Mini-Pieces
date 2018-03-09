<?php
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
while($row = mysql_fetch_assoc($content)){
	echo $row['username'].': '.
		$row['word'].'...at '.$row['time'].'<br/>';
}
mysql_close($link);
?>
