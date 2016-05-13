<?php
/**
* das fomular zum waehlen der zeitspanne
*/
$aKey=Array();
$aValue=Array();
function setValue( $sKey, $sValue ) {
	global $aKey, $aValue;
	$aKey[]=$sKey;
	$aValue[]=$sValue;
}
/**
* liest die werte des zeit formulars aus und belegt die
* die variablen $sBegin und $sEnd bzw. $sDate
*/
function getTimeValues() {
	global $txtTagB, $txtMonatB, $txtJahrB;
	global $txtTagE, $txtMonatE, $txtJahrE;
	global $txtTag, $txtMonat, $txtJahr;
	global $cmbBegin, $cmbEnd;
	global $sBegin, $sEnd, $sDate;
	global $urlBegin, $urlEnd, $urlDate;
	if( $urlBegin!="" ) {
		if( $urlBegin!="-1" )
			$sBegin=$urlBegin;
	}
	else {
		if( $txtTagB!="" && $txtMonatB!="" && $txtJahrB!="" ) {
			if( strlen( $txtTagB )==1 )
				$txtTagB= "0" . $txtTagB;
			if( strlen( $txtMonatB )==1 )
				$txtMonatB= "0" . $txtMonatB;
			if( strlen( $txtJahrB )==1 )
				$txtJahrB= "0" . $txtJahrB;
			$sBegin='20' . $txtJahrB . '-' . $txtMonatB . '-' . $txtTagB;
		}
		else {
			if( $cmbBegin!="" ) { 
				if( $cmbBegin!="-1" )
					$sBegin=$cmbBegin;
			}
			else
				$sBegin=date( "Y-m" ) . "-01"; 
		}
	}
	if( $urlEnd!="" ) {
		if( $urlEnd!="-1" )
			$sEnd=$urlEnd;
	}
	else {
		if( $txtTagE!="" && $txtMonatE!="" && $txtJahrE!="" ) {
			if( strlen( $txtTagE )==1 )
				$txtTagE= "0" . $txtTagE;
			if( strlen( $txtMonatE )==1 )
				$txtMonatE= "0" . $txtMonatE;
			if( strlen( $txtJahrE )==1 )
				$txtJahrE= "0" . $txtJahrE;
			$sEnd='20' . $txtJahrE . '-' . $txtMonatE . '-' . $txtTagE;
		}
		else {
			if( $cmbEnd!="" ) {
				if( $cmbEnd!="-1" ) {
					$sEnd=$cmbEnd;
				}
			}
			else {
				$nYear=date( "Y" );
				$nMonth=date( "m" );
				if( $nMonth==1 || $nMonth==3 || $nMonth==5 || $nMonth==7 || $nMonth==8 || $nMonth==10 || $nMonth==12 )
					$nDay=31;
				else {
					if( $nMonth==2 ) {
						if( $nYear/4==floor($nYear/4) )
							$nDay=29;
						else
							$nDay=28;
					}
					else
						$nDay=30;
				}
				$sEnd=$nYear . "-" . $nMonth . "-" . $nDay;
			}
		}
	}
	if( $urlDate!="" ) {
		$sDate=$urlDate;
		$sBegin="";
		$sEnd="";
	}
	else {
		if( $txtTag!="" && $txtMonat!="" && $txtJahr!="" ) {
			if( strlen( $txtTag )==1 )
				$txtTag= "0" . $txtTag;
			if( strlen( $txtMonat )==1 )
				$txtMonat= "0" . $txtMonat;
			if( strlen( $txtJahr )==1 )
				$txtJahr= "0" . $txtJahr;
			$sDate='20' . $txtJahr . '-' . $txtMonat . '-' . $txtTag;
			$sBegin="";
			$sEnd="";
		}
	}
}


/*
* gibt einen string zurueck der den zeitraum von $sBegin bis zu $sEnd bzw. $sDate
* beschreibt, $sBegin, $sEnd, $sDate sind daten in mysql format
*/
function getZeitraum( $sBegin, $sEnd, $sDate ) {
	global $txtTagB,$txtMonatB,$txtJahrB;
	global $txtTagE,$txtMonatE,$txtJahrE;
	global $urlBegin, $urlEnd;
	$sZeitraum = "Zeitraum: ";
	if( $sBegin!="" || $sEnd !="" ) {
		if( $sBegin=="" ) {
			$sZeitraum .= "Projektbeginn bis ";
		}
		else {
			if( ($txtTagB!="" && $txtMonatB!="" && $txtJahrB!="") || $urlBegin!="" )
				$sZeitraum .= getGermanDate( $sBegin ) . " bis ";	
			else
				$sZeitraum .= substr( $sBegin, 5, 2 ). "/" . substr( $sBegin, 0, 4 ) . " bis ";
		}
		if( $sEnd=="" ) {	
			$sZeitraum .= "heute";
		}
		else {
			if( ($txtTagE!="" && $txtMonatE!="" && $txtJahrE!="") || $urlEnd!="" )
				$sZeitraum .= getGermanDate( $sEnd );
			else
				$sZeitraum .= substr( $sEnd, 5, 2 ). "/" . substr( $sEnd, 0, 4 );
		}
	}			
	else {
		if( $sDate!="" ) {
			$sZeitraum = "Daten vom " . getGermanDate( $sDate );
		}
		else
			$sZeitraum = "Gesamt&uuml;bersicht";	
		}
		return $sZeitraum;
}

function printTimeTable() {
	global $aKey, $aValue, $sBegin, $sEnd, $PHP_SELF;
	global $txtTag, $txtMonat, $txtJahr;
	echo '
	<table border="0" cellpadding="1" cellspacing="1" width="100%">
	<form name="fmTime" action="' . $PHP_SELF . '" method="post">
';

	for( $i=0;$i<count($aKey);$i++ ) {
		echo '<input type="hidden" name="' . $aKey[$i] . '" value="' . $aValue[$i] . '">';
	}

	echo '<tr>
			<td width="100%">&nbsp;</td>
			<td>Anfang</td>
			<td><input name="txtTagB" type="text" size="2" maxlength="2">.<input name="txtMonatB" type="text" size="2" maxlength="2">.20<input name="txtJahrB" type="text" size="2" maxlength="2"></td>
			<td>Ende</td>
			<td><input name="txtTagE" type="text" size="2" maxlength="2">.<input name="txtMonatE" type="text" size="2" maxlength="2">.20<input name="txtJahrE" type="text" size="2" maxlength="2"></td>
		  	<td>Tag<input name="txtTag" type="text" size="2" maxlength="2">.<input name="txtMonat" type="text" size="2" maxlength="2">.20<input name="txtJahr" type="text" size="2" maxlength="2"></td>
		  </tr>
		  <tr>
		  	<td width="100%">&nbsp;</td>
			<td align="right">&nbsp;</td>
			<td><select name="cmbBegin" size="1" onChange="cmbBeginClicked()">';
	
	$nMonth = date( "m" );
	$nYear = date( "Y" );
	for( $i=0; $i<12; $i++ ) {
		echo '<option value="' . $nYear . '-' . $nMonth . '-01">' . $nMonth . '/' . $nYear;
		$nMonth--;
		if( $nMonth<1 ) {
			$nMonth=12;
			$nYear--;
		}	
		if( strlen($nMonth)==1 )
			$nMonth = "0" . $nMonth;
	}
	echo '<option value="-1">offen';
		
	echo '</select></td>
		  <td>&nbsp;</td>
		  <td><select name="cmbEnd" size="1">';
	
	$nMonth = date( "m" );
	$nYear = date( "Y" );
	for( $i=0; $i<12; $i++ ) {
		if( $nMonth==1 || $nMonth==3 || $nMonth==5 || $nMonth==7 || $nMonth==8 || $nMonth==10 || $nMonth==12 )
			$nDay=31;
		else {
			if( $nMonth==2 ) {
				if( $nYear/4==floor($nYear/4) )
					$nDay=29;
				else
					$nDay=28;
			}
			else
				$nDay=30;
		}
		echo '<option value="' . $nYear . '-' . $nMonth . '-' . $nDay . '">' . $nMonth . '/' . $nYear;
		$nMonth--;
		if( $nMonth<1 ) {
			$nMonth=12;
			$nYear--;
		}	
		if( strlen($nMonth)==1 )
			$nMonth = "0" . $nMonth;
	}
	echo '<option value="-1">offen';
		
	echo '</select></td>
		  <td><input type="submit" value="Zeitraum w&auml;hlen" class="form"></td>
			</tr>
		</form>
		</table>
';
		echo '
	<script type="text/javascript" language="JavaScript">
	';
		if( $sBegin!="" ) {
			echo 'selectCmbByValue( this, "fmTime", "cmbBegin", "' . $sBegin . '" );
	';
		}
		else {
			echo 'selectCmbByValue( this, "fmTime", "cmbBegin", "-1" );
	';
		}
		if( $sEnd!="" ) {
			echo 'selectCmbByValue( this, "fmTime", "cmbEnd", "' . $sEnd . '" );
	';
		}
		else {
			echo 'selectCmbByValue( this, "fmTime", "cmbEnd", "-1" );
	';
		}
		echo '</script>
	';
}

?>
