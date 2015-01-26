/* Include the pData class */
include("class/pData.class.php");
 
/* Create the pData object */
$MyData = new pData();  
 
/* Connect to the MySQL database */
$db = mysql_connect("localhost", "dbuser", "dbpwd");
mysql_select_db("pchart",$db);

/* Build the query that will returns the data to graph */
$Requete = "SELECT * FROM `measures`";
$Result  = mysql_query($Requete,$db);
while($row = mysql_fetch_array($Result))
{
  /* Get the data from the query result */
  $timestamp   = $row["timestamp"];
  $temperature = $row["temperature"];
  $humidity    = $row["humidity"];
 
  /* Save the data in the pData array */
  $myData->addPoints($timestamp,"Timestamp");
  $myData->addPoints($temperature,"Temperature");
  $myData->addPoints($humidity,"Humidity");
}

/* Build the query that will returns the data to graph */
$Requete = "SELECT * FROM `measures`";
$Result  = mysql_query($Requete,$db);
$timestamp=""; $temperature=""; $humidity="";
while($row = mysql_fetch_array($Result))
{
  /* Push the results of the query in an array */
  $timestamp[]   = $row["timestamp"];
  $temperature[] = $row["temperature"];
  $humidity[]    = $row["humidity"];
}
 
/* Save the data in the pData array */
$myData->addPoints($timestamp,"Timestamp");
$myData->addPoints($temperature,"Temperature");
$myData->addPoints($humidity,"Humidity");

/* Put the timestamp column on the abscissa axis */
$myData->setAbscissa("Timestamp");

/* Associate the "Humidity" data serie to the second axis */
$myData->setSerieOnAxis("Humidity", 1);
 
/* Name this axis "Time" */
$myData->setXAxisName("Time");
 
/* Specify that this axis will display time values */
$myData->setXAxisDisplay(AXIS_FORMAT_TIME,"H:i");

/* First Y axis will be dedicated to the temperatures */
$myData->setAxisName(0,"Temperature");
$myData->setAxisUnit(0,"°C");
 
/* Second Y axis will be dedicated to humidity */
$myData->setAxisName(1,"Humidity");
$myData->setAxisUnit(0,"%");
