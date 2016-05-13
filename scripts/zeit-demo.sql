# MySQL dump 7.1
#
# Host: localhost    Database: zeit-demo
#--------------------------------------------------------
# Server version	3.22.32-log
USE zeit-demo;
#
# Table structure for table 'arbeit'
#
CREATE TABLE arbeit (
  arbeit_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  ma_id smallint(6) DEFAULT '0' NOT NULL,
  schritt_id smallint(6) DEFAULT '0' NOT NULL,
  beschreibung varchar(255),
  beginn time,
  ende time,
  dauer int(11),
  datum date DEFAULT '0000-00-00' NOT NULL,
  PRIMARY KEY (arbeit_id),
  KEY schritt_id (schritt_id),
  KEY ma_id (ma_id),
  KEY datum (datum)
);
#
# Table structure for table 'gruppe'
#
CREATE TABLE gruppe (
  gruppe_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  bezeichnung varchar(25) DEFAULT '' NOT NULL,
  PRIMARY KEY (gruppe_id)
);

#
# Dumping data for table 'gruppe'
#
INSERT INTO gruppe VALUES (1,'Produktion');
INSERT INTO gruppe VALUES (2,'Projektmanager');
INSERT INTO gruppe VALUES (3,'Verwaltung');

#
# Table structure for table 'ma'
#
CREATE TABLE ma (
  ma_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  standort_id smallint(6) DEFAULT '0' NOT NULL,
  kennwort varchar(50) DEFAULT '' NOT NULL,
  vorname varchar(25) DEFAULT '' NOT NULL,
  name varchar(25) DEFAULT '' NOT NULL,
  email varchar(100) DEFAULT '' NOT NULL,
  strasse varchar(40),
  plz smallint(6),
  ort varchar(25),
  tel bigint(11),
  tel_privat bigint(11),
  handy bigint(11),
  status smallint(6) DEFAULT '0' NOT NULL,
  PRIMARY KEY (ma_id),
  UNIQUE login (kennwort,vorname)
);

#
# Dumping data for table 'ma'
#
INSERT INTO ma VALUES(1,3,'21fa4e806a38979e','Admin','','admin@foo.org','',0,'',0,0,0,0);

#
# Table structure for table 'ma_gruppe'
#
CREATE TABLE ma_gruppe (
  ma_id smallint(6) DEFAULT '0' NOT NULL,
  gruppe_id smallint(6) DEFAULT '0' NOT NULL
);

#
# Dumping data for table 'ma_gruppe'
#
INSERT INTO ma_gruppe VALUES (1,3); 


#
# Table structure for table 'ma_projekt'
#
CREATE TABLE ma_projekt (
  ma_id smallint(6) DEFAULT '0' NOT NULL,
  projekt_id smallint(6) DEFAULT '0' NOT NULL
);
#
# Dumping data for table 'ma_projekt'
#
INSERT INTO ma_projekt VALUES (25,16);

#
# Table structure for table 'projekt'
#
CREATE TABLE projekt (
  projekt_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  standort_id smallint(6) DEFAULT '0' NOT NULL,
  pm_id smallint(6) DEFAULT '0' NOT NULL,
  projekt_nr varchar(20),
  bezeichnung varchar(25) DEFAULT '' NOT NULL,
  status smallint(6) DEFAULT '0' NOT NULL,
  PRIMARY KEY (projekt_id)
);


#
# Table structure for table 'schritt'
#
CREATE TABLE schritt (
  schritt_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  projekt_id smallint(6) DEFAULT '0' NOT NULL,
  bezeichnung varchar(25) DEFAULT '' NOT NULL,
  PRIMARY KEY (schritt_id),
  UNIQUE schritt (projekt_id,bezeichnung)
);


#
# Table structure for table 'standort'
#
CREATE TABLE standort (
  standort_id smallint(6) DEFAULT '0' NOT NULL auto_increment,
  bezeichnung varchar(10) DEFAULT '' NOT NULL,
  PRIMARY KEY (standort_id)
);
#
# Dumping data for table 'standort'
#
INSERT INTO standort VALUES (1,'Standort1');
INSERT INTO standort VALUES (2,'Standort2');
INSERT INTO standort VALUES (3,'Global');
