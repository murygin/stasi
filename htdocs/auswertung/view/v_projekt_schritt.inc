<?php
include( "auswertung/projekt_schritt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer schritte eines projekts dar
*/
class v_projekt_schritt {
	
	var $bIsDebug=false;
	
	var $nProjektId;
	var $projekt_schritt;
	
	function v_projekt_schritt( $nProjektId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_schritt = new projekt_schritt($nProjektId);
		$this->projekt_schritt->sBegin = $sBegin;
		$this->projekt_schritt->sEnd = $sEnd;
	}
	
	function getTable() {
		global  $sBegin, $sEnd, $sDate, $urlBegin, $urlEnd;
		$rsProjektSchritt = $this->projekt_schritt->getResultSet();
		if( $rowProjektSchritt=mysql_fetch_array( $rsProjektSchritt ) ) {
			$sProjekt = $rowProjektSchritt["projekt"];
			$sSchritt = $rowProjektSchritt["schritt"];
			$nSchrittId = $rowProjektSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektSchritt["summe"] );
			
			if( $this->projekt_schritt->sBegin=="" )
				$urlBegin="-1";
			else
				$urlBegin=$this->projekt_schritt->sBegin;
			if( $this->projekt_schritt->sEnd=="" )
				$urlEnd="-1";
			else
				$urlEnd=$this->projekt_schritt->sEnd;
			
			$sTable = "
<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">
	<tr>
		<th colspan=\"2\" align=\"left\"><a href=\"index.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "\" class=\"th\">Projekte</a> - $sProjekt</th>
	</tr>
";
			
			$sTable .= '<tr>
		<td colspan="2">' . getZeitraum( $this->projekt_schritt->sBegin, $this->projekt_schritt->sEnd, $this->projekt_schritt->sDate ) . '</td>
	</tr>
	<tr>
		<td>Schritt</th>
		<td>Tage</th>
	</tr>
	<tr>
		<td><a href="javascript:showProjektSchrittMa(' . $nSchrittId . ', \'' . $sBegin . '\', \'' . $sEnd . '\', \'' . $sDate . '\' )">' . $sSchritt . '</a></td>
		<td><a href="javascript:showProjektSchrittMa(' . $nSchrittId . ', \'' . $sBegin . '\', \'' . $sEnd . '\', \'' . $sDate . '\' )">' . $nSumme . '</a></td>
	</tr>
';
		}
		
		while( $rowProjektSchritt=mysql_fetch_array( $rsProjektSchritt ) ) {
			$sSchritt = $rowProjektSchritt["schritt"];
			$nSchrittId = $rowProjektSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektSchritt["summe"] );
			$sTable .= "
<tr>
	<td><a href='javascript:showProjektSchrittMa(" . $nSchrittId . ", \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $sSchritt . "</a></td>
	<td><a href='javascript:showProjektSchrittMa(" . $nSchrittId . ", \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $nSumme . "</a></td>
</tr>
";
		} 
		$sTable .= "<tr>
	<td colspan=\"2\" class=\"klein\" align=\"right\"><a href='javascript:printView(" . $this->nProjektId . ", \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\");'>Druckansicht</a></td>		
</tr></table>
";
		return $sTable;
	}
	
}
?>