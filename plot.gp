set nokey
set term gif animate
set output "out.gif"
set xrange[-2000:2000]
set yrange[-2000:2000]
set zrange[-2000:2000]
n0 = 0
n1 = 5000
dn = 2
load "plot.plt"
