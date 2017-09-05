t = -5:0.01:5;
a = delta(t);
b = exp(t).*delta(t-1);
plot(t,a,t,b);
legend('delta(t)','exp(t).*delta(t-1)');