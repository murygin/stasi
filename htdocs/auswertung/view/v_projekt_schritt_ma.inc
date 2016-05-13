<?php
include( "auswertung/projekt_schritt_ma.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer schritte eines projekts dar
*/
class v_projekt_schritt_ma {
	
	var $bIsDebug=false;
	
	var $nSchrittId;
	var $projekt_schritt_ma;
	
	function v_projekt_schritt_ma( $nSchrittId, $sBegin, $sEnd ) {
		$this->nSchrittId = $nSchrittId;
		$this->projekt_schritt_ma = new projekt_schritt_ma($nSchrittId);
		$this->projekt_schritt_ma->sBegin = $sBegin;
		$this->projekt_schritt_ma->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd, $sDate;
		if( $this->projekt_schritt_ma->sBegin=="" )
			$urlBegin="-1";
		else
			$urlBegin=$this->projekt_schritt_ma->sBegin;
		if( $this->projekt_schritt_ma->sEnd=="" )
			$urlEnd="-1";
		else
			$urlEnd=$this->projekt_schritt_ma->sEnd;
		$sTable = "<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">
";
		$rsProjektSchrittMa = $this->projekt_schritt_ma->getResultSet();
		if( $rowProjektSchrittMa=mysql_fetch_array( $rsProjektSchrittMa ) ) {
			$sProjekt = $rowProjektSchrittMa["projekt"];
			$nProjektId = $rowProjektSchrittMa["projekt_id"];
			$sSchritt = $rowProjektSchrittMa["schritt"];
			$nSchrittId = $rowProjektSchrittMa["schritt_id"];
			$sName = $rowProjektSchrittMa["name"];
			$nMaId = $rowProjektSchrittMa["ma_id"];
			$nSumme = getDays( $rowProjektSchrittMa["summe"] );
				
			$sTable .= "
<tr>
	<th colspan=\"2\" align=\"left\"><a href=\"index.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "\" class=\"th\">Projekte</a> - <a href=\"projekt_schritt.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "&urlProjektId=$nProjektId\" class=\"th\">$sProjekt</a> - $sSchritt</th>
</tr>
<tr>
	<td colspan='2'>" . getZeitraum( $this->projekt_schritt_ma->sBegin, $this->projekt_schritt_ma->sEnd, $this->projekt_schritt_ma->sDate ) . "</td>
</tr>
<tr>
	<td>Mitarbeiter</th>
	<td>Tage</th>
</tr>
<tr>
	<td><a href='javascript:showDetail( $nMaId,$nSchrittId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>$sName</a></td>
	<td><a href='javascript:showDetail( $nMaId,$nSchrittId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>$nSumme</a></td>
</tr>
";
		}
		
		while( $rowProjektSchrittMa=mysql_fetch_array( $rsProjektSchrittMa ) ) {
			$sName = $rowProjektSchrittMa["name"];
			$nMaId = $rowProjektSchrittMa["ma_id"];
			$nSumme = getDays( $rowProjektSchrittMa["summe"] );
			$sTable .= "
<tr>
	<td><a href='javascript:showDetail( $nMaId,$nSchrittId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $sName . "</a></td>
	<td><a href='javascript:showDetail( $nMaId,$nSchrittId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $nSumme . "</a></td>
</tr>
";
		} 
		if( $this->projekt_schritt_ma->nPmId!="" || $this->projekt_schritt_ma->nMaId!="" ) {
			$sTable .= '<tr>
	<td>?</td>
	<td>?</td>
</tr>
';
			if( $this->projekt_schritt_ma->nPmId!="" ) {
			$sTable .= '<tr>
	<td colspan="2" class="klein">Es wird nur Deine eigene und die Arbeitszeit von Mitarbeitern angezeigt, die fuer Deine Projekte arbeiten.</td>
</tr>		 
';
			}
			else {
				if( $this->projekt_schritt_ma->nMaId!="" ) {
					$sTable .= '<tr>
	<td colspan="2" class="klein">Es wird nur Deine eigene Arbeitszeit angezeigt.</td>
</tr>		 
';
				}
			}
		} 
		$sTable .= '<tr>
	<td colspan="2" class="klein" align="right"><a href="javascript:printView(' . $this->nSchrittId . ', \'' . $sBegin . '\', \'' . $sEnd . '\', \'' . $sDate . '\');">Druckansicht</a></td>		
</tr></table>
';
		return $sTable;
	}
	
}
?>