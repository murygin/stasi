<?php
$bIsLocal=true;
//set db connection:
if( !$bIsDbConnected )
	include("stasi_db_settings.inc");
	
/*
* Repraesentiert einen Eintrag der Datenbanktabelle Arbeit
*/
class arbeit {
	var $bIsDebug=false;

	var $bShowAlways=false;
	
	var $nArbeitId;
	var $nMaId;
	var $nProjektId;
	var $nSchrittId;
	var $sBeschreibung;
	var $sBeginn;
	var $sEnde;
	var $nDauer;
	var $nStunden;
	var $nMinuten;
	var $sDatum;
	var $nTag;
	var $nMonat;
	var $nJahr;
	
	var $rsArbeit;
	var $sTable;
	
	//filter variablen
	var $rsFilterProjekt;
	var $rsFilterSchritt;
	var $rsFilterMa;
	var $sFilterBeginn;
	var $sFilterEnde;
	
	var $sDbBeginn;
	var $sDbEnde;
	var $nDbMaId;
	var $nDbPmId;
	var $nDbProjektId;
	var $nDbSchrittId;
	
	var $bProjektFilter=false;
	var $bSchrittFilter=false;
	var $bZeitFilter=false;
	var $bMaFilter=false;
	
	/*
	* Belegt die Membervariablen mit den Werten aus dem querystring
	*/
	function setValues( $nEintrag ) {
		global $txtArbeitId, $txtMaId, $txtJahr, $txtMonat, $txtTag, $cmbDatum;
		global $HTTP_POST_VARS;
		
		$this->nArbeitId=$txtArbeitId;
		$this->nMaId=$txtMaId;
		
		$this->nSchrittId=$HTTP_POST_VARS["cmbSchritt" . $nEintrag];
		$this->sBeschreibung=$HTTP_POST_VARS["txtBeschreibung" . $nEintrag];
		$this->nDauer=$HTTP_POST_VARS["txtDauer" . $nEintrag]*3600;
		
		if( $txtJahr>90 )
			$txtJahr="19" . $txtJahr;
		else
			$txtJahr="20" . $txtJahr;	
		if( $txtJahr!="" && $txtMonat!="" && $txtTag!="" )
			$this->sDatum=$txtJahr . "-" . $txtMonat . "-" . $txtTag;
		else
			$this->sDatum=$cmbDatum;
	}
	
	/*
	* Ueberprueft ob alle not null Werte gesetzt sind
	*/
	function checkValues() {
		return( $this->nMaId!="" &&
				$this->nSchrittId!="" &&
				$this->sDatum!="" &&
				($this->sBeginn!="" && $this->sEnde!="" || $this->nDauer!="" ) );	
	}
	
	/**
	* gibt das where stmt mit den gesetzten filtern zurueck fuer die
	* tabelle arbeit zurueck
	*/
	function getWhereStmt() {
		$sWhrereStmt="arbeit.schritt_id=schritt.schritt_id and schritt.projekt_id=projekt.projekt_id and arbeit.ma_id=ma.ma_id";	
		//filter
		if( $this->nDbPmId!="" )
			$sWhrereStmt.=" and projekt.pm_id=$this->nDbPmId";
		if( $this->nDbMaId!="" ) 
			$sWhrereStmt.=" and arbeit.ma_id=$this->nDbMaId";
		if( $this->sDbBeginn!="" )
			$sWhrereStmt.=" and datum>='$this->sDbBeginn'";
		if( $this->sDbEnde!="" ) 
			$sWhrereStmt.=" and datum<='$this->sDbEnde'";
		if( $this->nDbProjektId!="" ) 
			$sWhrereStmt.=" and arbeit.schritt_id=schritt.schritt_id and schritt.projekt_id=$this->nDbProjektId";
		if( $this->nDbSchrittId!="" ) 
			$sWhrereStmt.=" and arbeit.schritt_id=$this->nDbSchrittId";
		return $sWhrereStmt;
	}
	
	/**
	* erstellt ein resultset fuer die ausgabe der asreitsschritte
	*/
	function setResultSet() {
		$sWhrereStmt=$this->getWhereStmt();	
		$sWhrereStmt.=" order by projekt,datum,schritt,vorname";
		
		$this->rsArbeit = $this->selectTables( "arbeit.arbeit_id,projekt.bezeichnung as projekt,schritt.bezeichnung as schritt, concat( ma.vorname,' ',ma.name) as name, beschreibung,dauer,datum",
								  		 	   "arbeit,projekt,schritt,ma",
								  		 	   $sWhrereStmt );
	}
	
	/**
	* initialisiert die selectboxen fuer das filter-fomular
	*/
	function initFilter() {
		global $cmbFilterProjekt, $cmbFilterSchritt, $cmbFilterDatum, $cmbFilterMa;
		//die werte der filter selectboxen werden ausgelesen:
		if( $cmbFilterProjekt!="" )
			$this->nDbProjektId=$cmbFilterProjekt;
		if( $cmbFilterSchritt!="" )
			$this->nDbSchrittId=$cmbFilterSchritt;
		if( $cmbFilterDatum!="" ) {
			$this->sDbBeginn=$cmbFilterDatum;
			$nYahr=substr( $this->sDbBeginn, 0, 4 );
			$nMonat=substr( $this->sDbBeginn, 5, 2 );
			$this->sDbEnde=$nYahr . "-" . $nMonat . "-" . "31";
		}
		if( $cmbFilterMa!="" )
			$this->nDbMaId=$cmbFilterMa;
			
		//die sql-stmts fuer das fuellen der filter slectboxen werden bestimmt:
		//projekt filter
		if( $this->bProjektFilter ) {
			$sqlProjekt = "select distinct projekt.projekt_id,bezeichnung from projekt,ma_projekt";
			if( $this->nDbPmId!="" ) 
				$sqlProjekt .= " where projekt.pm_id=$this->nDbPmId";
			else 
				if( $this->nDbMaId!="" )
					$sqlProjekt .= " where ma_projekt.projekt_id=projekt.projekt_id and ma_projekt.ma_id=$this->nDbMaId or projekt.pm_id=$this->nDbMaId"; 
			$sqlProjekt .= " order by bezeichnung";
			$this->rsFilterProjekt = mysql_query( $sqlProjekt )
					or die( dbError( $sqlProjekt ) );
		}
		//schritt filter
		if( $this->bSchrittFilter && $this->nDbProjektId!="" ) {
			$sqlSchritt = "select distinct schritt_id,bezeichnung from schritt where projekt_id=$this->nDbProjektId";
			$sqlSchritt .= " order by bezeichnung";
			$this->rsFilterSchritt = mysql_query( $sqlSchritt )
					or die( dbError( $sqlSchritt ) );
		}
		//zeit filter
		if( $this->bZeitFilter ) {
			if( $this->sDbBeginn!="" ) {
				$sTempBeginn=$this->sDbBeginn;
				$this->sDbBeginn="";
			}
			if( $this->sDbEnde!="" ) {
				$sTempEnde=$this->sDbEnde;
				$this->sDbEnde="";
			}
			$rsFilterMonat = $this->selectTables( "max(datum) as max,min(datum) as min",
											  	  "arbeit,projekt,schritt,ma",
								  		 	  	  $this->getWhereStmt() );
			if( $sTempBeginn!="" ) {
				$this->sDbBeginn=$sTempBeginn;
				$sTempBeginn="";
			}
			if( $sTempEnde!="" ) {
				$this->sDbEnde=$sTempEnde;
				$sTempEnde="";
			}
			$rowMonat=mysql_fetch_array( $rsFilterMonat );
			$this->sFilterBeginn=substr( $rowMonat["min"], 0, 7 );
			$this->sFilterEnde=substr( $rowMonat["max"], 0, 7 );
			$nYahr=substr( $this->sFilterEnde, 0, 4 );
			$nMonat=substr( $this->sFilterEnde, 5, 2 );
			$nMonat++;
			if( $nMonat>12 ) {
			$nMonat="01";
			$nYahr++;
			}
			$this->sFilterEnde=$nYahr . "-" . $nMonat;
		}
		//ma filter
		if( $this->bMaFilter ) {
			$sqlMa="select distinct ma.ma_id,concat(vorname,' ',name) as name from ma";
			if( $this->nDbPmId!="" ) 
				$sqlMa .= ",ma_projekt,projekt where (ma.ma_id=ma_projekt.ma_id and ma_projekt.projekt_id=projekt.projekt_id and projekt.pm_id=$this->nDbPmId) or ma.ma_id=$this->nDbPmId";
			$this->rsFilterMa = mysql_query( $sqlMa )
					or die( dbError( $sqlMa ) );
		}
	}
	
	/**
	* erstellt die filter-tabellenzeile
	*/
	function getFilter() {
		if( $this->bProjektFilter )
			$this->bProjektFilter=mysql_num_rows( $this->rsFilterProjekt )>0;
		$this->bZeitFilter=$this->sFilterBeginn!="";
		if( $this->bMaFilter )
			$this->bMaFilter=mysql_num_rows( $this->rsFilterMa )>0;
		if( $this->bProjektFilter || $this->bZeitFilter ) {
			$sFilter = '<form name="fmFilter" action="' . $PHP_SELF . '"  method="post">
						<input name="txtIsFilterSubmit" type="hidden">
						<tr>					
							<td colspan="5" align="right" class="form">';
			if( $this->bProjektFilter ) {
				$sFilter.= '<select class="form" name="cmbFilterProjekt" size="1" onChange="cmbFilterProjektClicked();">
								<option value="">Projekt
								<option value="">-------';
				while( $rowProjekt=mysql_fetch_array( $this->rsFilterProjekt ) ){
					$sProjekt=$rowProjekt["bezeichnung"];
					$nProjektId=$rowProjekt["projekt_id"];
					$sFilter .= '<option value="' . $nProjektId . '">' . $sProjekt;
				}
				$sFilter.= '</select>
							';
			}
			if( $this->bSchrittFilter ) {
				$sFilter.= '<select class="form" name="cmbFilterSchritt" size="1">
								<option value="">Arbeitsschritt
								<option value="">-------';
				if( $this->rsFilterSchritt=="" ) {
					$sFilter .= '<option value="">bitte erst';
					$sFilter .= '<option value="">Projekt w&auml;hlen';	
				}
				else
					while( $rowSchritt=mysql_fetch_array( $this->rsFilterSchritt ) ){
						$sSchritt=$rowSchritt["bezeichnung"];
						$nSchrittId=$rowSchritt["schritt_id"];
						$sFilter .= '<option value="' . $nSchrittId . '">' . $sSchritt;
					}
				$sFilter.= '</select>
							';
			}
			if( $this->bZeitFilter ) {
				$sFilter.= '<select class="form" name="cmbFilterDatum" size="1">
								<option value="">Zeitraum
								<option value="">--------';
					do {
						$nYahr=substr( $this->sFilterBeginn, 0, 4 );
						$nMonat=substr( $this->sFilterBeginn, 5, 2 );
						$sFilter.=  '<option value="' . $nYahr . '-' . $nMonat . '-' . '01">' . $nMonat . '/' . $nYahr;
						if( $this->sFilterBeginn!=$this->sFilterEnde ) {
						$nMonat++;
						if( $nMonat>12 ) {
							$nMonat="01";
							$nYahr++;
						}
					}
					$this->sFilterBeginn=$nYahr . "-" . $nMonat;
				} while( $this->sFilterBeginn!=$this->sFilterEnde ); 
				$sFilter.= '</select>
							';
			}
			if( $this->bMaFilter ) {
				$sFilter.= '<select class="form" name="cmbFilterMa" size="1">
								<option value="">Mitarbeiter
								<option value="">-----------';
				while( $rowMa=mysql_fetch_array( $this->rsFilterMa) ){
					$sMa=$rowMa["name"];
					$nMaId=$rowMa["ma_id"];
					$sFilter .= '<option value="' . $nMaId . '">' . $sMa;
				}
				$sFilter.= '</select>
						</td></tr>';
			} 
			$sFilter.= '<tr>
					<td class="form" colspan="5" align="right"><input class="form" type="button" value="Filter setzen" onClick="submitFilter()"><input class="form" type="button" value="Druckansicht" onClick="openPrintWindow();">
					</td>
				</tr>
				</form>
				';
		}
		return $sFilter;
	}
	
	/**
	* erstellt eine tabelle mit den arbeitseintraegen eines ma
	*/
	function setTable() {
		global $PHP_SELF, $txtIsFilterSubmit;
		$this->initFilter();
		$sFilter = $this->getFilter();
		
		$this->setResultSet();
		if( mysql_num_rows( $this->rsArbeit )>0 || $sFilter!="" ) {
			
			$this->sTable= '<table width="580"><tr><td class="hintergrund"> 
							<table border="0" cellpadding="1" cellspacing="1" bgcolor="#666666" width="100%">
							';
			$this->sTable .= $sFilter;
			if( mysql_num_rows( $this->rsArbeit )>0 && ($this->bShowAlways||$txtIsFilterSubmit=="true") ) {
				$bShowSum=false;
				while( $rowArbeit=mysql_fetch_array( $this->rsArbeit ) ) {
					$datum = new datum;
					$datum->setDate( $rowArbeit["datum"] );
					$nArbeitId = $rowArbeit["arbeit_id"]; 
					$sName = $rowArbeit["name"];
					$nDauer = $rowArbeit["dauer"];
					$sProjekt = $rowArbeit["projekt"];
					$sSchritt = $rowArbeit["schritt"];
					$sBeschreibung = $rowArbeit["beschreibung"];
					
					$nDauerH = floor( $nDauer/3600 );
					$nDauerM = floor( ($nDauer-$nDauerH*3600)/60 );
					if( $nDauerM=="0" )
						$nDauerM="00"; 
					
					if( $sBeschreibung=="" )
						$sBeschreibung="&nbsp;";
					if( $sOldProjekt!=$sProjekt) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSum( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						$this->sTable .= '<tr>
											<th bgcolor="#444466" colspan="5" align="left">' . $sProjekt . '</th>
								  		</tr>
								  		';
					}
					if( $sOldMonth!=$datum->sMonat || $sOldProjekt!=$sProjekt ) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSum( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						$this->sTable .= '<tr>
					  						<td bgcolor="#444466" colspan="5">' . $datum->sMonat . ' ' . $datum->nJahr . '</td>
								  		</tr>
								  		';
					}
					if( $sSchritt!=$sOldSchritt || $sOldProjekt!=$sProjekt || $sOldMonth!=$datum->sMonat ) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSum( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						$this->sTable .= '<tr>
					  						<td bgcolor="#444466" colspan="5">' . $sSchritt . '</td>
								  		</tr>
								  		';	
					}
					if( $sOldName!=$sName || $sSchritt!=$sOldSchritt || $sOldProjekt!=$sProjekt || $sOldMonth!=$datum->sMonat )		
						$sTdName = $sName;
					else
						$sTdName = "s.o.";
					$this->sTable .= '<tr>
					  					<td bgcolor="#444466" align="right" width="10%">&nbsp;<a href="' . $PHP_SELF .'?urlArbeitId=' . $nArbeitId . '">' . $datum->nTag . '.' . $datum->nMonat . '.</a>&nbsp;</td>	
										<td bgcolor="#444466" width="7%">&nbsp;' . substr( $datum->sTag, 0, 2 ) . '&nbsp;</td>	
										<td bgcolor="#444466" width="7%" align="right">&nbsp;' . $nDauerH . ':' . $nDauerM . '</td>
										<td bgcolor="#444466" width="51%">' . $sBeschreibung . '</td>
										<td bgcolor="#444466" width="25%">' . $sTdName . '</td>
					 				</tr>
					 				';
					
					$nSumme = $nSumme+$nDauer;
					$nSummeH = floor( $nSumme/3600 );
					$nSummeM = floor( ($nSumme-$nSummeH*3600)/60 );
					if( $nSummeM=="0" )
						$nSummeM="00";
					
					$bShowSum=true;	
					$sOldMonth=$datum->sMonat;
					$sOldProjekt=$sProjekt;	
					$sOldName=$sName;	
					$sOldSchritt=$sSchritt;	
				}
				$this->sTable .= $this->getRowSum( $nSummeH,$nSummeM );
			} //if( mysql_num_rows( $rsArbeit )>0 )
			$this->sTable .= '</table></td></tr></table>';
		}
	}
	
	
	/**
	* erstellt eine tabelle fuer die druckansicht mit den arbeitseintraegen eines ma
	*/
	function setPrintTable() {
		global $PHP_SELF;
		$this->initFilter();
		$sFilter = $this->getFilter();
		
		$this->setResultSet();
		if( mysql_num_rows( $this->rsArbeit )>0 || $sFilter!="" ) {
			$this->sTable .= $sFilter;
			if( mysql_num_rows( $this->rsArbeit )>0 ) {
				$bShowSum=false;
				while( $rowArbeit=mysql_fetch_array( $this->rsArbeit ) ) {
					$datum = new datum;
					$datum->setDate( $rowArbeit["datum"] );
					$nArbeitId = $rowArbeit["arbeit_id"]; 
					$sName = $rowArbeit["name"];
					$nDauer = $rowArbeit["dauer"];
					$sProjekt = $rowArbeit["projekt"];
					$sSchritt = $rowArbeit["schritt"];
					$sBeschreibung = $rowArbeit["beschreibung"];
					
					$nDauerH = floor( $nDauer/3600 );
					$nDauerM = floor( ($nDauer-$nDauerH*3600)/60 );
					if( $nDauerM=="0" )
						$nDauerM="00"; 
					
					if( $sBeschreibung=="" )
						$sBeschreibung="&nbsp;";
					if( $sOldProjekt!=$sProjekt) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSumPrint( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						if(  $sOldProjekt!="" )
							$this->sTable .= '<tr><td class="print" colspan="4"><hr noshade></td></tr></table><br>
											 ';
						$this->sTable .= '<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff" width="90%">
											<tr>
												<th class="print" colspan="4" align="left">' . $sProjekt . '</th>
								  			</tr>
											<tr>
												<td class="klein">Datum</td>
												<td class="klein">&nbsp;&nbsp;h:m</td>
												<td class="klein">&nbsp;&nbsp;Beschreibung</td>
												<td class="klein">Name</td>
								  			</tr>
								  		';
					}
					if( $sOldMonth!=$datum->sMonat || $sOldProjekt!=$sProjekt ) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSumPrint( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						$this->sTable .= '<tr>
					  						<td colspan="4"><hr noshade>' . $datum->sMonat . ' ' . $datum->nJahr . '</td>
								  		</tr>
								  		';
					}
					if( $sSchritt!=$sOldSchritt || $sOldProjekt!=$sProjekt || $sOldMonth!=$datum->sMonat ) {
						if( $bShowSum ) {
							$this->sTable .= $this->getRowSumPrint( $nSummeH,$nSummeM );
							$bShowSum=false;
							$nSumme=0;
						}
						$this->sTable .= '<tr>
					  						<td colspan="4">' . $sSchritt . '</td>
								  		</tr>
								  		';	
					}
					if( $sOldName!=$sName || $sSchritt!=$sOldSchritt || $sOldProjekt!=$sProjekt || $sOldMonth!=$datum->sMonat )		
						$sTdName = $sName;
					else
						$sTdName = "s.o.";
					$this->sTable .= '<tr>
					  					<td align="right" width="10%">&nbsp;<a href="' . $PHP_SELF .'?urlArbeitId=' . $nArbeitId . '">' . $datum->nTag . '.' . $datum->nMonat . '.' . $datum->nJahr . '</a></td>	
										<td width="7%" align="right">&nbsp;' . $nDauerH . ':' . $nDauerM . '</td>
										<td width="51%">&nbsp;&nbsp;' . $sBeschreibung . '</td>
										<td width="25%">' . $sTdName . '</td>
					 				</tr>
					 				';
					
					$nSumme = $nSumme+$nDauer;
					$nSummeH = floor( $nSumme/3600 );
					$nSummeM = floor( ($nSumme-$nSummeH*3600)/60 );
					if( $nSummeM=="0" )
						$nSummeM="00";
					
					$bShowSum=true;	
					$sOldMonth=$datum->sMonat;
					$sOldProjekt=$sProjekt;	
					$sOldName=$sName;	
					$sOldSchritt=$sSchritt;	
			
				} //end while
				$this->sTable .= $this->getRowSumPrint( $nSummeH,$nSummeM );
				$this->sTable .= '</table>';
			} //if( mysql_num_rows( $rsArbeit )>0 )
		} //end if( mysql_num_rows( $this->rsArbeit )>0 || $sFilter!="" )
	}
	
	/**
	* gibt eime tabellenzeile mit der summe aus
	*/
	function getRowSum( $nSummeH,$nSummeM ) {
		return '<tr>
					<td bgcolor="#444466" colspan="2">Summe:</td>
					<td bgcolor="#444466" align="right">' . $nSummeH . ':' . $nSummeM . '</td>
					<td bgcolor="#444466" colspan="2">&nbsp;</td>
				</tr>
				';
	}
	
	/**
	* gibt eime tabellenzeile mit der summe aus
	*/
	function getRowSumPrint( $nSummeH,$nSummeM ) {
		return '<tr>
					<td class="print" align="right">Summe:</td>
					<td class="print" align="right">' . $nSummeH . ':' . $nSummeM . '</td>
					<td class="print" colspan="2">&nbsp;</td>
				</tr>
				';
	}
	
	/*
	* updateted einen eintrag
	*/
	function update() {
		global $txtIsSubmit;
		if( $txtIsSubmit!="true" )
			return;
		$this->setValues();
		if( !$this->checkValues() || $this->nArbeitId=="" ) {
			return false;
		}
		$sqlUpdate = "update arbeit set ma_id=$this->nMaId,schritt_id=$this->nSchrittId,datum='$this->sDatum',dauer=$this->nDauer";
		if( $this->sBeginn!="" && $this->sEnde!="" )
			$sqlUpdate .= ",beginn='$this->sBeginn',ende='$this->sEnde'";
		if( $this->sBeschreibung!="" )
			$sqlUpdate .= ",beschreibung='$this->sBeschreibung'";
		$sqlUpdate .= " where arbeit_id=$this->nArbeitId";
		mysql_query( $sqlUpdate )
			or die( dbError( $sqlUpdate ) );			 	
	}	
	
	/*
	* fuegt einen neuen eintrag zur Tabelle hinzu
	*/
	function insert() {
		global $txtIsSubmit;
		if( $txtIsSubmit!="true" )
			return;
		for( $i=0; $i<5; $i++ ) {
			$this->setValues( $i );
			if( $this->checkValues() ) {
				if( $this->sBeschreibung=="" )
					$sqlInsert="insert into arbeit (ma_id,schritt_id,dauer,datum) values ($this->nMaId,$this->nSchrittId,$this->nDauer,'$this->sDatum')";
				else
					$sqlInsert="insert into arbeit (ma_id,schritt_id,beschreibung,dauer,datum) values ($this->nMaId,$this->nSchrittId,'$this->sBeschreibung',$this->nDauer,'$this->sDatum')";
				mysql_query( $sqlInsert )
					or die( dbError( $sqlInsert ) );	
				//echo "$sqlInsert";
			}
		}	
	}
	
	/**
	* Waehlt Eintraege aus der Tabelle mit dem where-statement $sWhere aus
	* gibt ein result set zurueck
	*/
	function selectWhere( $sWhere ) {
		$sqlSelect="select arbeit_id,ma_id,arbeit.schritt_id,beginn,ende,dauer,datum,DAYOFMONTH(datum) as tag,MONTH(datum) as monat,YEAR(datum) as jahr,beschreibung,schritt.projekt_id from arbeit,schritt where $sWhere and arbeit.schritt_id=schritt.schritt_id";
		$rsSelect=mysql_query( $sqlSelect )
			or die( dbError( $sqlSelect ) );
		return $rsSelect;
	}
	
	/**
	* Waehlt den eintrag mit der id $nArbeitId uns belegt die entsprechenden Membervariablen
	*/
	function selectById( $p_nArbeitId ) {
		$rsSelect=$this->selectWhere( "arbeit_id=$p_nArbeitId" );
		if( $rowSelect=mysql_fetch_array( $rsSelect ) ) {
			$this->nArbeitId=$rowSelect["arbeit_id"];
			$this->nMaId=$rowSelect["ma_id"];
			$this->nSchrittId=$rowSelect["schritt_id"];
			$this->nProjektId=$rowSelect["projekt_id"];
			$this->sBeginn=$rowSelect["beginn"];
			$this->sEnde=$rowSelect["ende"];
			$this->nDauer=$rowSelect["dauer"];
			$this->sDatum=$rowSelect["datum"];
			$this->nTag=$rowSelect["tag"];
			$this->nMonat=$rowSelect["monat"];
			$this->nJahr=substr( $rowSelect["jahr"], 2 );
			$this->sBeschreibung=$rowSelect["beschreibung"];
			
			if( $this->nDauer!="" ) {
				$this->nStunden=floor($this->nDauer/3600);
				$nRest=$this->nDauer-$this->nStunden*3600;
				$this->nMinuten=floor($nRest/60);
			}
		}
		else
			return false;	
	}
	
	/**
	* Waehlt die Spalten $sColumns der Eintraege aus der Tabelle 
	* mit dem where-statement $sWhere aus gibt ein result set zurueck
	*/
	function select( $sColumns, $sWhere ) {
		$sqlSelect="select $sColumns from arbeit where $sWhere";
		$rsSelect=mysql_query( $sqlSelect )
			or die( dbError( $sqlSelect ) );
		return $rsSelect;
	}
	
	/**
	* Waehlt die Spalten $sColumns der Eintraege aus der Tabelle 
	* mit dem where-statement $sWhere aus gibt ein result set zurueck
	*/
	function selectTables( $sColumns, $sTables, $sWhere ) {
		global $bIsDebug; 
		$sqlSelect="select $sColumns from $sTables where $sWhere";
		$rsSelect=mysql_query( $sqlSelect )
			or die( dbError( $sqlSelect ) );
		if( $this->bIsDebug )
			echo "$sqlSelect<br>";
		return $rsSelect;
	}
}
?>