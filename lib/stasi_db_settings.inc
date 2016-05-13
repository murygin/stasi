<?php
/*
 * DB SETTINGS
 */
 
 $debug = true;
include ( "config.inc" );
 $db = mysql_connect($sDbHost, $sDbUser, $sDbPass);
 mysql_select_db($sDbName,$db);
 
 $bIsDbConnected=true;
 
 function dbError($queryString) {
 	echo "<b>An error occured executing the following query:</b><br>".$queryString;
 }
?>
