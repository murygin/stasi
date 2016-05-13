<?php
include( "woche.inc" );
/*
* stellt einen kalender dar
*/
class kalender {
	var $aWochen = Array();
	
	function setWoche( $sMySqlDatum ) {
		$woche = new woche;
		$woche->setWoche( $sMySqlDatum );
		$this->aWochen[] = $woche;
	}
	
	function output() {
		echo '<table border="0" cellpadding="1" cellspacing="1" bgcolor="#666666" width="100%">
				<tr>
					<th align="left">Mo</th><th align="left">Di</th><th align="left">Mi</th><th align="left">Do</th><th align="left">Fr</th><th align="left">Sa</th><th align="left">So</th>
				</tr>
		';
		for( $i=0; $i<count( $this->aWochen ); $i++ )
			$this->aWochen[$i]->output();
		echo '</table>
		';
	}
	
	function setStunden( $aTage ) {
		$nWeekCounter=0;
		for( $i=0; $i<count( $aTage ); $i++ ) {
			$bIsSet=false;
			while( !$bIsSet && $nWeekCounter<count($this->aWochen) ) {
				$bIsSet=$this->aWochen[$nWeekCounter]->setStunden( $aTage[$i][0], $aTage[$i][1] );
				$nWeekCounter++;
			}
			$nWeekCounter--;
		}
	}
	
	function setStatus( $sDatum, $nId, $sMessage ) {
		$nWeekCounter=0;
		while( !$bIsSet && $nWeekCounter<count($this->aWochen) ) {
			$bIsSet=$this->aWochen[$nWeekCounter]->setStatus( $sDatum, $nId, $sMessage );
			$nWeekCounter++;
		}
	}
}