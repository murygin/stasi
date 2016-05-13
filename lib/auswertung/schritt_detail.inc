<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class schritt_detail extends auswertung {
	var $bIsDebug=false;
	
	var $nSchrittId;
	var $nMaId;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function schritt_detail( $nMaId, $nSchrittId ) {
		$this->setMonth( date( "m" ) );
		$this->nSchrittId = $nSchrittId;
		$this->nMaId = $nMaId;
	}
	
	function getSql() {
		return "select projekt.projekt_id,projekt.bezeichnung as projekt,schritt.bezeichnung as schritt,arbeit.schritt_id,concat( ma.vorname,' ',ma.name) as name,ma.ma_id,arbeit.arbeit_id,arbeit.beschreibung,arbeit.datum,arbeit.dauer from arbeit,projekt,schritt,ma where arbeit.schritt_id=" . $this->nSchrittId . " and arbeit.ma_id=ma.ma_id and " . $this->getWhereStmt() . "  order by arbeit.datum";
	}

}
?>
