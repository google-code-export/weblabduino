<?php

/* Include the pData class */
include("./pChart/class/pData.class.php");
include("./pChart/class/pDraw.class.php");
include("./pChart/class/pImage.class.php");


 /* Create the pData object */
 $myData = new pData();

 /* Connect to the MySQL database */
 $db = mysql_connect("localhost", "cna", "cna");
 mysql_select_db("experimentos",$db);

 /* Build the query that will returns the data to graph */
 $Requete = "SELECT * FROM `cna`";
 $Result  = mysql_query($Requete,$db);
 while($row = mysql_fetch_array($Result))
 {
   /* Get the data from the query result */
   $data   = $row["data"];
   $ch0   = $row["ch0"];
   $ch1  = $row["ch1"];
  
   /* Save the data in the pData array */
   $myData->addPoints($data,"tempo");
   $myData->addPoints($ch0,"branca");
   $myData->addPoints($ch1,"preta");
 }  

/* Put the timestamp column on the abscissa axis */
$myData->setAbscissa("tempo");
$myData->setXAxisName("data");
$myData->setAxisUnit(0,"°C");

/*=================================================================*/

$myPicture = new pImage(700,500,$myData);
$Settings = array("R"=>170, "G"=>183, "B"=>87, "Dash"=>1, "DashR"=>190, "DashG"=>203, "DashB"=>107);
$myPicture->drawFilledRectangle(0,0,700,500,$Settings);

$Settings = array("StartR"=>147, "StartG"=>143, "StartB"=>255, "EndR"=>102, "EndG"=>158, "EndB"=>255, "Alpha"=>50);
$myPicture->drawGradientArea(0,0,700,500,DIRECTION_VERTICAL,$Settings);

$myPicture->drawRectangle(0,0,699,499,array("R"=>0,"G"=>0,"B"=>0));

$myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>50,"G"=>50,"B"=>50,"Alpha"=>20));

$myPicture->setFontProperties(array("FontName"=>"./pChart/fonts/Forgotte.ttf","FontSize"=>20));
$TextSettings = array("Align"=>TEXT_ALIGN_MIDDLEMIDDLE
, "R"=>255, "G"=>255, "B"=>255);
$myPicture->drawText(350,25,"Temperatura das Calotas",$TextSettings);

$myPicture->setShadow(FALSE);
$myPicture->setGraphArea(50,50,675,460);
$myPicture->setFontProperties(array("R"=>0,"G"=>0,"B"=>0,"FontName"=>"./pChart/fonts/pf_arma_five.ttf","FontSize"=>10));

$Settings = array("Pos"=>SCALE_POS_LEFTRIGHT
, "Mode"=>SCALE_MODE_FLOATING
, "LabelingMethod"=>LABELING_ALL
, "GridR"=>255, "GridG"=>255, "GridB"=>255, "GridAlpha"=>50, "TickR"=>0, "TickG"=>0, "TickB"=>0, "TickAlpha"=>50, "LabelRotation"=>45, "CycleBackground"=>1, "DrawArrows"=>1, "DrawXLines"=>1, "DrawSubTicks"=>1, "SubTickR"=>255, "SubTickG"=>0, "SubTickB"=>0, "SubTickAlpha"=>50, "DrawYLines"=>ALL);
$myPicture->drawScale($Settings);

$myPicture->setShadow(TRUE,array("X"=>1,"Y"=>1,"R"=>50,"G"=>50,"B"=>50,"Alpha"=>10));

$Config = array("DisplayValues"=>1);
$myPicture->drawSplineChart($Config);

$Config = array("FontR"=>0, "FontG"=>0, "FontB"=>0, "FontName"=>"./pChart/fonts/pf_arma_five.ttf", "FontSize"=>10, "Margin"=>6, "Alpha"=>30, "BoxSize"=>5, "Style"=>LEGEND_BOX
, "Mode"=>LEGEND_HORIZONTAL
);
$myPicture->drawLegend(10,15,$Config);

$myPicture->stroke();

?>
