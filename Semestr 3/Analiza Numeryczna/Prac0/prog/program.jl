
using Plots
x = 1:10; y = rand(10);
pl = plot(x,y);
savefig(pl, "plot.png");
