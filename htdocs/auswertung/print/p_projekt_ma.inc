<?php
include( "auswertung/projekt_ma.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer mitarbeiter eines projekts dar
*/
class p_projekt_ma {
	
	var $bIsDebug=false;
	
	var $projekt_ma;
	var $nProjektId;
	
	function p_projekt_ma( $nProjektId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_ma = new projekt_ma($nProjektId);
		$this->projekt_ma->sBegin = $sBegin;
		$this->projekt_ma->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd;
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
			
			$sTable .= '<tr>
		<th colspan="2"  class="tjossweiss" align="left">' . $sProjekt . '</th>
	</tr>
	<tr>
		<td colspan="2" class="tjossweissduenn">' . getZeitraum( $this->projekt_ma->sBegin, $this->projekt_ma->sEnd, $this->projekt_ma->sDate ) . '</td>
	</tr>
	<tr>
		<td class="tjossweissduenn">Name</td>
		<td class="tjossweissduenn">Tage</td>
	</tr>
	<tr>
		<td class="tjossweissduenn">' . $sName . '</td>
		<td class="tjossweissduenn">' . $nSumme . '</td>
	</tr>
';
		}
		
		while( $rowProjektMa=mysql_fetch_array( $rsProjektMa ) ) {
			$sName = $rowProjektMa["name"];
			$nMaId = $rowProjektMa["ma_id"];
			$nSumme = getDays( $rowProjektMa["summe"] );
			$sTable .= '
<tr>
	<td class="tjossweissduenn">' . $sName . '</td>
	<td class="tjossweissduenn">' . $nSumme . '</td>
</tr>
';
		} 
		if( $this->projekt_ma->nPmId!="" || $this->projekt_ma->nMaId!="" ) {
			$sTable .= '<tr>
	<td class="tjossweissduenn">?</td>
	<td class="tjossweissduenn">?</td>
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
		$sTable .= '</table>
';
		return $sTable;
	}
	
}
?>