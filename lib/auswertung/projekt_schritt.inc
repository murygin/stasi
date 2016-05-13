<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class projekt_schritt extends auswertung {
	var $bIsDebug=false;
	
	var $nProjektId;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function projekt_schritt( $nProjektId ) {
		$this->setMonth( date( "m" ) );
		$this->nProjektId = $nProjektId;
	}
	
	function getSql() {
		return "select projekt.bezeichnung as projekt,schritt.bezeichnung as schritt,schritt.schritt_id,sum(arbeit.dauer) as summe from " . $this->getTables() . " where projekt.projekt_id=" . $this->nProjektId . " and " . $this->getWhereStmt() . " group by arbeit.schritt_id order by schritt";
	}

}
?>
