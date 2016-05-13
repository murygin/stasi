function submitForm() {
	document.fmArbeit.submit();
}
function checkAndSubmit() {
	var sMissingFields;
	var sError;
	var regZahl=/[0-9][0-9]/;
	if( document.fmArbeit.cmbDatum.options[document.fmArbeit.cmbDatum.selectedIndex].value=="" ) {
		if( document.fmArbeit.txtTag.value=="" ) {
			if( sMissingFields!=null )
				sMissingFields += ", Tag";		
			else
				sMissingFields = "Tag";
		}
		else {
			if( document.fmArbeit.txtTag.value.length==1 )
				document.fmArbeit.txtTag.value = "0" + document.fmArbeit.txtTag.value;
			if( !regZahl.test( document.fmArbeit.txtTag.value ) ) {
				if( sError!=null )
					sError += "\nBitte nur Zahlen in Feld Tag!";	
				else
					sError = "Bitte nur Zahlen in Feld Tag!";
				document.fmArbeit.txtTag.value="";
			}
		}
	
		if( document.fmArbeit.txtMonat.value=="" ) {
			if( sMissingFields!=null )
				sMissingFields += ", Monat";
			else
				sMissingFields = "Monat";
		}
		else {
			if( document.fmArbeit.txtMonat.value.length==1 )
				document.fmArbeit.txtMonat.value = "0" + document.fmArbeit.txtMonat.value;
			if( !regZahl.test( document.fmArbeit.txtMonat.value ) ) {
				if( sError!=null )
					sError += "\nBitte nur Zahlen in Feld Monat!";	
				else
					sError = "Bitte nur Zahlen in Feld Monat!";
				document.fmArbeit.txtMonat.value="";
			}
		}
	
		if( document.fmArbeit.txtJahr.value=="" ) {
			if( sMissingFields!=null )
				sMissingFields += ", Jahr";
			else
				sMissingFields = "Jahr";
		}
		else {
			if( document.fmArbeit.txtJahr.value.length==1 )
				document.fmArbeit.txtJahr.value = "0" + document.fmArbeit.txtJahr.value;
			if( !regZahl.test( document.fmArbeit.txtJahr.value ) ) {
				if( sError!=null )
					sError += "\nBitte nur Zahlen in Feld Jahr!";	
				else
					sError = "Bitte nur Zahlen in Feld Jahr!";
				document.fmArbeit.txtJahr.value="";
			}
		}
	} //end cmbDatum=="" ?
	else {
		if( document.fmArbeit.txtJahr.value!="" || document.fmArbeit.txtMonat.value!="" || document.fmArbeit.txtTag.value!="" ) {
			if( document.fmArbeit.cmbDatum.options[document.fmArbeit.cmbDatum.selectedIndex].value!="20"+document.fmArbeit.txtJahr.value+"-"+document.fmArbeit.txtMonat.value+"-"+document.fmArbeit.txtTag.value )
				if( sError!=null )
					sError += "\nDie Angaben zum Datum sind wiederspr�chlich!";	
				else
					sError = "Die Angaben zum Datum sind wiederspr�chlich!";
		}
	}
	
	if( document.fmArbeit.txtDauerH.value=="" && (document.fmArbeit.txtBeginnH.value=="" && document.fmArbeit.txtEndeH.value=="") ) {
		if( sMissingFields!=null )
			sMissingFields += ", Beginn/Ende oder Dauer";
		else
			sMissingFields = "Beginn/Ende oder Dauer";
	}
	if( document.fmArbeit.txtDauerH.value!="" ) {
		if( document.fmArbeit.txtDauerH.value.length==1 )
			document.fmArbeit.txtDauerH.value = "0" + document.fmArbeit.txtDauerH.value;
		if( !regZahl.test( document.fmArbeit.txtDauerH.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Stunden!";	
			else
				sError = "\nBitte nur Zahlen in Feld Stunden!";
			document.fmArbeit.txtDauerH.value="";
		}
	}
	/*
	if( document.fmArbeit.txtDauerM.value!="" ) {
		if( document.fmArbeit.txtDauerM.value.length==1 )
			document.fmArbeit.txtDauerM.value = "0" + document.fmArbeit.txtDauerM.value;
		if( !regZahl.test( document.fmArbeit.txtDauerM.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld Minuten!";	
			else
				sError = "\nBitte nur Zahlen in Feld Minuten!";
			document.fmArbeit.txtDauerM.value="";
		}
	}
	*/
	if( document.fmArbeit.txtBeginnH.value!="" ) {
		if( document.fmArbeit.txtBeginnH.value.length==1 )
			document.fmArbeit.txtBeginnH.value = "0" + document.fmArbeit.txtBeginnH.value;
		if( !regZahl.test( document.fmArbeit.txtBeginnH.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld f�r die Startzeit!";	
			else
				sError = "\nBitte nur Zahlen in Feld f�r die Startzeit!";
			document.fmArbeit.txtBeginnH.value="";
		}
	}
	if( document.fmArbeit.txtBeginnM )
		if( document.fmArbeit.txtBeginnM.value!="" ) {
			if( document.fmArbeit.txtBeginnM.value.length==1 )
				document.fmArbeit.txtBeginnM.value = "0" + document.fmArbeit.txtBeginnM.value;
			if( !regZahl.test( document.fmArbeit.txtBeginnM.value ) ) {
				if( sError!=null )
					sError += "\nBitte nur Zahlen in Feld f�r die Startzeit!";	
				else
					sError = "\nBitte nur Zahlen in Feld f�r die Startzeit!";
				document.fmArbeit.txtBeginnM.value="";
			}
		}
		
	if( document.fmArbeit.txtEndeH.value!="" ) {
		if( document.fmArbeit.txtEndeH.value.length==1 )
			document.fmArbeit.txtEndeH.value = "0" + document.fmArbeit.txtEndeH.value;
		if( !regZahl.test( document.fmArbeit.txtEndeH.value ) ) {
			if( sError!=null )
				sError += "\nBitte nur Zahlen in Feld f�r die Endzeit!";	
			else
				sError = "\nBitte nur Zahlen in Feld f�r die Endzeit!";
			document.fmArbeit.txtEndeH.value="";
		}
	}
	if( document.fmArbeit.txtEndeM )
		if( document.fmArbeit.txtEndeM.value!="" ) {
			if( document.fmArbeit.txtEndeM.value.length==1 )
				document.fmArbeit.txtEndeM.value = "0" + document.fmArbeit.txtEndeM.value;
			if( !regZahl.test( document.fmArbeit.txtEndeM.value ) ) {
				if( sError!=null )
					sError += "\nBitte nur Zahlen in Feld f�r die Endzeit!";	
				else
					sError = "\nBitte nur Zahlen in Feld f�r die Endzeit!";
				document.fmArbeit.txtEndeM.value="";
			}
		}
	
	if( document.fmArbeit.txtBeginnH.value!="" && document.fmArbeit.txtEndeH.value!="" ) {
		var nBeginnM, nEndeM, nBeginnSek, nEndeSek;
		if( document.fmArbeit.txtBeginnM ) {
			if( document.fmArbeit.txtBeginnM.value=="" )
				nBeginnM=0;
			else
				nBeginnM=document.fmArbeit.txtBeginnM.value;	
		}
		else
			nBeginnM=0;
		if( document.fmArbeit.txtEndeM ) {
			if( document.fmArbeit.txtEndeM.value=="" )
				nEndeM=0;
			else
				nEndeM=document.fmArbeit.txtEndeM.value;
		}
		else
			nEndeM=0;
		nBeginnSek=document.fmArbeit.txtBeginnH.value*3600+nBeginnM*60;
		nEndeSek=document.fmArbeit.txtEndeH.value*3600+nEndeM*60;
		if( nEndeSek<nBeginnSek ) {
			if( sError!=null )
				sError += "\nDas Ende der Arbeitszeit sollte vor dem Anfang liegen, oder?";	
			else
				sError = "Das Ende der Arbeitszeit sollte vor dem Anfang liegen, oder?";		
		}
	}
	if( sError==null && sMissingFields==null ) {
		document.fmArbeit.submit();
	}
	else {
		if( sMissingFields!=null )
			alert( "Bitte f�lle die folgenden Felder aus: " + sMissingFields );
		if( sError!=null )
			alert( sError ); 	
	}
}
/**
* submitted das filter formular
*/
function submitFilter() {
	if( document.fmFilter ) {
		if( document.fmFilter.txtIsFilterSubmit )
			document.fmFilter.txtIsFilterSubmit.value="true";
		document.fmFilter.submit();
	}
}
/**
* oeffnet ein fenster in dem ein neues produkt editiert wird
*/
function openPrintWindow() {
	if( document.fmFilter.cmbFilterProjekt )
		nProjektId = document.fmFilter.cmbFilterProjekt.options[document.fmFilter.cmbFilterProjekt.selectedIndex].value;
	else
		nProjektId="";
	if( nProjektId=="" )
		nProjektId=-1;
	
	if( document.fmFilter.cmbFilterDatum )
		sDatum = document.fmFilter.cmbFilterDatum.options[document.fmFilter.cmbFilterDatum.selectedIndex].value;
	else
		sDatum="";
	if( sDatum=="" )
		sDatum=-1;
	
	if( document.fmFilter.cmbFilterMa )
		nMaiId = document.fmFilter.cmbFilterMa.options[document.fmFilter.cmbFilterMa.selectedIndex].value;
	else
		nMaiId="";
	if( nMaiId=="" )
		nMaiId=-1;
		
	if( document.fmFilter.cmbFilterSchritt )
		nSchrittId = document.fmFilter.cmbFilterSchritt.options[document.fmFilter.cmbFilterSchritt.selectedIndex].value;
	else
		nSchrittId="";
	if( nSchrittId=="" )
		nSchrittId=-1;
	
	wPrint = window.open( "../auswertung/printView.phtml?urlProjektId=" + nProjektId + "&urlDatum=" + sDatum + "&urlMaId=" + nMaiId + "&urlSchrittId=" + nSchrittId,
						  "wPrint",			
						  "toolbar=yes,location=no,directories=no,status=no,menubar=yes,scrollbars=yes,width=600,height=600,resizable=yes");
	if( window.focus )
		wPrint.focus();
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

function selectCmbByText( winCurr, sFormName, sCmbName, sText ) {
	var cmb=getFormElement( this, sFormName, sCmbName );
	if( cmb!=null ) {
		for( i=0; i<cmb.options.length; i++ ) {
			if( cmb.options[i].text==sText )
				cmb.options[i].selected=true;	
		}
	}
}