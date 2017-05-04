/*Dane s� warto�ci logiczne: T (true), F (false) i U (unknown) oraz nast�puj�ce operatory: AND, OR, NOT (zob. ich tabele prawdy w logice Kleene'a), ARG1 i ARG2 (dwa ostanie operatory s� jednoargumentowe i jako warto�� daj� wyra�enie b�d�ce odpowiednio pierwszym i drugim argumentem g��wnego operatora argumentu).

Operator�w ARG1 i ARG2 nie mo�na zastosowa� dla wyra�enia nie zawieraj�cego �adnego operatora, a ARG2 dodatkowo nie mo�na stosowa� dla wyra�e�, kt�rych g��wnym operatorem jest operator jednoargumentowy - patrz przyk�ady poni�ej.

Zadanie polega na implementacji kalkulatora wyra�e� logicznych z pami�ci�, kt�ry operuje w powy�szej logice 3-warto�ciowej.

Mo�liwo�ci kalkulatora

Kalkulator potrafi zapami�tywa� i oblicza� warto�ci wyra�e� logicznych. Pami�� kalkulatora sk�ada si� z n zmiennych przechowuj�cych zdania: S0, S1, ... ,Sn-1 (inicjalnie ka�da zmienna ma warto�� T - zdanie zawsze prawdziwe) oraz z k zmiennych przechowuj�cych warto�ci logiczne: x0, x1, ... ,xk-1 (inicjalnie r�wnie� maj� warto�� T).

Dost�pne komendy to:

= - pod wybran� zmienn� podstawiamy nowe wyra�enie lub warto��.
eval - oblicza warto�� wyra�enia przy ustalonej warto�ci zmiennych logicznych.
count - dla danego zdania, count analizuje wszystkie mo�liwe sposoby nadania zmiennym warto�ci (wszystkim zmiennym - tym, kt�re wyst�puj� w zdaniu i tym, kt�re nie wyst�puj�) i zlicza te sposoby, dla kt�rych zdanie jest prawdziwe (eval dla zdania daje T).
print - wypisuje warto�� na wyj�cie.
 

Wyra�enie logiczne sk�ada si� ze zmiennych i operator�w w Notacji Polskiej (prefiksowej lub przedrostkowej), czyli najpierw operator a nast�pnie operandy. Bardziej formalnie, ka�de z wyra�e� b�dzie zbudowane wed�ug regu� gramatyki podanej poni�ej:

< wyra�enie >::= < op2 > < wyra�enie > < wyra�enie >  
< wyra�enie >::= < op1 > < wyra�enie > 
< wyra�enie >::= < var1 >
< wyra�enie >::= < var2 >
< wyra�enie >::= F|T|U
< var1 >::= x0|x1| ... |xk-1
< var2 >::= S0|S1| ... |Sn-1
< op1 >::= NOT|ARG1|ARG2
< op2 >::= OR|AND
Z kolei instrukcje dla kalkulatora mo�emy tworzy� w nast�puj�cy spos�b:

< instrukcja >::= < podstawienie > | < print >  
< podstawienie >::= < var1 > = eval < wyra�enie >
< podstawienie >::= < var2 > = < wyra�enie >
< print >::= print < var2 > 
< print >::= print eval < wyra�enie > 
< print >::= print count < wyra�enie >
Opis danych wej�ciowych

W pierwszej linii na wej�ciu zostan� podane trzy liczby n (n < 1000), k (k < 10) i w (w < 10000). Nast�pnie, w kolejnych w wierszach w instrukcji. Dane s� poprawne, a instrukcje dla kalkulatora zawsze wykonalne.

Opis danych wyj�ciowych

Na wyj�ciu powinien pojawi� si� efekt dzia�ania instrukcji print. Po jednej w ka�dym wierszu.

Przyk�ad 1

Wej�cie:
5 2 13
S1 = OR T x1
S0 = AND S2 S1
print S0
S1 = AND F x0  
S3 = ARG2 S0
S4 = OR S1 x0
print count S2
print count ARG1 S4    
print S3
print S1
print eval S4
x0 = eval U
print eval S4 
 
wyj�cie:
AND T OR T x1
9
0
OR T x1
AND F x0
T
U
Przyk�ad 2

Wej�cie:
5 2 2
S1 = ARG1 S2 // to podstawienie jest nieprawid�owe,
             // gdy� S2 jest r�wne T - 
             // nie ma �adnego operatora
S1 = ARG2 NOT OR x2 x3  // to te� b��dne
                        // bo NOT ma tylko jeden argument
Opis zestaw�w danych testowych

testy 0, 1, 2 - wyst�puj� tylko instrukcje print < var2 >  oraz < var2 > = < wyra�enie >, operatory ARG1 i ARG2 nie wyst�puj�.

testy 3, 4 - dodatkowo wyst�puje instrukcja eval

testy 5, 6 - dodatkowo wyst�puje instrukcja count

testy 7, 8, 9 - brak dodatkowych ogranicze� na wyst�powanie instrukcji i operator�w.

Punktacja

Za napisany program student otrzymuje punkty wynikaj�ce z komunikatu w systemie SPOX (max. 24). Ka�dy z pierwszych 6 test�w jest warty 2 pkt, a ka�dy z pozosta�ych 3 punkty.  

 

Dodatkowe punkty mo�na uzyska� za styl i zarz�dzanie pami�ci�. Wynik programu napisanego w dobrym stylu i poprawnie obs�uguj�cego pami�� zostanie przemno�ony przez 1.25. Wynik programu napisanego niezgodnie z regu�ami dobrego stylu programowania (powtarzanie kodu, przypadkowe nazwy, brak lub niejasne komentarze, nielogiczna struktura, niestaranne formatowanie itp.) zostanie przemno�ony przez mniejszy wsp�czynnik (ale nie mniejszy ni� 1).

Wskaz�wki implementacyjne

Nie nale�y nic zak�ada� o d�ugo�ci wyra�enia.

Je�li po prawej stronie wyra�enia wyst�puje zmienna zawieraj�ca inne wyra�enie, to nale�y je skopiowa�. Na przyk�ad: S0 = S1 tworzy kopi� S1 tak, �e po tym podstawieniu modyfikacje S1 nie wp�ywaj� na S0.

Zaleca si� przechowywa� wyra�enia jako drzewa, w kt�rych w�z�ami s� operatory logiczne, a li��mi zmienne (operatory ARG mog� wyst�powa� bardzo cz�sto).*/

/*
Gotowe:
    print eval Sx;
	print Sx;
	Sx = ;

*/
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
using namespace std;
int n,k,w; // k - zmienne x0, x1, ... , xk/////// n - zdania S0,S1, ... ,Sn//// w - linie wej�cia
enum operatory	{AND, OR, NOT, ARG1, ARG2, W };
enum wartosci	{T, F, U, O, X};
wartosci ValX[10000];

struct Wezel
{
  Wezel *top, *left, *right;

  wartosci war;
  operatory op;
  int index;
};
Wezel *wskS[10000];

bool CzyJestX(Wezel *N,bool IsFound)
{
	if (N->left!=NULL	&& IsFound==false)	return CzyJestX(N->left, IsFound);
	if (N->right!=NULL	&& IsFound==false)	return CzyJestX(N->right, IsFound);
	if (N->war!=X		&& IsFound==false)	return false;
	if (N->war==X)
	{
		IsFound=true;
		return true;
	}
}
string IntToStr(int x)
{
int i = x;
ostringstream ss;
ss << i;
string str = ss.str();
return str;
}
Wezel *Cloned(Wezel *N)
{

	Wezel *X;
	X=new Wezel;
	X->op=N->op;
	X->war=N->war;
	if (N->war==4)
	X->index=N->index;
	X->top=N->top;
	X->left=N->left;
	X->right=N->right;
	if (X->left!=NULL) Cloned(X->left);
	if (X->right!=NULL) Cloned(X->right);
	return X;
}
wartosci Evaluj(Wezel *N)
{
	if (N->op==W)	
	{
		if (N->war!=X)
			return N->war;
		else
			return ValX[N->index];
	}
	if (N->op==OR) 
	{
		if (Evaluj(N->left)==T || Evaluj(N->right)==T)	return T;
		if (Evaluj(N->left)==F && Evaluj(N->right)==F)	return F;
		if (Evaluj(N->left)==U || Evaluj(N->right)==U)	return U;
	}
	if (N->op==AND)
	{
		if (Evaluj(N->left)==T && Evaluj(N->right)==T)	return T;
		if (Evaluj(N->left)==F || Evaluj(N->right)==F)	return F;
		if (Evaluj(N->left)==U || Evaluj(N->right)==U)	return U;
	}
	if (N->op==NOT)
	{
		if (Evaluj(N->left)==T) return F;
		if (Evaluj(N->left)==F) return T;
		if (Evaluj(N->left)==U) return U;
	}
}
void Drukuj(Wezel *N)
{
	if (N->op!=W)
	{
		string temp;
		switch (N->op)
		{
			case 0: temp="AND"; break;
			case 1: temp="OR"; break;
			case 2: temp="NOT"; break;
		}
		cout << temp;
	}
	else
	{
		string temp;
		switch (N->war)
		{
			case 0: temp="T"; break;
			case 1: temp="F"; break;
			case 2: temp="U"; break;
			case 4:{ 
					temp="x"+IntToStr(N->index);

					}	break;

		}
		cout << temp;
		return;
	}
	if (N->left!=NULL)
    {cout << " "; Drukuj(N->left);}
	if (N->right!=NULL) 
    {cout << " "; Drukuj(N->right);}
}
int Count (Wezel *N)
{
	
	if (CzyJestX(N,false)==false && Evaluj(N)==T) return pow(3,(double)k);
	if (CzyJestX(N,false)==false && Evaluj(N)==F) return 0;
	if (CzyJestX(N,false)==true )
	{

	}

}
int StrToInt(string s, int x)
{
	int wynik=0;
	int LiczDl=0;
	for ( int i=x;i<s.length();i++)
	{
		if ((int)s[i]>=48 && (int)s[i]<=57)
			LiczDl++;
		else break;
	}
	for ( int i=0;i<LiczDl;i++)
	{	
		wynik+=((int)s[x+i]-48)*pow(10,((double)(LiczDl-i)));
	}
	return wynik/10;
}
string UsunPodciag(string del, string s)
{
	bool jest=false;
	for (int i=0;i<s.length();i++)
	{
		if (s[i]==del[0])
		{
			for ( int q=0;q<del.length();q++)
			{
				if (s[i+q]==del[q])
				jest=true;
				else
				{
					jest=false;
					break;
				}
			}
			if (jest==true) 
				{
					s.erase(i,del.length()-1);
					return s;
				}
		}
	}
	return s;
}
string DeleteArgs(string s)
{
	for ( int i=0;i<s.length();i++)
	{
		if (s[i]=='A' && s[i+1]=='R')
		{
			if (s[i+5]=='A' && s[i+6]=='R')
			{
				if (s[i+8]=='1')
				s=DeleteArgs(UsunPodciag(("ARG1"),s));
				if (s[i+8]=='2')
				s=DeleteArgs(UsunPodciag(("ARG2"),s));
			}
			if (s[i+5]!='A' && s[i+6]!='R')
			{
				return s;
			}
		}
	}
	return s;
}
int main()
{
	cin >> n>>k>>w;
	for ( int i=0;i<k;i++)
		ValX[i]=T;
	
	for (int i=0;i<n;i++)
	{
		Wezel *N;
		N=new Wezel;
		N->war=T;
		N->op=W;
		N->left=NULL;
		N->right=NULL;
		N->top=NULL;
		wskS[i]=N;
	}
	for ( int i=0;i<w+1;i++)
	{
		string s;
		getline(cin,s);
		bool isFirst=true;
		Wezel *father;
		int ii=0;
		s=DeleteArgs(s);
		while (ii<s.length())
		{
			if (s[0]=='p' && s[1]=='r') //////////////print///////////print//////////////print////////////////////print
			{
				Wezel *Np;
				if (s[6]=='c' && s[7]=='o') /////////////////print count/////////////print count/////////print count////
				{
					if (s[12]=='S')
					{
						Np=wskS[StrToInt(s,13)];
						cout << Count(Np);
						break;
					}
				}
				if (s[6]=='e' && s[7]=='v') ///////print eval//////////print eval//////print eval/////print eval///////
				{
						Np=wskS[StrToInt(s,12)];
					switch (Evaluj(Np))
					{
					case 0: cout << "T"; break;
					case 1: cout << "F"; break;
					case 2: cout << "U"; break;
					};
					break;
				} //////////////////////////// KONIEC eval///////////// KONIEC eval///////////////////////
				if (s[6]=='S')
				{
					Np=wskS[StrToInt(s,7)];
					Drukuj(Np);
					break;
				}
				if (s[6]=='x')
				{
					int temp=ValX[StrToInt(s,7)];
					switch (temp)
					{
					case 0: cout << "T"; break;
					case 1: cout << "F"; break;
					case 2: cout << "U"; break;
					}
					break;
				}
			}
				///////////////////KONIEC print////////////////////////KONIEC print///////////////////////////


			/////////////////PRZYPISANIE/////////////////PRZYPISANIE///////////////
			if (s[3]=='=' || s[4]=='=' || s[5]=='=' || s[6]=='=' || s[7]=='=' || s[8]=='=' || s[9]=='=' || s[10]=='=' || s[11]=='=' || s[12]=='=')
			{
				if (s[0]=='x')
				{
					if (s[ii]=='e' && s[ii+1]=='v')
					{
						if (s[ii+5]=='T' || s[ii+5]=='F' || s[ii+5]=='U')
						{
							if (s[ii+5]=='T')
								ValX[StrToInt(s,1)]=T;
							if (s[ii+5]=='F')
								ValX[StrToInt(s,1)]=F;
							if (s[ii+5]=='U')
								ValX[StrToInt(s,1)]=U;
						}
					}

				}
				if (s[0]=='S')
				{
					Wezel *N;
					N=new Wezel;
					N->left=N->right=N->top=NULL;

					bool IsFound=false;
					operatory tempO;
					wartosci tempW;
/*BLAD*/			if (s[ii]=='S' && ii>0) ///////////////////////W WYRA�ENIU Sx MAMY INNE WYRA�ENIE Sy///////// TUTAJ BLAD
					{
						IsFound=true;
						N=Cloned(wskS[StrToInt(s,ii+1)]);
						tempO=N->op;
						tempW=N->war;
					}
					if (s[ii]=='A' && s[ii+1]=='R' && s[ii+2]=='G' && s[ii+3]=='2')//////ARG 2///////// ARG 2////// ARG 2/////ARG 2///
					{
						if (s[ii+5]=='S')
						{
							IsFound=true;
							if (wskS[StrToInt(s,ii+6)]->right!=NULL)
								N=Cloned(wskS[StrToInt(s,ii+6)]->right);
							else
								N=wskS[StrToInt(s,ii+6)];
							tempO=N->op;
							tempW=N->war;
							ii+=5;
						}
					}
					if (s[ii]=='A' && s[ii+1]=='R' && s[ii+2]=='G' && s[ii+3]=='1')////////ARG 1////////ARG 1///////ARG 1//////////
					{
						if (s[ii+5]=='S')
						{
							IsFound=true;
							if (wskS[StrToInt(s,ii+6)]->left!=NULL)
							{
								N=Cloned(wskS[StrToInt(s,ii+6)]->left);
							}
							else
								N=wskS[StrToInt(s,ii+6)];
							tempO=N->op;
							tempW=N->war;
							ii+=5;
						}

					}


					if (s[ii]=='N' && s[ii+1]=='O' && s[ii+2]=='T' && IsFound==false)
					{
						IsFound=true;
						tempO=NOT;
						tempW=O;
						ii+=2;
					}
					if (s[ii]=='O' && s[ii+1]=='R' && IsFound==false)
					{
						IsFound=true;
						tempO=OR;
						tempW=O;
						ii+=1;
					}
					if (s[ii]=='A' && s[ii+1]=='N' && s[ii+2]=='D' && IsFound==false)
					{
						IsFound=true;
						tempO=AND;
						tempW=O;
						ii+=2;
					}
					if (IsFound==false)
					{
						switch (s[ii])
						{
							case 'T': {IsFound=true; tempO=W; tempW=T;} break;
							case 'F': {IsFound=true; tempO=W; tempW=F;} break;
							case 'U': {IsFound=true; tempO=W; tempW=U;} break;
							case 'x': {
										IsFound=true;
										tempO=W;
										tempW=X;
										N->index=StrToInt(s,ii+1);
									  } break;
						}

					}
					if (IsFound==true)
					{
				
						N->op=tempO;
						N->war=tempW;
						if (isFirst==true)
						{ 
							wskS[StrToInt(s,1)]=N; 
							isFirst=false; 
							
						}
						else
						{
							while (N->top==NULL)
							{
								if (father->left!=NULL && father->right!=NULL) {father=father->top; continue; }
								if ((father->left!=NULL && father->right==NULL) && father->op!=NOT) father->right=N;
								if (father->left==NULL) father->left=N;
						
								if (father->left==N || father->right==N ) N->top=father;	
							}
						}
						if (N->war==O)
						father=N;
					}
				}
			}
			ii++;
			
		}
	}


	return 0;
}