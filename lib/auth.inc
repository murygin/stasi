<?php	
$bIsLocal=true;
if( !isset($PHP_AUTH_USER) || ($irl=="true" && !strcmp($txtOldUser,  $PHP_AUTH_USER) && !strcmp($txtOldPwd,  $PHP_AUTH_PW))) {
	Header("WWW-Authenticate: Basic realm=\"mfs\"");
    Header("HTTP/1.0 401 Unauthorized");
    echo "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">
			<HTML><HEAD>
				<TITLE>401 Authorization Required</TITLE>
			</HEAD><BODY>
				<H1>Authorization Required</H1>
				This server could not verify that you
				are authorized to access the document
				requested.  Either you supplied the wrong
				credentials (e.g., bad password), or your
				browser doesn't understand how to supply
				the credentials required.<P>
			</BODY></HTML>";
    exit;
} 
else {
	if( !$bIsDbConnected )
		include(  "stasi_db_settings.inc" );
	//$nSeconds=mktime( date( "H" ), date( "i" ), date(s)+5*60, date( "m" ), date( "d" ), date( "Y" ) );
	
	$aGruppe = Array();
	$sqlSelectGruppe="select ma.ma_id as ma_id,gruppe.gruppe_id as gruppe_id from gruppe,ma,ma_gruppe where gruppe.gruppe_id=ma_gruppe.gruppe_id and ma.ma_id=ma_gruppe.ma_id and ma.vorname='$PHP_AUTH_USER' and ma.kennwort=password('$PHP_AUTH_PW') and ma.status=0";
	$rsGruppe = mysql_query( $sqlSelectGruppe )
		or die( dbError( $sqlSelectGruppe ) );
    while( $rowGruppe=mysql_fetch_array( $rsGruppe ) ) {
		$nGruppeId=$rowGruppe["gruppe_id"];
		$aGruppe[]=$nGruppeId;
		$nMaId=$rowGruppe["ma_id"];	
	}
	if( $nGruppeId=="" ) {
		echo '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
			  <html>
			  <head>
				<title>Staatssicherheit</title>
				<script type="text/javascript" language="JavaScript">
					/**
					* oeffnet ein fenster mit der "login gescheitert" meldung
					*/
					function noLogin() {
						ewMa = window.open("/noLogin.phtml","ewMa","toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,width=213,height=100,resizable=no");
						ewMa.focus();
					}
					
					noLogin();
				</script>
			  </head>
			  <body>
				<form name="fmIrl" action="' . $PHP_SELF . '" method="post"><input name="irl" type="hidden" value="true"><input name="txtOldUser" type="hidden" value="' . $PHP_AUTH_USER . '"><input name="txtOldPwd" type="hidden" value="' . $PHP_AUTH_PW . '"></form>
			   </body>
			  </html>';
		exit;
	}
	$bIsAuth=false;
	for( $i=0; $i<count( $aGruppe ); $i++ )
		for( $k=0; $k<count( $aAccessId ); $k++ )
			if( $aGruppe[$i]==$aAccessId[$k] )
				$bIsAuth=true;
	
	if( !$bIsAuth ) {
		echo "kein Zugang zu dieser Seite!";
		exit;
	}
	
}
?>
