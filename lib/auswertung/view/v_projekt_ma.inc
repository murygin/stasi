<?php
include( "auswertung/projekt_ma.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer mitarbeiter eines projekts dar
*/
class v_projekt_ma {
	
	var $bIsDebug=false;
	
	var $projekt_ma;
	var $nProjektId;
	
	function v_projekt_ma( $nProjektId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_ma = new projekt_ma($nProjektId);
		$this->projekt_ma->sBegin = $sBegin;
		$this->projekt_ma->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd, $sDate;
		global $txtTagB, $txtMonatB, $txtJahrB, $txtTagE, $txtMonatE, $txtJahrE;
		$sTable = "<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">
";
		$rsProjektMa = $this->projekt_ma->getResultSet();
		if( $rowProjektMa=mysql_fetch_array( $rsProjektMa ) ) {
			$sProjekt = $rowProjektMa["projekt"];
			$nProjektId= $rowProjektMa["projekt_id"];
			$sName = $rowProjektMa["name"];
			$nMaId = $rowProjektMa["ma_id"];
			$nSumme = getDays( $rowProjektMa["summe"] );
			
			if( $this->projekt_ma->sBegin=="" )
				$urlBegin="-1";
			else
				$urlBegin=$this->projekt_ma->sBegin;
			if( $this->projekt_ma->sEnd=="" )
				$urlEnd="-1";
			else
				$urlEnd=$this->projekt_ma->sEnd;
			
			$sTable .= "<tr>
		<th colspan=\"2\" align=\"left\"><a href=\"index.phtml?urlBegin=" . $urlBegin . "&urlEnd=" . $urlEnd . "&urlDate=" . $sDate . "\" class=\"th\">Projekte</a> - " . $sProjekt . "</th>
	</tr>
	<tr>
		<td colspan=\"2\">" . getZeitraum( $this->projekt_ma->sBegin, $this->projekt_ma->sEnd, $this->projekt_ma->sDate ) . "</td>
	</tr>
	<tr>
		<td>Name</th>
		<td>Tage</th>
	</tr>
	<tr>
		<td><a href='javascript:showProjektMaSchritt( " . $nProjektId . "," . $nMaId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $sName . "</a></td>
		<td><a href='javascript:showProjektMaSchritt( " . $nProjektId . "," . $nMaId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $nSumme . "</a></td>
	</tr>
";
		}
		
		while( $rowProjektMa=mysql_fetch_array( $rsProjektMa ) ) {
			$sName = $rowProjektMa["name"];
			$nMaId = $rowProjektMa["ma_id"];
			$nSumme = getDays( $rowProjektMa["summe"] );
			$sTable .= "
<tr>
	<td><a href='javascript:showProjektMaSchritt( $nProjektId,$nMaId,\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $sName . "</a></td>
	<td><a href='javascript:showProjektMaSchritt( $nProjektId,$nMaId,\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>" . $nSumme . "</a></td>
</tr>
";
		} 
		if( $this->projekt_ma->nPmId!="" || $this->projekt_ma->nMaId!="" ) {
			$sTable .= '<tr>
	<td>?</td>
	<td>?</td>
</tr>
';
			if( $this->projekt_ma->nPmId!="" ) {
			$sTable .= '<tr>
	<td colspan="2" class="klein">Es wird nur Deine eigene und die Arbeitszeit von Mitarbeitern angezeigt, die fuer Deine Projekte arbeiten.</td>
</tr>		 
';
			}
			else {
				if( $this->projekt_ma->nMaId!="" ) {
					$sTable .= '<tr>
	<td colspan="2" class="klein">Es wird nur Deine eigene Arbeitszeit angezeigt.</td>
</tr>		 
';
				}
			}
		} 
		$sTable .= "<tr>
	<td colspan=\"2\" class=\"klein\" align=\"right\"><a href='javascript:printView(" . $nProjektId . ",\"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\");'>Druckansicht</a></td>		
</tr></table>
";
		return $sTable;
	}
	
}
?>