t = -5:0.01:10;
a = step(t-1);
b = 2*step(t+2);
c = step(t+1)-step(t-1);
axis([-5 10 -3 3])
plot(t,c)
plot(t,a,t,b,t,c)
set(gca,'xtick',-5:1:10)
grid()
axis([-5 10 -3 3])
legend('u(t-1)','2*u(t+2)','u(t+1)-u(t-1)')