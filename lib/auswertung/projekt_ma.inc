<?php
if( !$bAuswertungIncluded )
	include( "auswertung/auswertung.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class projekt_ma extends auswertung {
	var $bIsDebug=false;
	
	var $nProjektId;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function projekt_ma( $nProjektId ) {
		$this->setMonth( date( "m" ) );
		$this->nProjektId = $nProjektId;
	}
	
	function getSql() {
		return "select projekt.bezeichnung as projekt,projekt.projekt_id,concat( ma.vorname,' ',ma.name) as name,ma.ma_id,sum(arbeit.dauer) as summe from arbeit,projekt,schritt,ma where projekt.projekt_id=" . $this->nProjektId . " and arbeit.ma_id=ma.ma_id and " . $this->getWhereStmt() . " group by arbeit.ma_id order by name";
	}

}
?>
