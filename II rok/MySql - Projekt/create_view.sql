/* 
	Widok zawieraj¹cy nr rachunku, saldo wp³at i aktualne saldo.
*/
CREATE VIEW nrs
AS SELECT Rachunki.id, Saldo_Aktualne, Saldo_Wplat, Portfel.Symbol_Ref, Portfel.Ilosc_Kupiona, Portfel.Wartosc_Kupionych
FROM Rachunki JOIN Portfel ON Portfel.id_rach=Rachunki.id

SELECT * FROM nrs

SELECT Rachunki.id, Saldo_Aktualne, Saldo_Wplat, Portfel.Symbol_Ref, Portfel.Ilosc_Kupiona, Portfel.Wartosc_Kupionych
FROM Rachunki JOIN Portfel ON Portfel.id_rach=Rachunki.id

SELECT Rachunki.id, Saldo_Aktualne, Saldo_Wplat, Portfel.Symbol_Ref, Portfel.Ilosc_Kupiona, Portfel.Wartosc_Kupionych
FROM Rachunki, Portfel
WHERE Portfel.id_rach=Rachunki.id