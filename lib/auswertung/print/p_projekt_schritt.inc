<?php
include( "auswertung/projekt_schritt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer schritte eines projekts dar
*/
class p_projekt_schritt {
	
	var $bIsDebug=false;
	
	var $nProjektId;
	var $projekt_schritt;
	
	function p_projekt_schritt( $nProjektId, $sBegin, $sEnd ) {
		$this->nProjektId = $nProjektId;
		$this->projekt_schritt = new projekt_schritt($nProjektId);
		$this->projekt_schritt->sBegin = $sBegin;
		$this->projekt_schritt->sEnd = $sEnd;
	}
	
	function getTable() {
		global  $sBegin, $sEnd, $sDate;
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
		<th colspan=\"2\"  class=\"tjossweiss\"  align=\"left\">$sProjekt</th>
	</tr>
";
			$sTable .= '<tr>
		<td colspan="2" class="tjossweissduenn">' . getZeitraum( $this->projekt_schritt->sBegin, $this->projekt_schritt->sEnd, $this->projekt_schritt->sDate ) . '</td>
	</tr>
	<tr>
		<td class="tjossweissduenn">Schritt</th>
		<td class="tjossweissduenn">Tage</th>
	</tr>
	<tr>
		<td class="tjossweissduenn">' . $sSchritt . '</td>
		<td class="tjossweissduenn">' . $nSumme . '</td>
	</tr>
';
		}
		
		while( $rowProjektSchritt=mysql_fetch_array( $rsProjektSchritt ) ) {
			$sSchritt = $rowProjektSchritt["schritt"];
			$nSchrittId = $rowProjektSchritt["schritt_id"];
			$nSumme = getDays( $rowProjektSchritt["summe"] );
			$sTable .= '
<tr>
	<td class="tjossweissduenn">' . $sSchritt . '</td>
	<td class="tjossweissduenn">' . $nSumme . '</td>
</tr>
';
		} 
		$sTable .= '</table>
';
		return $sTable;
	}
	
}
?>