# Set the output to a png file
set terminal png size 500,500
# The file we'll write to
set output 'myfunc.png'

plot \
'./data/table_50000.txt' u 1:3, \
'./data/table_100000.txt' u 1:3, \
'./data/table_150000.txt' u 1:3, \
'./data/table_200000.txt' u 1:3, \
'./data/table_250000.txt' u 1:3, \
'./data/table_300000.txt' u 1:3, \
'./data/table_350000.txt' u 1:3, \
'./data/table_400000.txt' u 1:3, \
'./data/table_450000.txt' u 1:3, \

