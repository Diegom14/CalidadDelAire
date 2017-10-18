<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysql_query("SELECT * FROM `sensores` ORDER BY `tiempo` DESC",$link);
?>

<html>
   <head>
      <title>Datos de Sensores</title>
   </head>
<body>
   <h1>Lecturas de temperatura, humedad y concentracion de polvo.</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Tiempo&nbsp;</td>
			<td>&nbsp;Temperatura 1&nbsp;</td>
			<td>&nbsp;Humedad 1&nbsp;</td>
      <td>&nbsp;Concentracion 1&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["tiempo"], $row["temperatura"], $row["humedad"], $row["concentracion"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
