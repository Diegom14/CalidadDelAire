<?php
 
 try{
     $conn = new PDO('mysql:host= '127.0.0.1' ;dbname=sensores','usuario','pass');
     echo 'Conexion realizada';
    }            
catch (PDOException $ex) {
       echo $ex->getMessage();
       exit;
    }
 
/* @var $_POST type */
$nombre= $_POST["txtusuario"];
$pass= $_POST["txtpassword"];

 
 $query=("SELECT usuario,pass FROM `login` "
         . "WHERE `usuario`='".mysql_real_escape_string($nombre)."' and "
         . "`pass`='".mysql_real_escape_string($pass)."'"); 

$rs= mysql_query($query); 
$row=mysql_fetch_object($rs); 
$nr = mysql_num_rows($rs);


if($nr == 0){ 
   
echo 'No ingreso'; 
} 

else if($nr == 1	) {    
     
     header("Location:index.html"); 
}   

?>
