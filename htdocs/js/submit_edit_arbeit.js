function checkAndSubmit() {
	var sMissingFields;
	var sError;
	var reg2Zahlen=/[0-9][0-9]/;
	var regKeineZahl=/\D/;
	if( document.fmEditArbeit.txtTag.value=="" ) {
		if( sMissingFields!=null )
			sMissingFields += ", Tag";		
		else
			sMissingFields = "Tag";
	}
	else {
		if( document.fmEditArbeit.txtTag.value.length==1 )
			document.fmEditArbeit.txtTag.value = "0" + document.fmEditArbeit.txtTag.value;
		if( !reg2Zahlen.test( document.fmEditArbeit.txtTag.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Tag!";	
			else
				sError = "Bitte nur Zahlen in Feld Tag!";
			document.fmEditArbeit.txtTag.value="";
		}
		if( document.fmEditArbeit.txtTag.value>31 ) {
			if( sError!=null )
				sError += "\nWelcher Monat hat " + document.fmEditArbeit.txtTag.value + " Tage?";	
			else
				sError = "Welcher Monat hat " + document.fmEditArbeit.txtTag.value + " Tage?";
			document.fmEditArbeit.txtTag.value="";
		}
	}
	if( document.fmEditArbeit.txtMonat.value=="" ) {
		if( sMissingFields!=null )
			sMissingFields += ", Monat";
		else
			sMissingFields = "Monat";
	}
	else {
		if( document.fmEditArbeit.txtMonat.value.length==1 )
			document.fmEditArbeit.txtMonat.value = "0" + document.fmEditArbeit.txtMonat.value;
		if( !reg2Zahlen.test( document.fmEditArbeit.txtMonat.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Monat!";	
			else
				sError = "Bitte nur Zahlen in Feld Monat!";
			document.fmEditArbeit.txtMonat.value="";
		}
		if( document.fmEditArbeit.txtMonat.value>12 ) {
			if( sError!=null )
				sError += "\nEs gibt kein Jaht mit " + document.fmEditArbeit.txtMonat.value + " Monaten?";	
			else
				sError = "Es gibt kein Jaht mit " + document.fmEditArbeit.txtMonat.value + " Monaten?";
			document.fmEditArbeit.txtMonat.value="";
		}
	}
	if( document.fmEditArbeit.txtJahr.value=="" ) {
		if( sMissingFields!=null )
			sMissingFields += ", Jahr";
		else
			sMissingFields = "Jahr";
	}
	else {
		if( document.fmEditArbeit.txtJahr.value.length==1 )
			document.fmEditArbeit.txtJahr.value = "0" + document.fmEditArbeit.txtJahr.value;
		if( !reg2Zahlen.test( document.fmEditArbeit.txtJahr.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Jahr!";	
			else
				sError = "Bitte nur Zahlen in Feld Jahr!";
			document.fmEditArbeit.txtJahr.value="";
		}
	}
	if( document.fmEditArbeit.txtDauer.value=="" ) {
		if( sMissingFields!=null )
			sMissingFields += ", Dauer";
		else
			sMissingFields = "Dauer";
	}
	else {
		if( regKeineZahl.test( document.fmEditArbeit.txtDauer.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Dauer!";	
			else
				sError = "Bitte nur Zahlen in Feld Dauer!";
			document.fmEditArbeit.txtDauer.value="";
		}
	}
	
	if( sError==null && sMissingFields==null ) {
		document.fmEditArbeit.submit();
	}
	else {
		if( sMissingFields!=null )
			alert( "Bitte fülle die folgenden Felder aus: " + sMissingFields );
		if( sError!=null )
			alert( sError ); 	
	}
}

var n,ie;
/**
* ueberprueft welcher browser benutzt wird und belegt die variable n und ie
* mit true oder false
*
* code: fork/ds
*/
function checkBrowser() {
	n = (document.layers) ? 1:0
	ie = (document.all) ? 1:0	
}

/**
* gibt das form mit dem namen sFormName aus dem frame winCurr zurueck
* es ist egal, wo und in welchem layer sich das formular in winCurr befindet
* ist das formular nicht vorhanden, gibt sie methode null zurueck
*
* code: FORK-ds
*/
function getForm( winCurr, sFormName ) {
	if( n==null || ie==null )
		checkBrowser();
	if( winCurr.document.forms[ sFormName ] ) {
		return winCurr.document.forms[ sFormName ];
	}
	if( n ) {
		for( i=0; i<winCurr.document.layers.length; i++ ) { 
			if( winCurr.document.layers[i].document.forms[ sFormName ] ) {
 				return winCurr.document.layers[i].document.forms[ sFormName ];
 			}	 
 		} //end for
	} //end if( n )
	return null;
}

/**
* gibt das formular element mit dem namen sElementName aus dem formular
* sFormName aus dem frame winCurr zurueck.
* es ist egal, wo und in welchem layer sich das formular in winCurr befindet
* ist das formular nicht vorhanden, gibt sie methode null zurueck
*
* code: FORK-ds
*/
function getFormElement( winCurr, sFormName, sElementName ) {
	if( eval( "getForm( winCurr, sFormName )." + sElementName ) )
		return ( eval( "getForm( winCurr, sFormName )." + sElementName ) );
	else
		return null; 	
}

function getSelectedCmbValue( winCurr, sFormName, sCmbName ) {
	if( getFormElement( winCurr, sFormName, sCmbName ) )
		return( getFormElement( winCurr, sFormName, sCmbName ).options[getFormElement( winCurr, sFormName, sCmbName ).options.selectedIndex].value );
	else
		return null;
}

function getSelectedCmbText( winCurr, sFormName, sCmbName ) {
	if( getFormElement( winCurr, sFormName, sCmbName ) )
		return( getFormElement( winCurr, sFormName, sCmbName ).options[getFormElement( winCurr, sFormName, sCmbName ).options.selectedIndex].text );
	else
		return null;
}

function selectCmbByValue( winCurr, sFormName, sCmbName, sValue ) {
	var cmb=getFormElement( this, sFormName, sCmbName );
	if( cmb!=null ) {
		for( i=0; i<cmb.options.length; i++ ) {
			if( cmb.options[i].value==sValue )
				cmb.options[i].selected=true;	 
		}
	}
}
