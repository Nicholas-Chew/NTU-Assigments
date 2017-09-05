t = -5:0.01:5;
a = ramp_fn(t-1);
b = ramp_fn(t+1);
c = ramp_fn(t+1)-ramp_fn(t-1);
plot(t,a,t,b,t,c)
set(gca,'xtick',-5:0.5:5)
grid()
axis([-5 5 -5 5])
legend('rampFn(t-1)','rampFn(t+1)','rampFn(t+1)-rampFn(t-1)')