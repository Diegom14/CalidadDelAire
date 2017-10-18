<?php
   	include("connect.php");
   	
   	$link=Connection();

	$temp=$_POST["temp"];
	$humedad=$_POST["humedad"];
  $dustConc=$_POST["dustConc"];

	$query = "INSERT INTO `sensores` (`temperatura`, `humedad`.`concentracion`) 
		VALUES ('".$temp."','".$humedad."','".$dustConc."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
