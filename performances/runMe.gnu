set title "Test"
set logscale x
set xlabel "nb octets"
set logscale y
set ylabel "vitesse en octets/s"
set style data linespoints
plot "ex3.dat" using 1:2 title "temps", \
     "ex3.dat" using 1:3 title "vitesse"
pause -1  "Hit return to continue"
