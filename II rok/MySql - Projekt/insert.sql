/*								Symbol		Prowizja	*/
INSERT INTO Instrumenty	VALUES( 'EUR/USD', 	2.0);
INSERT INTO Instrumenty VALUES( 'USD/PLN', 	15.0);
INSERT INTO Instrumenty VALUES( 'GOOG', 	100.0);
INSERT INTO Instrumenty VALUES(	'KGHM',		65.0);
INSERT INTO Instrumenty VALUES( 'APPL',		85.0);

/*									Nazwa			adres		adres www				kod*/
INSERT INTO Domy_maklerskie VALUES( 'Aviva', 	'Warszawa', 'www.aviva.pl', 			2);
INSERT INTO Domy_maklerskie VALUES( 'XTB', 		'Warszawa', 'www.xtb.pl', 				54);
INSERT INTO Domy_maklerskie VALUES( 'Noble', 	'Kraków', 	'www.noblesecurities.pl', 	42);

/*							id	nazwa_ref	S Akt	nr_rach	S Wpł	ZAB		L*/
INSERT INTO Rachunki VALUES (1, 'Aviva',	105,	50,		100,	30,		100);
INSERT INTO Rachunki VALUES (2, 'XTB', 		700,	600,	800,	300,	1); 
INSERT INTO Rachunki VALUES (3, 'XTB',		0,		1234,	1500,	30,		100);
INSERT INTO Rachunki VALUES (6, 'XTB',		900,	1235,	900,	30,		100);
INSERT INTO Rachunki VALUES (4, 'Noble',	6500,	5432,	500,	80,		50);
INSERT INTO Rachunki VALUES (5, 'Noble',	50000,	5433,	80000,	30,		1);


/*							ID	id_ref	s_ref	Czas Złożenia			Czas Wykonania			Cz		Cw		TP		SL		B/S*/
INSERT INTO Zlecenie VALUES (1, 1, 'EUR/USD',	'2012-12-12 12:12:12', 	'2012-12-13 12:13:13', 	2.5,	2.6,	3.7,	2.3,	1);
INSERT INTO Zlecenie VALUES (2, 1, 'USD/PLN',	'2012-12-14 6:12:12',	'2012-12-15 7:13:13', 	3.5,	2.5,	2.0,	4.5,	0);
INSERT INTO Zlecenie VALUES (3, 2, 'GOOG',		'2012-12-16 12:12:12', 	'2012-12-17 12:13:13', 	700,	701,	720,	680,	1);
INSERT INTO Zlecenie VALUES (4, 3, 'APPL',		'2012-12-17 12:12:12', 	'2012-12-17 18:13:13',	150,	200,	220,	145,	1);
INSERT INTO Zlecenie VALUES (5, 4, 'KGHM',		'2012-12-17 10:12:12', 	'2012-12-19 14:13:13',	45,		35,		55,		35,		1);
INSERT INTO Zlecenie VALUES (6, 5, 'APPL',		'2012-12-20 10:00:00', 	'2012-12-26 11:00:00',	200,	220,	220,	190,	1);
INSERT INTO Zlecenie VALUES (7, 5, 'APPL',		'2012-12-21 21:00:00',	'2012-12-22 4:00:00',	250,	300,	305,	200,	1);

/*					 id_portf	s_ref		id_rach	Ik	Wk		Is	Ws*/
INSERT INTO Portfel VALUES (1,	'EUR/USD',	1,		10,	25,		10,	26);
INSERT INTO Portfel VALUES (2,	'USD/PLN',	1,		15,	52.5,	15, 37.5);
INSERT INTO Portfel VALUES (3,	'GOOG',		2,		1,	700,	1,	701); 
INSERT INTO Portfel VALUES (4,  'APPL',		3,		2,	300,	2,	400);
INSERT INTO Portfel VALUES (5,	'KGHM',		4,		1,	45,		1,	35);
INSERT INTO Portfel VALUES (6,	'APPL',		5,		2,	450,	2,	520);

/*									id_waluty	ID		Loty	*/
INSERT INTO Zlecenie_na_walutach VALUES (45,	1,		10);
INSERT INTO Zlecenie_na_walutach VALUES (46,	2,		15);

/*										 id_akcje	ID	ilosc	Kup		Sprz*/
INSERT INTO Zlecenie_na_akcjach VALUES 	(88,		3,	1,		'',	'');
INSERT INTO Zlecenie_na_akcjach VALUES 	(89,		4,	2,		'',	'');
INSERT INTO Zlecenie_na_akcjach VALUES 	(90,		5,	1,		'',	'');
INSERT INTO Zlecenie_na_akcjach VALUES 	(91,		6,	1,		'',	'');
INSERT INTO Zlecenie_na_akcjach VALUES 	(92,		7,	1,		'',	'');

