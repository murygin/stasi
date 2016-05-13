<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class projekt extends auswertung {
	
	var $bIsDebug=false;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function projekt() {
		$this->setMonth( date( "m" ), date( "Y" ) );
	}
	
	function getSql() {
		return "select projekt.bezeichnung as projekt,projekt.projekt_id,sum(arbeit.dauer) as summe from " . $this->getTables() . " where " . $this->getWhereStmt() . " group by projekt.projekt_id order by projekt.bezeichnung";
	}
	
}
?>