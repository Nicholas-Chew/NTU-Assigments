t = -5:0.01:5;
a = square(2*t-1);
b = 1.5*square(-6*t+5);
c = square(0.5*t-2)+ 2*square(0.5*t-1)+3*square(0.5*t)+ 2*square(0.5*t+1)+square(0.5*t+2);
axis([-5 5 0 3])
plot(t,a,t,b,t,c)
set(gca,'xtick',-5:0.25:5)
grid()
axis([-5 5 0 3])
legend('square(2*t-1)','1.5*square(-6*t+5)','square(0.5*t-2)+ 2*square(0.5*t-1)+3*square(0.5*t)+ 2*square(0.5*t+1)+square(0.5*t+2)')