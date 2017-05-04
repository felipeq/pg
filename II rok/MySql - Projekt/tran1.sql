SET IMPLICIT_TRANSACTIONS OFF;
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
BEGIN TRANSACTION

SELECT TOP 3 * FROM Rachunki
ORDER BY Rachunki.id DESC
/* Umieszczamy w bazie nowy rachunek */ 
INSERT INTO Rachunki VALUES (7, 'Aviva',	0,	345,	0,		30,		100);

SELECT TOP 3 * FROM Rachunki
ORDER BY Rachunki.id DESC

-- DRUGA TRANSAKCJA

ROLLBACK TRANSACTION

/*	Zlecamy otworzenie nowego rachunku domowi maklerskiemu Aviva. Aviva rozpoczyna procedurê otwierania rachunku, niestety transakcja jest wykonywana
	na poziomie READ UNCOMMITED, przez co rachunek mo¿e przedwczeœnie trafiæ do naszej bazy. W miêdzyczasie my czekamy na ten rachunek, ¿eby wp³aciæ na 
	jego konto œrodki finansowe. Aviva otwiera rachunek, który nie jest jeszcze ostatecznie zatwierdzony i gotowy do u¿ytku. Jednak, przez niedostateczny
	poziom izolacji, udaje siê nam odczytaæ dane otwieranego rachunku z bazy. Myœl¹c, ¿e jest to gotowy, dzia³aj¹cy rachunek, decydujemy siê na przelanie
	pieniêdzy na najnowszy rachunek. Niestety tu¿ przed rozpoczêciem przelewu Aviva wycofa³a decyzjê o otwarciu naszego rachunku z powodu b³êdu w 
	dokumentach, tym samym usuwaj¹c z bazy rachunek. My jednak o tym nie wiemy, bo sprawdziliœmy wartoœæ bazy wczeœniej, kiedy ten rachunek jeszcze istnia³.
	Dochodzi do b³êdu DIRTY READ - odczytaliœmy niepotwierdzone dane, które chwilê potem zosta³y wycofane, jednak nie jesteœmy tego œwiadomi i chcemy dokonaæ
	jakiejœ akcji na danych, które nie istniej¹. 
	Aby unikn¹æ DIRTY READ zmieniamy poziom izolacji na READ COMMITED - od teraz nie bêdziemy mogli odczytywaæ niezatwierdzonych danych, czyli w tym przypadku
	nie bêdziemy mieli dostêpu do rachunków, jeœli s¹ one modyfikowane przez dom maklerski.

*/
	