<?php
  header("refresh: 4;");
  include("conectar.php");

  $sql2 = "SELECT * FROM `valores` ORDER BY `tiempo` DESC LIMIT 10";
  $result2 = $mysqli->query($sql2);
    

    /*if ($result2) {
      echo "data leida";
    } else {
      echo "Error: " . $sql2 . "<br>" . $mysqli->error;
    } */

  
?>

<?php
  //header("refresh: 15;");
  include("conectar.php");

  $sql = "SELECT tiempo, temperatura, humedad, polvo FROM `valores` ORDER BY `tiempo` DESC LIMIT 50";
    $result = $mysqli->query($sql);
    /*if ($result) {
      echo "data leida";
    } else {
      echo "Error: " . $sql . "<br>" . $mysqli->error;
    } */
	
	$rawdata = array();
    //guardamos en un array multidimensional todos los datos de la consulta
    $i=0;
    while($row = $result->fetch_assoc())
    {   
            //guardamos en rawdata todos los vectores/filas que nos devuelve la consulta
        $rawdata[$i] = $row;
        $i++;
    }
        //Cerramos la base de datos
    $mysqli->close();
        //devolvemos rawdata
    //return $rawdata;
    
    //Adaptar el tiempo
    for($i=0;$i<count($rawdata);$i++){
	    $tiempo = $rawdata[$i]["tiempo"];
	    $date = new DateTime($tiempo);
	    $rawdata[$i]["tiempo"]=$date->getTimestamp()*1000;
	}
   
?>


<html>
   <head>
      <h1 style="text-align: center;">Monitoreo del aire</h1>
   </head>
</html>

<HTML>
<BODY>




<meta charset="utf-8"> 

<!-- Latest compiled and minified JavaScript -->
<script src="https://code.jquery.com/jquery.js"></script>
    <!-- Importo el archivo Javascript de Highcharts directamente desde su servidor -->
<script src="http://code.highcharts.com/stock/highstock.js"></script>
<script src="http://code.highcharts.com/modules/exporting.js"></script>

<div id="container">
</div>


<script type='text/javascript'>
$(function () {
    $(document).ready(function() {
        Highcharts.setOptions({
            global: {
                useUTC: false
            }
        });
    
        var chart;
        $('#container').highcharts({
            chart: {
                type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function() {
                        
                    }
                }
            },
            title: {
                text: 'Gráfico Concentración de Polvo'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Valores'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) +'<br/>'+
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: true
            },
            exporting: {
                enabled: true
            },
            series: [{
                name: 'polvo',
                     data: (function() {
                         var data = [];
                    <?php
                        for($i = 0 ;$i<count($rawdata);$i++){
                    ?>
                    data.push([<?php echo $rawdata[$i]["tiempo"];?>,<?php echo $rawdata[$i]["polvo"];?>]);
                    <?php } ?>
                return data;
                     })()     
            }]
        });
    });
    
});


</script>

<html>
<body>
   <h1 style="text-align: center;">Tabla de Valores</h1>

   <table style="height: 99px; margin-left: auto; margin-right: auto;" border="1" width="361">
    <tr>
      <td>&nbsp;Tiempo&nbsp;</td>
      <td>&nbsp;Temperatura&nbsp;</td>
      <td>&nbsp;Humedad&nbsp;</td>
      <td>&nbsp;Polvo&nbsp;</td>
    </tr>

      <?php 
      if($result2->num_rows > 0){
         while($row = $result2->fetch_assoc()) {
            printf("<tr> <td> &nbsp;%s </td> <td> &nbsp;%s&nbsp; </td> <td> &nbsp;%s </td>  <td> &nbsp;%s </td> </tr>", 
               $row["tiempo"], $row["temperatura"],$row["humedad"],$row["polvo"]);
         }
         mysql_free_result($result2);
         $mysqli->close();
      }
      ?>

   </table>
</body>
</html>
