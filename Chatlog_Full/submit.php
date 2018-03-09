<?php
$usr = strip_tags($_GET['usr']);
$msg = strip_tags($_GET['msg']);
error_reporting(0);

$servername = 'dbhome.cs.nctu.edu.tw';
$username = 'huangyh9999_cs';
$password =  'password';
$dbname = 'huangyh9999_cs';
try{
	$conn = new PDO("mysql:host=$servername;dbname=$dbname",$username,$password);
	$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$conn->prepare("INSERT INTO Chat values(?,now(),?)")
		->execute(array($usr,$msg));
	$conn=null;
} catch(PDOException $e){
	die('Fail to connect');
}
?>
