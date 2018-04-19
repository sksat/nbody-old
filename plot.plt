if(exist("n")==0 || n<0) n=n0
frame = sprintf("out/output_%05d.prof", n)
plot frame
n = n + dn
if(n < n1) reread
undefine n
