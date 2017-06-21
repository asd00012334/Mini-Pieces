arrivals = [0];
current = 0.0;
deltaTime = 1.0;
lambda0 = 0.5;
n = 1e7;
for min = 1:n,
    step = -log(1-rand())*deltaTime/lambda0;
    arrivals(end+1) = step;
end

[num,t]=hist(arrivals,100);
plot(t,num/n);
