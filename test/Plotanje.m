function [] = Plotanje()
  cd ..;
  cd build/bin;
  graphics_toolkit('gnuplot');
  A = load("DobiveneVrijednosti.txt");
  B = load("OcekivaneVrijednosti.txt");
  C = load("RecentError.txt");
  x=1:rows(A);
  x=x';
  figure;
  scatter(x,A);
  xlabel ("Broj uzoraka");
  ylabel ("Dobivene i ocekivane vrijednosti");
  title ("Prikaz rezultata ucenja mreze");
  hold on;
  scatter(x,B);
  figure;
  plot(x,C);
  xlabel ("Broj uzoraka");
  ylabel ("Nedavna greska");
  title ("Prikaz greske tokom ucenja");
  pause;


  
endfunction