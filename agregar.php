<?php
  include("conectar.php");

  $sql = "INSERT INTO `valores`(`temperatura`,`humedad`,`polvo`) VALUES ('" . $_GET['temperatura'] . "','" . $_GET['humedad'] . "','" . $_GET['polvo'] . "')";

  if ($mysqli->query($sql) === TRUE) {
      echo "Data insert correctamente";
  } else {
    echo "Error: " . $sql . "<br>" . $mysqli->error;
  } 

  $mysqli->close();
?>
