set terminal latex
set output 'report-gnuplottex-fig1.tex'
set terminal epslatex color size 12cm, 12cm
  set xzeroaxis lt -1
  set yzeroaxis lt -1
  set xrange [0:18]
  set style line 1 lt 1 lw 4 lc rgb '#ee0000' pt -1
  set style line 2 lt 1 lw 4 lc rgb '#008800' pt -1
  set grid xtics lc rgb '#555555' lw 1 lt 0
  set grid ytics lc rgb '#555555' lw 1 lt 0
  set key bottom right
  plot 'residual_4.log' using 1:2 with lines ls 1 ti '$eigen 4$', \
       'residual_7.log' using 1:2 with lines ls 2 ti '$eigen 7$'
  
