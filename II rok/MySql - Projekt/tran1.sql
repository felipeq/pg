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

/*	Zlecamy otworzenie nowego rachunku domowi maklerskiemu Aviva. Aviva rozpoczyna procedur� otwierania rachunku, niestety transakcja jest wykonywana
	na poziomie READ UNCOMMITED, przez co rachunek mo�e przedwcze�nie trafi� do naszej bazy. W mi�dzyczasie my czekamy na ten rachunek, �eby wp�aci� na 
	jego konto �rodki finansowe. Aviva otwiera rachunek, kt�ry nie jest jeszcze ostatecznie zatwierdzony i gotowy do u�ytku. Jednak, przez niedostateczny
	poziom izolacji, udaje si� nam odczyta� dane otwieranego rachunku z bazy. My�l�c, �e jest to gotowy, dzia�aj�cy rachunek, decydujemy si� na przelanie
	pieni�dzy na najnowszy rachunek. Niestety tu� przed rozpocz�ciem przelewu Aviva wycofa�a decyzj� o otwarciu naszego rachunku z powodu b��du w 
	dokumentach, tym samym usuwaj�c z bazy rachunek. My jednak o tym nie wiemy, bo sprawdzili�my warto�� bazy wcze�niej, kiedy ten rachunek jeszcze istnia�.
	Dochodzi do b��du DIRTY READ - odczytali�my niepotwierdzone dane, kt�re chwil� potem zosta�y wycofane, jednak nie jeste�my tego �wiadomi i chcemy dokona�
	jakiej� akcji na danych, kt�re nie istniej�. 
	Aby unikn�� DIRTY READ zmieniamy poziom izolacji na READ COMMITED - od teraz nie b�dziemy mogli odczytywa� niezatwierdzonych danych, czyli w tym przypadku
	nie b�dziemy mieli dost�pu do rachunk�w, je�li s� one modyfikowane przez dom maklerski.

*/
	