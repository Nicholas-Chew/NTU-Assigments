t = -5:0.01:5;
fn = @(t) exp(t).*delta(t-1);
integral(fn,-Inf,Inf)