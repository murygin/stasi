<?php
/*
* wertet ein datum in der form yyyy-mm-tt aus
*/
class datum {
	var $sDatum;
	var $nJahr;
	var $nMonat;
	var $sMonat;
	var $nTag;
	var $sEnTag;
	var $sTag;
	var $nTagWoche;
	
	var $sLanguage = "german";
	
	function setDate( $sDatum ) {
		$this->sDatum=$sDatum;
		$this->nJahr = substr( $sDatum, 0, 4 );
		$this->nMonat = substr( $sDatum, 5, 2 );
		if( substr( $this->nMonat, 0, 1 )==0 )
			$this->nMonat = substr( $this->nMonat, 1 );
		$this->nTag = substr( $sDatum, 8, 2 );
		if( substr( $this->nTag, 0, 1 )==0 )
			$this->nTag = substr( $this->nTag, 1 );
		$this->nTagWoche = date( "w", strtotime( $this->sDatum ) );
		$this->sEnTag = date( "l", strtotime( $this->sDatum ) );
		switch( $this->sEnTag ) {
			case "Monday": $this->sTag="Montag";break;
			case "Tuesday": $this->sTag="Dienstag";break;
			case "Wednesday": $this->sTag="Mittwoch";break;
			case "Thursday": $this->sTag="Donnerstag";break;
			case "Friday": $this->sTag="Freitag";break;
			case "Saturday": $this->sTag="Samstag";break;
			case "Sunday": $this->sTag="Sonntag";
		}
		switch( $this->nMonat ) {
			case 1: $this->sMonat="Januar"; break;
			case 2: $this->sMonat="Februar"; break;
			case 3: $this->sMonat="M&auml;rz"; break;
			case 4: $this->sMonat="April"; break;
			case 5: $this->sMonat="Mai"; break;
			case 6: $this->sMonat="Juni"; break;
			case 7: $this->sMonat="Juli"; break;
			case 8: $this->sMonat="August"; break;
			case 9: $this->sMonat="September"; break;
			case 10: $this->sMonat="Oktober"; break;
			case 11: $this->sMonat="November"; break;
			case 12: $this->sMonat="Dezember";
		}
	}
	
	/**
	* vergleicht das datum im mysql format $sDatum mit dem datums objekt es wird 0
	* 0 zurueckgegeben falls die daten gleich sind,
	* 1 wenn $sDatum kleiner ist und 
	* 2 wenn $sDatum groesser ist
	*/ 
	function compare( $sDatum ) {
		if( substr( $sDatum, 0, 4 ) > $this->nJahr )
			return 2;	
		else
			if( substr( $sDatum, 0, 4 ) < $this->nJahr )	
				return 1;
			else
				if( substr( $sDatum, 5, 2 ) > $this->nMonat )
					return 2;
				else
					if( substr( $sDatum, 5, 2 ) < $this->nMonat )	
						return 1;
					else
						if( substr( $sDatum, 8, 2 ) > $this->nTag )
							return 2;
						else
							if( substr( $sDatum, 8, 2 ) < $this->nTag )
								return 1;
							else
								return 0;
							
	}
	
}
?>
