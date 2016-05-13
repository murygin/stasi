<?php
include( "tag.inc" );
/*
* stellt eine kalenderwoche dar
*/
class woche {
	var $aTage;
	
	function setWoche( $sMySqlDatum ) {
		$datum = new datum;
		$datum->setDate( $sMySqlDatum );
		$this->aTage = Array();
		$currDay = new tag;
		$currDay->setTag( $datum, "" );
		$this->aTage[]=$currDay;
		while( $datum->nTagWoche>1 ) {
			$nCurrYear = $datum->nJahr;
			$nCurrMonth = $datum->nMonat;
			$nCurrDay = $datum->nTag-1;
			if( $nCurrDay<1 ) {
				if( $nCurrMonth==3 ) {
					$nCurrMonth=2;
					$nCurrDay=28;	
				}
				else {
					if( $nCurrMonth==1 ) {
						$nCurrMonth=12;
						$nCurrDay=31;
						$nCurrYear--;	
					}
					else {
						if( $nCurrMonth==2 || $nCurrMonth==4 || $nCurrMonth==6 || $nCurrMonth==8 || $nCurrMonth==9 || $nCurrMonth==11 ) {
				 			$nCurrMonth--;
							$nCurrDay=31;	
						}
						else {
							$nCurrMonth--;
							$nCurrDay=30;
						}
					}
				}
			}
			if( strlen($nCurrMonth)==1 )
				$nCurrMonth = "0" . $nCurrMonth;
			if( strlen($nCurrDay)==1 )
				$nCurrDay = "0" . $nCurrDay;	
			$datum->setDate( $nCurrYear . "-" . $nCurrMonth . "-" . $nCurrDay );
			$currDay = new tag;
			$currDay->setTag( $datum, "" );
			array_unshift( $this->aTage, $currDay );
		}
		$datum->setDate( $sMySqlDatum );
		while( $datum->nTagWoche<6 ) {
			$nCurrYear = $datum->nJahr;
			$nCurrMonth = $datum->nMonat;
			$nCurrDay = $datum->nTag+1;
			if( $nCurrDay>28 && $nCurrMonth==2 ) {
					$nCurrMonth=3;
					$nCurrDay=1;	
			}
			else {
				if( $nCurrDay>30 && ($nCurrMonth==2 || $nCurrMonth==4 || $nCurrMonth==6 || $nCurrMonth==8 || $nCurrMonth==9 || $nCurrMonth==11 ) ) {
					$nCurrMonth++;
					$nCurrDay=1; 
				}
				else {
					if( $nCurrDay>31 && $nCurrMonth==12 ) {
				 		$nCurrMonth=1;
						$nCurrDay=1;
						$nCurrYear++;	
					}
					else { 
						if( $nCurrDay>31 ) {
							$nCurrMonth++;
							$nCurrDay=1;
						}
					}
				}
			}
			if( strlen($nCurrMonth)==1 )
				$nCurrMonth = "0" . $nCurrMonth;
			if( strlen($nCurrDay)==1 )
				$nCurrDay = "0" . $nCurrDay;		 
			$datum->setDate( $nCurrYear . "-" . $nCurrMonth . "-" . $nCurrDay );
			$currDay = new tag;
			$currDay->setTag( $datum );
			array_push( $this->aTage, $currDay );
		}	
		if( $datum->nTagWoche==6 ) {
			$nCurrYear = $datum->nJahr;
			$nCurrMonth = $datum->nMonat;
			$nCurrDay = $datum->nTag+1;
			if( $nCurrDay>28 && $nCurrMonth==2 ) {
					$nCurrMonth=3;
					$nCurrDay=1;	
			}
			else {
				if( $nCurrDay>30 && ($nCurrMonth==2 || $nCurrMonth==4 || $nCurrMonth==6 || $nCurrMonth==8 || $nCurrMonth==9 || $nCurrMonth==11 ) ) {
					$nCurrMonth++;
					$nCurrDay=1; 
				}
				else {
					if( $nCurrDay>31 && $nCurrMonth==12 ) {
				 		$nCurrMonth=1;
						$nCurrDay=1;
						$nCurrYear++;	
					}
					else { 
						if( $nCurrDay>31 ) {
							$nCurrMonth++;
							$nCurrDay=1;
						}
					}
				}
			}
			if( strlen($nCurrMonth)==1 )
				$nCurrMonth = "0" . $nCurrMonth;
			if( strlen($nCurrDay)==1 )
				$nCurrDay = "0" . $nCurrDay;		 
			$datum->setDate( $nCurrYear . "-" . $nCurrMonth . "-" . $nCurrDay );
			$currDay = new tag;
			$currDay->setTag( $datum );
			array_push( $this->aTage, $currDay );
		}
	}
	
	function output() {
		echo '<tr>
		';
		for( $i=0; $i<count( $this->aTage ); $i++ )
			$this->aTage[$i]->output();
		echo '
			</tr>
			';
	}
	
	function setStunden( $sDatum, $nStunden ) {
		$bIsSet=false;
		$nDayCounter=0;
		while( !$bIsSet && $nDayCounter<count($this->aTage) ) {
			if( $this->aTage[$nDayCounter]->datum->compare( $sDatum )==0 ) {
				$this->aTage[$nDayCounter]->sEintrag=$this->aTage[$nDayCounter]->sEintrag+$nStunden/3600;
				$this->aTage[$nDayCounter]->setStatus( 1 );	
				$bIsSet=true;
			}
			if( $this->aTage[$nDayCounter]->datum->compare( $sDatum )==1 )
					$bIsSet=true;	
			$nDayCounter++;
		}
		return $bIsSet;
	}
	
	function setStatus( $sDatum, $nId, $sMessage ) {
		$bIsSet=false;
		$nDayCounter=0;
		while( !$bIsSet && $nDayCounter<count($this->aTage) ) {
			if( $this->aTage[$nDayCounter]->datum->compare( $sDatum )==0 ) {
				$this->aTage[$nDayCounter]->setStatus( $nId );
				$this->aTage[$nDayCounter]->sMessage=$sMessage;
			}
			if( $this->aTage[$nDayCounter]->datum->compare( $sDatum )==1 )
				$this->aTage[$nDayCounter]->setStatus( 1 );	
			$nDayCounter++;
		}
		return $bIsSet;
	}
}