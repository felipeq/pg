% SYMULACJA LADOWNIKA - 
lad_glob;  % zmienne globalne
liczba_krokow = 5000;
animacja = 1;
stany_pocz = [ 400 100 0;1000 8000 10; 400 3000 -60;800 6000 -100; 400 50 250];  % sym12 

                                     % kazdy stan opisany przez trojke [ilosc_paliwa, x, V]
liczba_stanow_pocz = length(stany_pocz(:,1))                         

fis = readfis('dane.fis');                            % odczyt systemu rozmytego z pliku
V_konc = [];
ilosc_konc = [];
krok_konc = [];
historia = [];
for i=1:liczba_stanow_pocz                      % po stanach poczatkowych
   stan = stany_pocz(i,:);
   x = stan(2);
   krok = 0;
   historia = [];   
   while (krok < liczba_krokow)&(x~=0)     % po krokach czasowych az do wyladowania   
      ilosc_paliwa = stan(1);
      x = stan(2);
      V = stan(3);
      
      F = evalfis([ilosc_paliwa x V],fis); % wyznaczenie sily ciagu
      
      %[krok stan F]                        % wyswietlenie 
      
      stan_n = Ladownik(stan,F);           % wyznaczenie nowego stanu po pewnym interwale czasowym
      stan = stan_n;
      krok = krok+1;
            
      historia(krok,:) = [stan F];         % zapis biezacego stanu + proponowanej sily ciagu (nie musi taka byc)
   end
   V_konc(i) = V;                          % zapis wartosci koncowych
   ilosc_konc(i) = ilosc_paliwa;
   krok_konc(i) = krok;
   
   historia(:,4) = historia(:,4)/100;      % przygotowanie wykresu
   plot(historia)
   legend('paliwo','x','V','F/100');
   title(strcat('ster. ladownikiem dla stanu pocz.: ',num2str(stany_pocz(i,:))));
   xlabel(strcat('predkosc ladowania V_k = ',num2str(V),' m/s'));
   pause
   close
   
   % Rysowanie animacji zachowania ladownika
   if animacja
      historia(:,4) = historia(:,4).*(historia(:,1)>0);  % sila rzeczywiscie uzyta
      max_x = max(historia(:,2));
      axis([-40  40  -max_x/8  max_x*1.1]);
      ylabel('wysokosc [m]');
      xkab = [-2 -1 -4 -3 3 4 1 2];
      ykab = [0 2 2 6 6 2 2 0]*max_x/100;
      xciag = [-2 -2 2 2];
      yciag = [-historia(1,4)*max_x/1000 0 0 -historia(1,4)*max_x/1000] + historia(1,2);
      y = ykab+historia(1,2);
      idkab = patch(xkab,y , 'b', 'erasemode','xor');     % rysowanie wypelnionego konturu kadluba
      idciag = patch(xciag,yciag, 'y','erasemode','xor');  % rysowanie plomienia ciagu
      patch([-40 -40 40 40],[-max_x/8 0 0 -max_x/8] , 'g', 'erasemode','xor');   % rys. powierzchni planety
      %idl=line(xs, ys, 'erasemode','xor')         % rys. linii
      for k=1:krok,
         y = ykab+historia(k,2);
         set(idkab,'xdata', xkab, 'ydata', y);
         yciag = [-historia(k,4)*max_x/1000 0 0 -historia(k,4)*max_x/1000] + historia(k,2);
         set(idciag,'xdata', xciag, 'ydata', yciag);
         %set(idl,'xdata', xs, 'ydata', ys);
         drawnow;
         pause(0.01)
      end
      %delete(idkab);
      close;
   end
   
end
% Wyswietlanie wynikow:
disp(sprintf(' <Nr stanu pocz.>:<predkosc ladowania>  <ilosc paliwa> <liczba krokow>'));
for i=1:liczba_stanow_pocz  
   disp(sprintf(' %d: %f     %f     %d',i,V_konc(i),ilosc_konc(i),krok_konc(i))); 
end

punktacja = 10000/sum(abs(V_konc.^4)) + sum(ilosc_paliwa)*(max(abs(V_konc))<5)