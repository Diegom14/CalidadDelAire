<?php
session_start();
?>

<?php

$host_db = "localhost";
$user_db = "arduino";
$pass_db = "password";
$db_name = "sensores";
$tbl_name = "login";

$conexion = new mysqli($host_db, $user_db, $pass_db, $db_name);

if ($conexion->connect_error) {
 die("La conexion falló: " . $conexion->connect_error);
}

$username = $_POST['username'];
$password = $_POST['password'];
 
$sql = "SELECT * FROM $tbl_name WHERE usuario = '$username'";

$result = $conexion->query($sql);


if ($result->num_rows > 0) {     
 }
 
echo "<br><br><a href=seleccion.html>ENTRAR</a>"; 

 
 mysqli_close($conexion); 
 ?>
