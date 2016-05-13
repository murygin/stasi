<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class projekt_schritt_ma extends auswertung {
	var $bIsDebug=false;
	
	var $nSchrittId;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function projekt_schritt_ma( $nSchrittId ) {
		$this->setMonth( date( "m" ) );
		$this->nSchrittId = $nSchrittId;
	}
	
	function getSql() {
		return "select projekt.projekt_id,projekt.bezeichnung as projekt,schritt.bezeichnung as schritt,arbeit.schritt_id,concat( ma.vorname,' ',ma.name) as name,ma.ma_id,sum(arbeit.dauer) as summe from arbeit,projekt,schritt,ma where arbeit.schritt_id=" . $this->nSchrittId . " and arbeit.ma_id=ma.ma_id and " . $this->getWhereStmt() . "  group by arbeit.ma_id order by name";
	}

}
?>
