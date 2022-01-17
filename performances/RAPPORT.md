# exercice 28 

## Question 1 et 2 
Cmd : 	`**/usr/bin/time -f '%e %U %S' ./myfile pow(2) testMe.txt > /dev/null**`

## Question 3   
```shell
for((i = 2; i < 33; i=i\*2)); do
        /usr/bin/time -f '%e %U %S' ./myfile $i testMe.txt > /dev/null
        printf '%s' "i = "
        printf '%d' "$i"
        printf $'\n'
        done
```
## Question 4 
1. execution scripty
2. utilisation du runMe.gnu
3. plot ex3.dat

