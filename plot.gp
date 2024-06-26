set terminal png
set output 'plot.png'

set xrange [0:4000]
set yrange [0:4000]

plot 'users.dat' with points pointtype 7 title 'Users', \
     'points.dat' with points pointtype 5 title 'Points'
