CREATE TABLE Domy_maklerskie 
(
	nazwa 		CHAR(255) PRIMARY KEY,
	adres 		CHAR(255),
	adres_www 	CHAR(255),
	kod 		SMALLINT
);

CREATE TABLE Rachunki 
(
	id 				INT PRIMARY KEY,
	nazwa_ref 		CHAR(255) NOT NULL REFERENCES Domy_maklerskie(nazwa),
	Saldo_Aktualne 	FLOAT,
	nr_rachunku 	INT,
	Saldo_Wplat 	FLOAT,
	Wymagany_Depozyt_Zabezpieczajacy 	FLOAT,
	Dzwignia 		INT
);

CREATE TABLE Instrumenty 
(
	Symbol 		VARCHAR(8) PRIMARY KEY,
	Prowizja 	FLOAT
);

CREATE TABLE Zlecenie 
(
	ID 			INT PRIMARY KEY,
	id_ref 		INT NOT NULL REFERENCES Rachunki(id),
	symbol_ref 	VARCHAR(8) NOT NULL REFERENCES Instrumenty(Symbol),
	Czas_Zlozenia	DATETIME,
	Czas_Wykonania 	DATETIME,
	Cena_Zlozenia 	MONEY,
	Cena_Wykonania 	MONEY,
	TP 		FLOAT,
	SL 		FLOAT,
	BuySell BIT
);

CREATE TABLE Zlecenie_na_akcjach
(
	id_akcje 	INT PRIMARY KEY,
	ID 			INT REFERENCES Zlecenie(ID),
	Ilosc 		INT,
	Kupujacy 	CHAR(255),
	Sprzedajacy CHAR(255),

);

CREATE TABLE Zlecenie_na_walutach
(
	id_waluty 	INT PRIMARY KEY,
	ID 			INT REFERENCES Zlecenie(ID),
	Loty 		FLOAT
);

CREATE TABLE Portfel 
(
	id_portfel 	INT PRIMARY KEY,
	Symbol_Ref 	VARCHAR (8) REFERENCES Instrumenty(Symbol),
	id_rach 	INT NOT NULL REFERENCES Rachunki(id),
	Ilosc_Kupiona		FLOAT,
	Wartosc_Kupionych	FLOAT,
	Ilosc_Sprzedanych	FLOAT,
	Wartosc_Sprzedanych	FLOAT
);

