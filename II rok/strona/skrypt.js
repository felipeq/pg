var slide_step=1; 	// o ile pixeli przesuwamy bannery co delay
var delay=13;		// co jaki czas przesuwamy bannery [ w ms ]
var x=0;			// wartoœæ przesuniêcia bannera od prawej krawêdzi #MASK do lewej
var a=3;			// aktualnie wyœwietlany banner

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
		temp=gora; // zamieniamy pozycjê gora z pozycj¹ dó³ i na odwrót z pomoc¹ zmiennej pomocniczej temp
		var temp2=gora.lastChild.src="banner/"+a+".jpg";
		gora.lastChild.src=dol.lastChild.src;
		dol.lastChild.src=temp2; // to samo robimy z adresami bannerów, które aktualnie musz¹ wyœwietlaæ
		x=0;
		if (a>=6)	a=0;
		a++;
	}
*/	