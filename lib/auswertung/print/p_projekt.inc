<?php
include( "auswertung/projekt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class p_projekt {
	
	var $bIsDebug=false;
	
	var $projekt;
	
	function p_projekt( $sBegin, $sEnd ) {
		$this->projekt = new projekt();
		$this->projekt->sBegin = $sBegin;
		$this->projekt->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd;
		$sTable = '
<table border="0" cellpadding="1" cellspacing="1" width="100%">
';
		$sTable .= '<tr>
	<th colspan="2"  class="tjossweiss" align="left">Projekte</th>
</tr>
<tr>
	<td colspan="2"  class="tjossweissduenn">' . getZeitraum( $this->projekt->sBegin, $this->projekt->sEnd, $this->projekt->sDate ) . '</td>
</tr>
<tr>
	<td class="tjossweissduenn">Projekt</td>
	<td class="tjossweissduenn">Tage</td>
</tr>
';
		$rsProjekt = $this->projekt->getResultSet();
		while( $rowProjekt=mysql_fetch_array( $rsProjekt ) ) {
			$sProjekt = $rowProjekt["projekt"];
			$nProjektId = $rowProjekt["projekt_id"];
			$nSumme = getDays( $rowProjekt["summe"] );
			$sTable .= "
<tr>
	<td class='tjossweissduenn'>" . $sProjekt . "</td>
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