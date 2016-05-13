<?php
/**
* funktionene fuer die auswertung
*/
function getDays( $nSeconds ) {
	return  round( $nSeconds/28800, 2 );
}
function getHours( $nSeconds ) {
	$nHours = floor( $nSeconds/3600 );
	$nMinutes = floor( ($nSeconds-$nHours*3600)/60 );
	if( $nMinutes==0 )
		return $nHours;
	else
		return $nHours . ":" . $nMinutes;
}

/**
* wandelt ein datum vom mysql format yyyy-mm-tt in das dt. datums format tt.mm.yyyy
*/
function getGermanDate( $sMySqlDate ) {
	$nYahr=substr( $sMySqlDate, 0, 4 );
	$nMonat=substr( $sMySqlDate, 5, 2 );
	$nTag=substr( $sMySqlDate, 8, 2 );
	return $nTag . "." . $nMonat . "." . $nYahr;
}

?>