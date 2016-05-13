var regZahl=/[0-9]/;
var aEmptyFields;
var aNumberErrorFields;
/**
+ ueberprueft formfelder auf inhalt
* die namen der einzelnen formfelder werden als array aFormFields
* uebergeben, die formfelder befinden sich im formular sFormName
* im fenster winCurr
* sind alle felder ausgefuellt, wird true zurueckgegeben, wenn nicht
* false
* die namen von leeren feldern werden im array aEmptyFields gespeichert
*
* ACHTUNG die art des feldes wird am namen erkannt. die namen muessen daher
* laut namenskonvention vergeben sein:
* textfeld: txt[name], textarea: txa[name]
* radio: rb[name], checkbox: cb[name], select-/conmbobox: cmb[name]
*
* ACHTUNG unterstuetzt noch kein selectboxen
*
* code: FORK-ds
*
* @param winnCurr Frame
* @param sFormName String
* @param aFormFields Array of Strings
* @return boolean
*/
function checkEmptyness( winCurr, sFormName, aFormFields ) {
	aEmptyFields=new Array();
	var bIsValue=true;
	var currElement;
   for( k=0;k<aFormFields.length;k++ ) {
   	currElement = getFormElement( winCurr, sFormName, aFormFields[k] );
   	if( currElement!=null ) {
   		if( aFormFields[k].indexOf("txt")!=-1 || aFormFields[k].indexOf("txa")!=-1 ) {
   	 		//textfield textarea
   			if( currElement.value=="" || currElement.value==null ) {
   				bIsValue=false;
   				aEmptyFields[aEmptyFields.length]=getTitle(aFormFields[k]);	
   			}
   		}
   		if( aFormFields[k].indexOf("rb")!=-1 ) {
   		 	if( getSelectedRbValue( winCurr, sFormName, aFormFields[k] )==null ) {
   		 		bIsValue=false;
   				aEmptyFields[aEmptyFields.length]=getTitle(aFormFields[k]);
   		 	}
   		}
   		if( aFormFields[k].indexOf("cb")!=-1 ) {
   		 	if( getSelectedCbValue( winCurr, sFormName, aFormFields[k] )==null ) {
   		 		bIsValue=false;
   				aEmptyFields[aEmptyFields.length]=getTitle(aFormFields[k]);
   		 	}	
   		}
   		if( aFormFields[k].indexOf("cmb")!=-1 ) {
   		 	if( getSelectedCmbValue( winCurr, sFormName, aFormFields[k] )==null ) {
   		 		bIsValue=false;
   				aEmptyFields[aEmptyFields.length]=getTitle(aFormFields[k]);
   		 	}	
   		}
   		if( aFormFields[k].indexOf("mcb")!=-1 ) {
   		 	if( getSelectedCmbValue( winCurr, sFormName, aFormFields[k] )==null ) {
   		 		bIsValue=false;
   				aEmptyFields[aEmptyFields.length]=getTitle(aFormFields[k]);
   		 	}	
   		}
   	}
   	else
   		bIsValue=false;	 	
   }
   return bIsValue;
}
/**
* ueberprueft formfelder auf zahlen
* die namen der einzelnen formfelder werden als array aFormFields
* uebergeben, die formfelder befinden sich im formular sFormName
* im fenster winCurr
* enthalten alle felder ausschliesslich zahlen wird true zurueckgegeben
* sonst false
* im array aExceptions einzelne zeichen als ausnahmen uebergeben werden.
* ist eine dieser ausnahmen vorhanden wird nicht false zurueckgegeben.
*
* die namen von feldern mit zahlen werden im array aNumberErrorFileds
* gespeichert
*
* code: FORK-ds
*
* @param winnCurr Frame
* @param sFormName String
* @param aFormFields Array of Strings
* @param aExceptions Array of Chars
* @return boolean
*/
function checkForNumbers( winCurr, sFormName, aFormFields, aExceptions ) {
	aNumberErrorFields=new Array();
	var bIsValue=true;
	var currElement;
   for( m=0;m<aFormFields.length;m++ ) {
   	currElement = getFormElement( winCurr, sFormName, aFormFields[m] );
   	if( currElement!=null ) {
   		if( currElement.value!=null && currElement.value!="" ) {
   			if( !isNumber(currElement.value,aExceptions) ) {
   				bIsValue=false;
   				aNumberErrorFields[aNumberErrorFields.length]=getTitle( aFormFields[m] );	
   			}
   		}			
   	}
   	else
   		bIsValue=false;	 	
   }
   return bIsValue;
}

/**
* prueft ob sEmail eine korrekte emailadresse ist
* wenn ja wird true zurueckgeben,
* wenn nein false
*
* code: FORK-ds
*
* @param sEmail String
* @return boolean
*/
function isEmail( sEmail ) {
	var bIsOk = sEmail.indexOf("@")!=-1 &&
				  	sEmail.indexOf(".")!=-1 &&
	        		sEmail.indexOf("@")<sEmail.lastIndexOf(".") &&
	        		(sEmail.lastIndexOf(".")+5)>sEmail.length &&
	        		(sEmail.lastIndexOf(".")<(sEmail.length-2) ) &&
	        		sEmail.indexOf("@")!=0;
	return bIsOk;
}
/**
* prueft ob der uebergeben string sNumber ausschliesslich
* aus zahlen besteht oder eines der zeichen aus dem array
* aChar (aChar darf null sein). wenn ja wird true zurueckgeben,
* wenn nein false
*
* code: FORK-ds
*
* @param sNumber String
* @param aExceptions Array of Chars
* @return boolean
*/
function isNumber( sNumber, aExceptions ) {
	var bIsNumber=true;
	for( n=0;n<sNumber.length;n++ ) {
		if( !regZahl.test( sNumber.charAt(n) ) )
			bIsNumber=false;
		if( aExceptions!=null ) {
			for( i2=0; i2<aExceptions.length; i2++ ) {
		 		if( sNumber.charAt(n)==aExceptions[i2] )
		 			bIsNumber=true;	
			}
		}	
	}
	return bIsNumber;	
}

/**
* gibt einen namen fuer die ausgabe fuer ein formfeld zurueck
* dazu wird das typekuerzel des formfeldnamens entfernt
* falls kein bekanntes kuerzel vorhanedne ist wird sFormFieldName
* zurueckgegeben
*
* code: FORK-ds
*
* @param sFormFieldName String
* @return String
*/
function getTitle( sFormFieldName ) {
	if( sFormFieldName.indexOf("txt")!=-1 ) {
	 	return sFormFieldName.substring( sFormFieldName.indexOf("txt")+3, sFormFieldName.length );
	}
	else
		if( sFormFieldName.indexOf("txa")!=-1 ) {
	 		return sFormFieldName.substring( sFormFieldName.indexOf("txa")+3, sFormFieldName.length );
		}
		else
			if( sFormFieldName.indexOf("rb")!=-1 ) {
	 			return sFormFieldName.substring( sFormFieldName.indexOf("rb")+2, sFormFieldName.length );
			}
			else
				if( sFormFieldName.indexOf("cb")!=-1 ) {
	 				return sFormFieldName.substring( sFormFieldName.indexOf("cb")+2, sFormFieldName.length );
				}
				else
					return sFormFieldName;
}