function lad_glob

global g t ml k ko Fmax

g=9.8135; % [m/s2]
t=1; % krok calkowania [s]
ml=600; % masa ladownika [kg]

tmax=200; % czas pracy silnika z pelna moca [s]
mp0=1000; % poczatkowa masa paliwa [kg]
Fmax=22000; % sila maksymalna [N]
k=mp0/(Fmax*tmax);
ko=1/k; %odwrotnosc k




