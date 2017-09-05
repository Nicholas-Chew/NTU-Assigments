function y = square(t)
%SQUARE Summary of this function goes here
%   Detailed explanation goes here
y = step(t+0.5)- step(t-0.5);

end

