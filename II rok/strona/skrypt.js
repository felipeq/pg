var slide_step=1; 	// o ile pixeli przesuwamy bannery co delay
var delay=13;		// co jaki czas przesuwamy bannery [ w ms ]
var x=0;			// warto�� przesuni�cia bannera od prawej kraw�dzi #MASK do lewej
var a=3;			// aktualnie wy�wietlany banner

function change()
{
	var dol	=document.getElementById('BANNER');
	var gora=document.getElementById('BANNER2');
	
	dol.style.left=-x+"px";
	gora.style.left=1000-x+"px";
	
	x+=slide_step;
	if (x>=1000)	dol.style.left=2010-x+"px";
	if (x==2000)	
	{
				if (a>=6)	a=0;
		a++;
		gora.lastChild.src="banner/"+a+".jpg";
		x=0;
	}
	if (x==1000)	
	{
		if (a>=6)	a=0;
		a++;
		dol.lastChild.src="banner/"+a+".jpg";
	}
}

setInterval("change()",delay);
	
/*
	if (x==1000)
	{
		dol.style.left=1000+"px";
		var temp;
		temp=dol;
		dol=gora;
		gora=temp;
		temp=gora; // zamieniamy pozycj� gora z pozycj� d� i na odwr�t z pomoc� zmiennej pomocniczej temp
		var temp2=gora.lastChild.src="banner/"+a+".jpg";
		gora.lastChild.src=dol.lastChild.src;
		dol.lastChild.src=temp2; // to samo robimy z adresami banner�w, kt�re aktualnie musz� wy�wietla�
		x=0;
		if (a>=6)	a=0;
		a++;
	}
*/	