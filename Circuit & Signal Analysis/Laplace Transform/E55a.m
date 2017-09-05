N = 256;
dw = 2*pi/N;
w = 0:dw:50*2*(pi-dw);
s = 1i*w;
Ht = 50./(50-s);
plot(w, Ht)
set(gca,'xtick',pi:2*pi:50*2*pi)
set(gca,'xticklabel',1:1:50)