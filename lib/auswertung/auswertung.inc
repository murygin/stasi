<?php
$bAuswertungIncluded=true;
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* basisklasse fuer die auswertung
*/
class auswertung {

	/**
	* mitarbeiter id
	*/
	var $nMaId;
	
	/**
	* pm id
	*/
	var $nPmId;
	
	/*
	* beginn der auswertung, datum in mysql format yyyy-mm-tt
	*/
	var $sBegin;
	
	/*
	* ende der auswertung, datum in mysql format yyyy-mm-tt
	*/
	var $sEnd;
	
	/*
	* tag der auswertung
	*/
	var $sDate;
	
	/**
	* setzt den auswertungszeitraum auf den monat $nMonth
	* und das jahr $nYear
	*/
	function setMonth( $nMonth, $nYear ) {
		$this->sBegin=$nYear . "-" . $nMonth . "-01";
		if( $nMonth==1 || $nMonth==3 || $nMonth==5 || $nMonth==7 || $nMonth==8 || $nMonth==10 || $nMonth==12 )
			$nDay=31;
		else {
			if( $nMonth==2 ) {
				if( $nYear/4==floor($nYear/4) )
					$nDay=29;
				else
					$nDay=28;
			}
			else
				$nDay=30;
		}
		$this->sEnd=$nYear . "-" . $nMonth . "-". $nDay;
	}
	
	/**
	* setzt den auswertungszeitraum auf den monat $nMonth
	* und das jahr auf das aktuelle jahr
	*/
	function setMonth( $nMonth ) {
		$this->sBegin=date( "Y" ) . "-" . $nMonth . "-01";
		if( $nMonth==1 || $nMonth==3 || $nMonth==5 || $nMonth==7 || $nMonth==8 || $nMonth==10 || $nMonth==12 )
			$nDay=31;
		else {
			if( $nMonth==2 ) {
				if( $nYear/4==floor($nYear/4) )
					$nDay=29;
				else
					$nDay=28;
			}
			else
				$nDay=30;
		}
		$this->sEnd=date( "Y" ) . "-" . $nMonth . "-" . $nDay;
	}
	
	/**
	* gibt das where stmt mit den gesetzten filtern zurueck fuer die
	* tabelle arbeit zurueck
	*/
	function getWhereStmt() {
		$sWhrereStmt="arbeit.schritt_id=schritt.schritt_id and schritt.projekt_id=projekt.projekt_id and arbeit.ma_id=ma.ma_id";	
		//filter
		if( $this->nPmId!="" && $this->nMaId )
			$sWhrereStmt.=" and (projekt.pm_id=$this->nPmId or arbeit.ma_id=$this->nMaId)";
		else {
			if( $this->nPmId!="" )
				$sWhrereStmt.=" and projekt.pm_id=$this->nPmId";
			if( $this->nMaId!="" ) 
				$sWhrereStmt.=" and arbeit.ma_id=$this->nMaId";
		}
		if( $this->sBegin!="" )
			$sWhrereStmt.=" and datum>='$this->sBegin'";
		if( $this->sEnd!="" ) 
			$sWhrereStmt.=" and datum<='$this->sEnd'";
		if( $this->sDate!="" )
			$sWhrereStmt.=" and datum='$this->sDate'";
		return $sWhrereStmt;
	}
	
	/**
	* gibt die tabellen zurueck aus denen ausgelesen wird
	*/
	function getTables() {
		return "arbeit,schritt,projekt,ma";
	}
	
	function getResultSet() {
		$rs=mysql_query( $this->getSql() )
			or die( dbError( $this->getSql() ) );
		if( $this->bIsDebug )
			echo $this->getSql();
		return $rs;
	}
}
?>