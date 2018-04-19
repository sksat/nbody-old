set nokey
set term gif animate
set output "out.gif"
set xrange[-3000:3000]
set yrange[-3000:3000]
set zrange[-3000:3000]
n0 = 0
n1 = 20
dn = 1
load "plot.plt"
