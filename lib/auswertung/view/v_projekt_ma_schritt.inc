<?php
include( "auswertung/projekt_ma_schritt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer mitarbeiter eines projekts dar
*/
class v_projekt_ma_schritt {
	
	var $bIsDebug=false;
	
	var $projekt_ma_schritt;
	var $nProjektId;
	
	function v_projekt_ma_schritt( $nProjektId, $nMaId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_ma_schritt = new projekt_ma_schritt( $nProjektId,$nMaId );
		$this->projekt_ma_schritt->sBegin = $sBegin;
		$this->projekt_ma_schritt->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd, $sDate;
		global $txtTagB, $txtMonatB, $txtJahrB, $txtTagE, $txtMonatE, $txtJahrE;
		$rsProjektMaSchritt = $this->projekt_ma_schritt->getResultSet();
		if( $rowProjektMaSchritt=mysql_fetch_array( $rsProjektMaSchritt ) ) {
			$sProjekt = $rowProjektMaSchritt["projekt"];
			$nProjektId = $rowProjektMaSchritt["projekt_id"];
			$sName = $rowProjektMaSchritt["name"];
			$nMaId = $rowProjektMaSchritt["ma_id"];
			$sSchritt = $rowProjektMaSchritt["schritt"];
			$nSchrittId = $rowProjektMaSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektMaSchritt["summe"] );
			
			if( $this->projekt_ma_schritt->sBegin=="" )
				$urlBegin="-1";
			else
				$urlBegin=$this->projekt_ma_schritt->sBegin;
			if( $this->projekt_ma_schritt->sEnd=="" )
				$urlEnd="-1";
			else
				$urlEnd=$this->projekt_ma_schritt->sEnd;
			
			$sTable = "
<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">
	<tr>
		<th colspan=\"2\" align=\"left\"><a href=\"index.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "\" class=\"th\">Projekte</a> - <a href=\"projekt_ma.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "&urlProjektId=$nProjektId\" class=\"th\">$sProjekt</a> - $sName</th>
	</tr>
	<tr>
		<td colspan=\"2\">" . getZeitraum( $this->projekt_ma_schritt->sBegin, $this->projekt_ma_schritt->sEnd, $this->projekt_ma_schritt->sDate ) . "</td>
	</tr>
	<tr>
		<td>Arbeitsschritt</th>
		<td>Tage</th>
	</tr>
	<tr>
		<td><a href='javascript:showDetail( " . $nMaId . "," . $nSchrittId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\"  )'>$sSchritt</a></td>
		<td><a href='javascript:showDetail( " . $nMaId . "," . $nSchrittId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\"  )'>$nSumme</a></td>
	</tr>
";
		}
		
		while( $rowProjektMaSchritt=mysql_fetch_array( $rsProjektMaSchritt ) ) {
			$sSchritt = $rowProjektMaSchritt["schritt"];
			$nSchrittId = $rowProjektMaSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektMaSchritt["summe"] );
			//$nSumme = $rowProjektMaSchritt["summe"];
			$sTable .= "
<tr>
	<td><a href='javascript:showDetail( " . $nMaId . "," . $nSchrittId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\"  )'>" . $sSchritt . "</a></td>
	<td><a href='javascript:showDetail( " . $nMaId . "," . $nSchrittId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\"  )'>" . $nSumme . "</a></td>
</tr>
";
		} 
		$sTable .= '<tr>
	<td colspan="2" class="klein" align="right"><a href="javascript:printView(' . $this->nProjektId . ',' . $nMaId . ', \'' . $sBegin . '\', \'' . $sEnd . '\', \'' . $sDate . '\');">Druckansicht</a></td>		
</tr></table>
';
		return $sTable;
	}
	
}
?>