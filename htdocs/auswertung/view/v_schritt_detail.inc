<?php
include( "auswertung/schritt_detail.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer schritte eines projekts dar
*/
class v_schritt_detail {
	
	var $bIsDebug=false;
	var $schritt_detail;
	
	function v_schritt_detail( $nMaId, $nSchrittId, $sBegin, $sEnd ) {
		$this->schritt_detail = new schritt_detail( $nMaId,$nSchrittId );
		$this->schritt_detail->sBegin = $sBegin;
		$this->schritt_detail->sEnd = $sEnd;
	}
	
	function getTable() {
		global $txtTagB, $txtMonatB, $txtJahrB, $txtTagE, $txtMonatE, $txtJahrE;
		global $sBegin, $sEnd, $sDate;
		if( $this->schritt_detail->sBegin=="" )
			$urlBegin="-1";
		else
			$urlBegin=$this->schritt_detail->sBegin;
		if( $this->schritt_detail->sEnd=="" )
			$urlEnd="-1";
		else
			$urlEnd=$this->schritt_detail->sEnd;
		$sTable = "<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">
";
		$rsSchrittDetail = $this->schritt_detail->getResultSet();
		if( $rowSchrittDetail=mysql_fetch_array( $rsSchrittDetail ) ) {
			$sProjekt = $rowSchrittDetail["projekt"];
			$nProjektId = $rowSchrittDetail["projekt_id"];
			$sSchritt = $rowSchrittDetail["schritt"];
			$nSchrittId = $rowSchrittDetail["schritt_id"];
			$sName = $rowSchrittDetail["name"];
			$nMaId = $rowSchrittDetail["ma_id"];
			$nArbeitId = $rowSchrittDetail["arbeit_id"];
			$nDauer = getHours( $rowSchrittDetail["dauer"] );
			$sDatum = getGermanDate( $rowSchrittDetail["datum"] );
			$sBeschreibung = $rowSchrittDetail["beschreibung"]; 
			if( $sBeschreibung=="" )
				$sBeschreibung="&nbsp;"; 
					
			$sTable .= "
<tr>
	<th colspan=\"3\" align=\"left\"><a href=\"index.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "\" class=\"th\">Projekte</a> - <a href=\"projekt_schritt.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "&urlProjektId=$nProjektId\" class=\"th\">$sProjekt</a> - <a href=\"projekt_ma_schritt.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "&urlProjektId=" . $nProjektId . "&urlMaId=" . $nMaId . "\" class=\"th\">" . $sName ."</a> - <a href=\"projekt_schritt_ma.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "&urlSchrittId=" . $nSchrittId . "\" class=\"th\">" . $sSchritt . "</a></th>
</tr>
<tr>
	<td colspan='3'>" . getZeitraum( $this->schritt_detail->sBegin, $this->schritt_detail->sEnd, $this->schritt_detail->sDate ) . "</td>
</tr>
<tr>
	<td>Datum</td>
	<td>Dauer in h</td>
	<td>Beschreibung</td>
</tr>
<tr>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $sDatum . "</a></td>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $nDauer . "</a></td>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $sBeschreibung . "</a></td>
</tr>
";
		}
		
		while( $rowSchrittDetail=mysql_fetch_array( $rsSchrittDetail ) ) {
			$nArbeitId = $rowSchrittDetail["arbeit_id"];
			$nDauer = getHours( $rowSchrittDetail["dauer"] );
			$nDauer = getHours( $rowSchrittDetail["dauer"] );
			$sDatum = getGermanDate( $rowSchrittDetail["datum"] );
			$sBeschreibung = $rowSchrittDetail["beschreibung"];
			if( $sBeschreibung=="" )
				$sBeschreibung="&nbsp;"; 
			$sTable .= "
<tr>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $sDatum . "</a></td>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $nDauer . "</a></td>
	<td><a href='javascript:openEditWindow( " . $nArbeitId . " )'>" . $sBeschreibung . "</a></td>
</tr>
";
		} 
		
		$sTable .= '<tr>
	<td colspan="3" class="klein" align="right"><a href="javascript:printView(' . $this->schritt_detail->nMaId . ',' . $this->schritt_detail->nSchrittId . ', \'' . $sBegin . '\', \'' . $sEnd . '\', \'' . $sDate . '\');">Druckansicht</a></td>		
</tr></table>
';
		return $sTable;
	}
	
}
?>