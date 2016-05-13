<?php
/*
* stellt einen kalendereintrag dar
*/
class tag {
	var $datum;
	var $sEintrag;
	//der status des tages
	//0: keine stunden eingetragen
	//1: stunden eingetragen
	//2: heute
	//21: heute und stunden eingetragen
	var $bHeute;
	var $bStunden;
	
	function setTag( $datum ) {
		$this->datum = $datum;
		$this->sEintrag = 0;
		$this->bHeute=false;
		if( $datum->nTagWoche!=6 && $datum->nTagWoche!=0 )
			$this->bStunden=false;
		else
			$this->bStunden=true;
	}
	
	//0: keine stunden eingetragen
	//1: stunden eingetragen
	//2: heute
	//21: heute und stunden eingetragen
	function setStatus( $nId ) {
		if( $nId==2 )
			$this->bHeute=true;
		if( $nId==1 )
			$this->bStunden=true;	
	}
	
	function output() {
		echo '<td';
		if( !$this->bStunden )
			echo ' class="wichtig"';
		echo '>';
		echo "<a";
		if( $this->bHeute )
			echo ' class="heute"';
		echo " href=\"javascript:selectDatum( '" . $this->datum->sDatum . "')\">" . $this->datum->nTag . ".</a>";
		if( $this->datum->nTag==1 )
			echo $this->datum->nMonat . '.';	
		echo "&nbsp;&nbsp;&nbsp;<a href=\"javascript:selectDatum( '" . $this->datum->sDatum . "')\">";
		echo $this->sEintrag . 'h</a>';
		if( $this->bHeute )
			echo '</font>';
		echo '</td>';
	}
}