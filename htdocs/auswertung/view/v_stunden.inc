<?php
include( "auswertung/stunden.inc" );
include( "auswertung/lib.inc" ); 
	
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* stellt alle stunden eines tages dar
*/
class v_stunden {
	var $bIsDebug=false;
	
	var $stunden;
	
	function v_stunden( $nMaId, $sDate ) {
		$this->stunden = new stunden( $nMaId );
		$this->stunden->sDate=$sDate;
	}
	
	function getTable() { 
		$rsStunden = $this->stunden->getResultSet();
		$sTable = '<table border="0" cellpadding="1" cellspacing="1" bgcolor="#666666" width="100%">
					<tr>
						<th colspan="4" align="left">Der ' . getGermanDate( $this->stunden->sDate ) . ' im &Uuml;berblick</th>
					</tr>
					<tr>
						<td>Projekt</td>
						<td>Kategorie</td>
						<td>Beschreibung</td>
						<td>Dauer in h</td>
					</tr>
					';
		while( $rowStunden=mysql_fetch_array( $rsStunden ) ) {
			$nArbeitId = $rowStunden["arbeit_id"];
			$sProjekt = $rowStunden["projekt"];
			$sSchritt = $rowStunden["schritt"];
			$sBeschreibung = $rowStunden["beschreibung"];
			if( $sBeschreibung=="" )
				$sBeschreibung="&nbsp;";
			$nDauer = getHours( $rowStunden["dauer" ] );
			$sTable .= '<tr>
							<td><a href="javascript:openEditWindow( ' . $nArbeitId . ' )">' . $sProjekt . '</a></td>
							<td><a href="javascript:openEditWindow( ' . $nArbeitId . ' )">' . $sSchritt . '</a></td>
							<td><a href="javascript:openEditWindow( ' . $nArbeitId . ' )">' . $sBeschreibung . '</a></td>
							<td><a href="javascript:openEditWindow( ' . $nArbeitId . ' )">' . $nDauer . '</a></td>
						</tr>	
						';
		}
		$sTable .= '</table>';
		return $sTable;
	}
}