set title "Temps et vitesse d'execution"
set logscale x
set  xlabel "taille en ligne"
set logscale y
set ylabel "temps en s ou vitesse en octet/s"
set style data linespoints
plot "mcat-tm.dat" using 1:2 title "real time",\
     "mcat-tm.dat" using 1:3 title "user time",\
     "mcat-tm.dat" using 1:4 title "system time"
pause -1 "Hit return to continue"
