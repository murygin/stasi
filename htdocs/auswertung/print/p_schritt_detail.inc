<?php
include( "auswertung/schritt_detail.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer schritte eines projekts dar
*/
class p_schritt_detail {
	
	var $bIsDebug=false;
	var $schritt_detail;
	
	function p_schritt_detail( $nMaId, $nSchrittId, $sBegin, $sEnd ) {
		$this->schritt_detail = new schritt_detail( $nMaId,$nSchrittId );
		$this->schritt_detail->sBegin = $sBegin;
		$this->schritt_detail->sEnd = $sEnd;
	}
	
	function getTable() {
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
			$nDauer = getHours( $rowSchrittDetail["dauer"] );
			$sDatum = getGermanDate( $rowSchrittDetail["datum"] );
			$sBeschreibung = $rowSchrittDetail["beschreibung"]; 
			if( $sBeschreibung=="" )
				$sBeschreibung="&nbsp;"; 
					
			$sTable .= "
<tr>
	<th colspan=\"3\"  class=\"tjossweiss\" align=\"left\">Projekte - " . $sProjekt . " - " . $sName ." - " . $sSchritt . "</th>
</tr>
<tr>
	<td colspan=\"3\" class=\"tjossweissduenn\">" . getZeitraum( $this->schritt_detail->sBegin, $this->schritt_detail->sEnd, $this->schritt_detail->sDate ) . "</td>
</tr>
<tr>
	<td class='tjossweissduenn'>Datum</td>
	<td class='tjossweissduenn'>Dauer in h</td>
	<td class='tjossweissduenn'>Beschreibung</td>
</tr>
<tr>
	<td class='tjossweissduenn'>$sDatum</td>
	<td class='tjossweissduenn'>$nDauer</td>
	<td class='tjossweissduenn'>$sBeschreibung</td>
</tr>
";
		}
		
		while( $rowSchrittDetail=mysql_fetch_array( $rsSchrittDetail ) ) {
			$nDauer = getHours( $rowSchrittDetail["dauer"] );
			$sDatum = getGermanDate( $rowSchrittDetail["datum"] );
			$sBeschreibung = $rowSchrittDetail["beschreibung"];
			if( $sBeschreibung=="" )
				$sBeschreibung="&nbsp;"; 
			$sTable .= "
<tr>
	<td class='tjossweissduenn'>$sDatum</td>
	<td class='tjossweissduenn'>$nDauer</td>
	<td class='tjossweissduenn'>$sBeschreibung</td>
</tr>
";
		} 
		
		$sTable .= '</table>
';
		return $sTable;
	}
	
}
?>