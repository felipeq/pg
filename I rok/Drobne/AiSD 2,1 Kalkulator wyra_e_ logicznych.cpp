/*Dane s¹ wartoœci logiczne: T (true), F (false) i U (unknown) oraz nastêpuj¹ce operatory: AND, OR, NOT (zob. ich tabele prawdy w logice Kleene'a), ARG1 i ARG2 (dwa ostanie operatory s¹ jednoargumentowe i jako wartoœæ daj¹ wyra¿enie bêd¹ce odpowiednio pierwszym i drugim argumentem g³ównego operatora argumentu).

Operatorów ARG1 i ARG2 nie mo¿na zastosowaæ dla wyra¿enia nie zawieraj¹cego ¿adnego operatora, a ARG2 dodatkowo nie mo¿na stosowaæ dla wyra¿eñ, których g³ównym operatorem jest operator jednoargumentowy - patrz przyk³ady poni¿ej.

Zadanie polega na implementacji kalkulatora wyra¿eñ logicznych z pamiêci¹, który operuje w powy¿szej logice 3-wartoœciowej.

Mo¿liwoœci kalkulatora

Kalkulator potrafi zapamiêtywaæ i obliczaæ wartoœci wyra¿eñ logicznych. Pamiêæ kalkulatora sk³ada siê z n zmiennych przechowuj¹cych zdania: S0, S1, ... ,Sn-1 (inicjalnie ka¿da zmienna ma wartoœæ T - zdanie zawsze prawdziwe) oraz z k zmiennych przechowuj¹cych wartoœci logiczne: x0, x1, ... ,xk-1 (inicjalnie równie¿ maj¹ wartoœæ T).

Dostêpne komendy to:

= - pod wybran¹ zmienn¹ podstawiamy nowe wyra¿enie lub wartoœæ.
eval - oblicza wartoœæ wyra¿enia przy ustalonej wartoœci zmiennych logicznych.
count - dla danego zdania, count analizuje wszystkie mo¿liwe sposoby nadania zmiennym wartoœci (wszystkim zmiennym - tym, które wystêpuj¹ w zdaniu i tym, które nie wystêpuj¹) i zlicza te sposoby, dla których zdanie jest prawdziwe (eval dla zdania daje T).
print - wypisuje wartoœæ na wyjœcie.
 

Wyra¿enie logiczne sk³ada siê ze zmiennych i operatorów w Notacji Polskiej (prefiksowej lub przedrostkowej), czyli najpierw operator a nastêpnie operandy. Bardziej formalnie, ka¿de z wyra¿eñ bêdzie zbudowane wed³ug regu³ gramatyki podanej poni¿ej:

< wyra¿enie >::= < op2 > < wyra¿enie > < wyra¿enie >  
< wyra¿enie >::= < op1 > < wyra¿enie > 
< wyra¿enie >::= < var1 >
< wyra¿enie >::= < var2 >
< wyra¿enie >::= F|T|U
< var1 >::= x0|x1| ... |xk-1
< var2 >::= S0|S1| ... |Sn-1
< op1 >::= NOT|ARG1|ARG2
< op2 >::= OR|AND
Z kolei instrukcje dla kalkulatora mo¿emy tworzyæ w nastêpuj¹cy sposób:

< instrukcja >::= < podstawienie > | < print >  
< podstawienie >::= < var1 > = eval < wyra¿enie >
< podstawienie >::= < var2 > = < wyra¿enie >
< print >::= print < var2 > 
< print >::= print eval < wyra¿enie > 
< print >::= print count < wyra¿enie >
Opis danych wejœciowych

W pierwszej linii na wejœciu zostan¹ podane trzy liczby n (n < 1000), k (k < 10) i w (w < 10000). Nastêpnie, w kolejnych w wierszach w instrukcji. Dane s¹ poprawne, a instrukcje dla kalkulatora zawsze wykonalne.

Opis danych wyjœciowych

Na wyjœciu powinien pojawiæ siê efekt dzia³ania instrukcji print. Po jednej w ka¿dym wierszu.

Przyk³ad 1

Wejœcie:
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
 
wyjœcie:
AND T OR T x1
9
0
OR T x1
AND F x0
T
U
Przyk³ad 2

Wejœcie:
5 2 2
S1 = ARG1 S2 // to podstawienie jest nieprawid³owe,
             // gdy¿ S2 jest równe T - 
             // nie ma ¿adnego operatora
S1 = ARG2 NOT OR x2 x3  // to te¿ b³êdne
                        // bo NOT ma tylko jeden argument
Opis zestawów danych testowych

testy 0, 1, 2 - wystêpuj¹ tylko instrukcje print < var2 >  oraz < var2 > = < wyra¿enie >, operatory ARG1 i ARG2 nie wystêpuj¹.

testy 3, 4 - dodatkowo wystêpuje instrukcja eval

testy 5, 6 - dodatkowo wystêpuje instrukcja count

testy 7, 8, 9 - brak dodatkowych ograniczeñ na wystêpowanie instrukcji i operatorów.

Punktacja

Za napisany program student otrzymuje punkty wynikaj¹ce z komunikatu w systemie SPOX (max. 24). Ka¿dy z pierwszych 6 testów jest warty 2 pkt, a ka¿dy z pozosta³ych 3 punkty.  

 

Dodatkowe punkty mo¿na uzyskaæ za styl i zarz¹dzanie pamiêci¹. Wynik programu napisanego w dobrym stylu i poprawnie obs³uguj¹cego pamiêæ zostanie przemno¿ony przez 1.25. Wynik programu napisanego niezgodnie z regu³ami dobrego stylu programowania (powtarzanie kodu, przypadkowe nazwy, brak lub niejasne komentarze, nielogiczna struktura, niestaranne formatowanie itp.) zostanie przemno¿ony przez mniejszy wspó³czynnik (ale nie mniejszy ni¿ 1).

Wskazówki implementacyjne

Nie nale¿y nic zak³adaæ o d³ugoœci wyra¿enia.

Jeœli po prawej stronie wyra¿enia wystêpuje zmienna zawieraj¹ca inne wyra¿enie, to nale¿y je skopiowaæ. Na przyk³ad: S0 = S1 tworzy kopiê S1 tak, ¿e po tym podstawieniu modyfikacje S1 nie wp³ywaj¹ na S0.

Zaleca siê przechowywaæ wyra¿enia jako drzewa, w których wêz³ami s¹ operatory logiczne, a liœæmi zmienne (operatory ARG mog¹ wystêpowaæ bardzo czêsto).*/

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
int n,k,w; // k - zmienne x0, x1, ... , xk/////// n - zdania S0,S1, ... ,Sn//// w - linie wejœcia
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
/*BLAD*/			if (s[ii]=='S' && ii>0) ///////////////////////W WYRA¯ENIU Sx MAMY INNE WYRA¯ENIE Sy///////// TUTAJ BLAD
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