<?php
include( "auswertung/projekt_ma_schritt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer mitarbeiter eines projekts dar
*/
class p_projekt_ma_schritt {
	
	var $bIsDebug=false;
	
	var $projekt_ma_schritt;
	var $nProjektId;
	
	function p_projekt_ma_schritt( $nProjektId, $nMaId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_ma_schritt = new projekt_ma_schritt( $nProjektId,$nMaId );
		$this->projekt_ma_schritt->sBegin = $sBegin;
		$this->projekt_ma_schritt->sEnd = $sEnd;
	}
	
	function getTable() {
		global  $sBegin, $sEnd;
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
		<th colspan=\"2\" class=\"tjossweiss\" align=\"left\">$sProjekt - $sName</th>
	</tr>
";
			$sTable .= '<tr>
		<td colspan="2" class="tjossweissduenn">' . getZeitraum( $this->projekt_ma_schritt->sBegin, $this->projekt_ma_schritt->sEnd, $this->projekt_ma_schritt->sDate ) . '</td>
	</tr>
	<tr>
		<td class="tjossweissduenn">Arbeitsschritt</th>
		<td class="tjossweissduenn">Tage</th>
	</tr>
	<tr>
		<td class="tjossweissduenn">' . $sSchritt . '</td>
		<td class="tjossweissduenn">' . $nSumme . '</td>
	</tr>
';
		}
		
		while( $rowProjektMaSchritt=mysql_fetch_array( $rsProjektMaSchritt ) ) {
			$sSchritt = $rowProjektMaSchritt["schritt"];
			$nSchrittId = $rowProjektMaSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektMaSchritt["summe"] );
			$sTable .= "
<tr>
	<td class='tjossweissduenn'>" . $sSchritt . "</td>
	<td class='tjossweissduenn'>" . $nSumme . "</td>
</tr>
";
		} 
		$sTable .= '</table>
';
		return $sTable;
	}
	
}
?>