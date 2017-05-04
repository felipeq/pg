/*
	1. Najbardziej zyskowne instrumenty w moim portfelu
*/
SELECT Portfel.Symbol_Ref, sum(Portfel.Wartosc_Sprzedanych-Portfel.Wartosc_Kupionych) AS 'Zysk'
FROM Portfel
GROUP BY Portfel.Symbol_Ref

/* 
	-- 1/2 ZŁĄCZENIE
	-- 1/2 FUNKCJE AGREGUJĄCE
	-- 1/2 GRUPOWANIE

	Złączenie Domów maklerskich z Rachunkami w nich otwartymi oraz podsumowanie Sald

*/
SELECT nazwa, sum(Rachunki.Saldo_Aktualne) AS 'Saldo'
FROM Domy_maklerskie INNER JOIN Rachunki
ON Domy_maklerskie.nazwa = Rachunki.nazwa_ref
GROUP BY Domy_maklerskie.nazwa

/*
	-- 2/2 ZŁĄCZENIE
	-- 2/2 FUNKCJE AGREGUJĄCE
	-- 2/2 GRUPOWANIE

	Ilość transakcji zawartych dla poszczególnego instrumentu

*/
SELECT Instrumenty.Symbol, count(Zlecenie.ID) AS 'Ilość transakcji'
FROM Instrumenty INNER JOIN Zlecenie
ON Instrumenty.Symbol = Zlecenie.symbol_ref
GROUP BY Instrumenty.Symbol

/*
	-- 1/2 PODZAPYTANIA

	Wszystkie zlecenia kupna posortowane wg daty otwarcia.

*/
SELECT *
FROM ( SELECT Czas_Zlozenia, Czas_Wykonania, BuySell FROM Zlecenie ) AS Dane
WHERE BuySell = 1
ORDER BY Czas_Zlozenia

/*
	-- 2/2 PODZAPYTANIA
	-- 1/1 PORZĄDKOWANIE

	Rachunki, na których otwarto zlecenia na walutach
*/

SELECT DISTINCT "ID Rachunku"
FROM ( SELECT Zlecenie_na_walutach.ID AS "ID Zlecenia Walut", Zlecenie.ID AS "ID Zlecenia", Zlecenie.id_ref AS "RACH id", Rachunki.id AS "ID Rachunku" FROM Zlecenie_na_walutach,Zlecenie, Rachunki ) AS Dane
WHERE "ID Zlecenia Walut"="ID Zlecenia" AND "RACH id"="ID Rachunku"
ORDER BY "ID Rachunku" DESC

/*
	2. Średni czas oczekiwania na wykonanie się zlecenia na akcjach 
*/

SELECT Zlecenie.symbol_ref AS 'Symbol' , AVG(DATEDIFF(hh, Zlecenie.Czas_Zlozenia, Zlecenie.Czas_Wykonania)) AS 'Średni czas do wykonania w godzinach'
FROM Zlecenie, Zlecenie_na_akcjach
WHERE Zlecenie_na_akcjach.ID = Zlecenie.ID
GROUP BY Zlecenie.symbol_ref

/*
	3. Podsumowanie zysków z wszystkich rachunków dla róznych domów maklerskich
*/

SELECT Rachunki.nazwa_ref AS 'Dom maklerski', sum(Rachunki.Saldo_Aktualne-Rachunki.Saldo_Wplat) AS 'Profit'
FROM Rachunki
GROUP BY Rachunki.nazwa_ref
ORDER BY 'Profit' DESC

/* 
	4. Najbardziej zyskowne transakcje na akcjach
*/

SELECT Zlecenie.symbol_ref, Zlecenie_na_akcjach.Ilosc*(Zlecenie.Cena_Wykonania-Zlecenie.Cena_Zlozenia) AS 'Profit'
FROM Zlecenie_na_akcjach, Zlecenie
WHERE Zlecenie_na_akcjach.ID = Zlecenie.ID
ORDER BY 'Profit' DESC

/*
	5. Iloma akcjami Apple łącznie obróciłem?
*/
SELECT Portfel.Symbol_Ref, sum(Portfel.Ilosc_Kupiona) AS 'Ilość akcji'
FROM Portfel
WHERE Portfel.Symbol_Ref = 'APPL'
GROUP BY Portfel.Symbol_Ref

/*
	6. Na jakim rachunku otworzyłem najwięcej transakcji?
*/
SELECT Zlecenie.id_ref AS 'ID Rachunku', count(Zlecenie.ID) AS 'Ilość Zleceń'
FROM Zlecenie
GROUP BY Zlecenie.id_ref
ORDER BY Zlecenie.id_ref ASC