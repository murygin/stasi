<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class stunden extends auswertung {
	var $bIsDebug=false;
	
	var $nMaId;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function stunden( $nMaId ) {
		$this->sDate=date( "Y-m-d" );
		$this->nMaId = $nMaId;
	}
	
	function getSql() {
		return "select projekt.bezeichnung as projekt,schritt.bezeichnung as schritt,arbeit.arbeit_id,arbeit.beschreibung,arbeit.datum,arbeit.dauer from " . $this->getTables() ." where " . $this->getWhereStmt() . "  order by arbeit.datum";
	}
}
?>
