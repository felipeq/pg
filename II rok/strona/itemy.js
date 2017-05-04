function item(tlo, nazwa, cena, kat, id) // 'klasa' zawierające informacje o przedmiocie
{	
	this.tlo=tlo;
	this.nazwa=nazwa;
	this.cena=cena;
	this.kat=kat;
	this.id=id;
	this.wykrzycz=function() 
	{
		alert("Tło: "+tlo+"\nNazwa: "+nazwa+"\nCena: "+cena+"\nKategoria: "+kat+"\nID: "+id);
	};
	
};
var tab=[11];
tab[0]=new item('items_small/300_SpartanCleanShield_1SM.jpg',	'Tarcza, czysta',				'999 PLN', 	'300', 				'1');
tab[1]=	new item('items_small/bane1.jpg',						'Maska Bane\'a',				'259 PLN', 	'Mroczny Rycerz', 	'2');
tab[2]=	new item('items_small/Rorschach-Mask-3.jpg',			'Maska Rorschach\'a',			'99 PLN',	'Watchmen',			'3');
tab[3]=	new item('items_small/300-AstinosShield1.jpg',			'Tarcza, zniszczona',			'999 PLN',	'300',				'4');
tab[4]=	new item('items_small/avengers_shield1.jpg',			'Tarcza Kapitana Ameryki',		'699 PLN',	'Avengers',			'5');
tab[5]=	new item('items_small/avengers-BlackWidowSmokeBomb1.jpg','Bomby Dymne',					'39 PLN',	'Avengers',			'6');
tab[6]=	new item('items_small/batman1.jpg',						'Kombinezon Batmana',			'1999 PLN',	'Mroczny Rycerz',	'7');
tab[7]=	new item('items_small/Iron_Man1.jpg',					'Hełm Iron Mana MK I',			'199 PLN',	'Iron Man',			'8');
tab[8]=	new item('items_small/silkspectre_1.jpg',				'Strój Jedwabnej Zjawy',		'399 PLN',	'Watchmen',			'9');
tab[9]=	new item('items_small/spear1.jpg',						'Włócznia',						'99 PLN',	'Tomb Rider',		'10');
tab[10]=new item('items_small/sword1.jpg',						'Miecz',						'99 PLN',	'Tomb Rider',		'11');

function wstaw(it) // funkcja wstawiająca produkt o indeksie 'it' na stronę
{
	var element = document.createElement('div'); // tworzymy główny styl dla całego produktu
	var pole 	= document.createElement('div'); // tworzymy styl na nazwy i ceny
	element.id = 'jsit_'+it.id;
	element.setAttribute("onclick","linkto("+it.id+")");
	element.style.width = '180px';
	element.style.height= '180px';
	element.style.backgroundImage='url(\''+it.tlo+'\')';
	element.style.display='block';
	element.style.cssFloat ='left';
	element.style.margin="12px";
	element.style.clear	="none";	
	element.style.overflow='hidden';
	element.style.cursor="pointer";
	element.style.borderBottomRightRadius="5px";
	element.style.borderBottomLeftRadius ="5px";
	
	pole.id='jsitp_'+it.id;
	pole.style.position='relative';
	pole.style.top='130px';
	pole.style.backgroundColor="DodgerBlue";
	pole.style.height='50px';
	pole.style.paddingTop='5px';
	var body = document.getElementById('PRODUKTY'); 
	body.appendChild(element);	// dodajemy do #PRODUKTY 'element'
	
	body = document.getElementById('jsit_'+it.id); 
	body.appendChild(pole);		// dodajemy do dodanego przed chwilą 'element'-u pole na nazwę i cenę
	
	body = document.getElementById('jsitp_'+it.id);
	body.appendChild(document.createTextNode(it.nazwa));
	body.appendChild(document.createElement("br"));
	body.appendChild(document.createTextNode(it.cena)); // dodajemy nazwę i cenę do utworzonego pola na tekst
};


Node.prototype.kasuj = function() // funkcja usuwająca wszystkie przedmioty z ekranu
{
    if (this.childNodes.length) 
	{
        for (x=this.childNodes.length-1; x>=0; x--) 
		{
            this.removeChild(this.childNodes[x]);
        }
    }
}
function show(wybor) // funkcja pokazująca wybrane przedmioty w polu #PRODUKTY
{
	var ul = document.getElementById('PRODUKTY');
	ul.kasuj();
	
	for ( i=0;i<11;i++)
	{
		if (tab[i].kat==wybor || wybor=='all')
			wstaw(tab[i]);
	};
};
function linkto(idx)
{
window.location = "item"+idx+".htm";
}

show('all');