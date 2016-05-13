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

/**
* waehlt den eintrag einer selectbox mit dem value sValue
* die select box liegt im frame winCurr im formular sFormName
* und heisst sCmbName
*
* code: FORK-ds
*/
function selectCmbByValue( winCurr, sFormName, sCmbName, sValue ) {
	var cmb=getFormElement( this, sFormName, sCmbName );
	if( cmb!=null ) {
		for( i=0; i<cmb.options.length; i++ ) {
			if( cmb.options[i].value==sValue )
				cmb.options[i].selected=true;	 
		}
	}
}

/**
* waehlt den eintrag einer selectbox mit dem text sText
* die select box liegt im frame winCurr im formular sFormName
* und heisst sCmbName
*
* code: FORK-ds
*/
function selectCmbByText( winCurr, sFormName, sCmbName, sText ) {
	var cmb=getFormElement( this, sFormName, sCmbName );
	if( cmb!=null ) {
		for( i=0; i<cmb.options.length; i++ ) {
			if( cmb.options[i].text==sText )
				cmb.options[i].selected=true;	
		}
	}
}

/**
* gibt die values der ausgewaehlten checkboxen einer checkboxgruppe
* mit dem namen sCbName als array zurueck
*
* code: FORK-ds
*/
function getSelectedCbValue( winCurr, sFormName, sCbName ) {
	var cb=getFormElement( this, sFormName, sCbName );
	if( cb!=null ) {
		var aValue = new Array();
		if( cb.value!=null ) {
			//checkbox mit einem eintrag
			if( cb.checked )
				aValue[aValue.length]=cb.value;
		}
		else {
			//checkbox mit mehreren eintraegen	
			for( i=0; i<cb.length; i++ ) {
		 		if( cb[i].checked ) {
		 			aValue[aValue.length]=cb[i].value;
		 		}
			}
		}
		return aValue;
	}
	else
		return null;
}

/**
* gibt die values der ausgewaehlten radiobuttons einer radiobuttongruppe
* mit dem namen sRbName als array zurueck
*
* code: FORK-ds
*/
function getSelectedRbValue( winCurr, sFormName, sRbName ) {
 	var aValue=getSelectedCbValue( winCurr, sFormName, sRbName );
 	if( aValue!=null ) {
 		if( aValue.length>0 ) {
 			return aValue[0];
 		}
 		else
 			return null;
 	}
 	else
 		return null;
}



