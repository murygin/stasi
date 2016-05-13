<?php
if( !$bAuswertungIncluded )
	include( "auswertung/projekt_ma.inc" );
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class projekt_ma_schritt extends projekt_ma {
	var $bIsDebug=false;
	
	/**
	* erzeugt eine neue projektansicht fuer das aktuelle jahr und dne aktuellen monat
	*/
	function projekt_ma_schritt( $nProjektId, $nMaId ) {
		$this->setMonth( date( "m" ) );
		$this->nProjektId = $nProjektId;
		$this->nMaId = $nMaId;
	}
	
	function getSql() {
		return "select distinct projekt.bezeichnung as projekt,projekt.projekt_id,concat( ma.vorname,' ',ma.name) as name,arbeit.ma_id,arbeit.schritt_id,schritt.bezeichnung as schritt,sum(arbeit.dauer) as summe from " . $this->getTables() ." where projekt.projekt_id=" . $this->nProjektId . " and " . $this->getWhereStmt() . " group by schritt.schritt_id order by schritt";
	}

}
?>
