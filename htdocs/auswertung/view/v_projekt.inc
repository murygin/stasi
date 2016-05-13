<?php
include( "auswertung/projekt.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt die summe aller stunden fuer projekte dar
*/
class v_projekt {
	
	var $bIsDebug=false;
	
	var $projekt;
	
	function v_projekt( $sBegin, $sEnd ) {
		$this->projekt = new projekt();
		$this->projekt->sBegin = $sBegin;
		$this->projekt->sEnd = $sEnd;
	}
	
	function getTable() {
		global $sBegin, $sEnd, $sDate;
		global $txtTagB, $txtMonatB, $txtJahrB, $txtTagE, $txtMonatE, $txtJahrE;
		$sTable = '
<table border="0" cellpadding="1" cellspacing="1" width="100%">
<tr>
	<th colspan="2" align="left">Projekte</th>
</tr>
<tr>
	<td colspan="2">' . getZeitraum( $this->projekt->sBegin, $this->projekt->sEnd, $this->projekt->sDate ) . '</td>
</tr>
<tr>
		<td align="left">Projekt</th>
		<td align="left">Tage</th>
	</tr>
';
		$rsProjekt = $this->projekt->getResultSet();
		while( $rowProjekt=mysql_fetch_array( $rsProjekt ) ) {
			$sProjekt = $rowProjekt["projekt"];
			$nProjektId = $rowProjekt["projekt_id"];
			$nSumme = getDays( $rowProjekt["summe"] );
			$sTable .= "
<tr>
	<td><a href='javascript:showProjektSchritt( $nProjektId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\"  )'>" . $sProjekt . "</a>&nbsp;[<a href='javascript:showProjektMa( $nProjektId, \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" )'>ma</a>]</td>
	<td><a href='javascript:showProjektSchritt( $nProjektId )'>" . $nSumme . "</a></td>
</tr>
";
		} 
		$sTable .= "<tr>
	<td colspan=\"2\" class=\"klein\" align=\"right\"><a href='javascript:printView( \"" . $sBegin . "\", \"" . $sEnd . "\", \"" . $sDate . "\" );'>Druckansicht</a></td>		
</tr></table>
";
		return $sTable;
	}
	
}
?>