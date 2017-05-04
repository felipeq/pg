% funkcja obliczajaca reakcje ladownika na pobudzenie
% Pobudzenie: sila F, ilosc paliwa mp, odleglosc x, predkosc v.
% Odpowiedz: odleglosc x, predkosc v, ilosc paliwa mp.

function stann=ladownik(stan,F)

global g t ml k ko Fmax

mp=stan(1);
x=stan(2);
v=stan(3);

mc=ml+mp; % masa laczna

if F<0
   F=0;
end
if F>Fmax
   F=Fmax;
end

mp1=mp-k*F*t;
if mp1<0
    F=mp/(k*t);
    mp1=0;
end
%if mp == 0  % bez tego jest blad
%   F = 0
%end   




if F>0.1
    v1=ko*log(mc/(mc-k*F*t))+v-g*t;
    x1=-(ko*ko/F)*log(mc/(mc-k*F*t))*(mc-k*F*t)+t/k+v*t-(g*t*t)/2+x;
else
    v1=v-g*t;
    x1=v*t-(g*t*t)/2+x;
end

% wyznaczenie dokladnej chwili zderzenia i predkosci w tej chwili.

if x1<0
    x1=0;
    tpom=0:0.01:t;
    i=1;
    if F>0.1    
        while -(ko*ko/F)*log(mc/(mc-k*F*tpom(i)))*(mc-k*F*tpom(i))+tpom(i)/k+v*tpom(i)-(g*tpom(i)*tpom(i))/2+x>0,
            i=i+1;
        end
        v1=ko*log(mc/(mc-k*F*tpom(i)))+v-g*tpom(i);
    else
        while v*tpom(i)-(g*tpom(i)*tpom(i))/2+x>0,
            i=i+1;
        end
        v1=v-g*tpom(i);        
    end
end

stann=[mp1,x1,v1];