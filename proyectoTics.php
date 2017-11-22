<?php
    // Importamos la configuración
    require("config.php");
    // Leemos los valores que nos llegan por GET
    $valor1 = mysqli_real_escape_string($con, $_GET['temperatura']);
    $valor2 = mysqli_real_escape_string($con, $_GET['humedad']);
    $valor3 = mysqli_real_escape_string($con, $_GET['polvo']);

    // Esta es la instrucción para insertar los valores
    $query = "INSERT INTO valores(temperatura, humedad, polvo) VALUES('".$valor1."', '" .$valor2."', '".$valor3."')";
    // Ejecutamos la instrucción
    mysqli_query($con, $query);
    mysqli_close($con);
?>
