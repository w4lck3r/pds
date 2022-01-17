for((i = 2; i < 33; i=i\*2)); do
    /usr/bin/time -f '%e %U %S' ./myfile $i testMe.txt > ex3.dat
    done