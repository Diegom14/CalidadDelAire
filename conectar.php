<?php
  
    DEFINE('DB_USERNAME', 'arduino');
    DEFINE('DB_PASSWORD', 'password');
    DEFINE('DB_HOST', 'localhost');
    DEFINE('DB_DATABASE', 'sensores');

    $mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_DATABASE);

    if (mysqli_connect_error()) {
      die('Connect Error ('.mysqli_connect_errno().') '.mysqli_connect_error());
    }


  //echo 'Connected successfully.';
//  $mysqli->close();
?>
