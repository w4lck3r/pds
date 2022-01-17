tous: lstar lstar2 arrondi512
exec_tous: exec_arrondi512 exec_lstar run_lstar2

lstar: lstar.c
	gcc lstar.c -o lstar

exec_lstar:
	./lstar lstar.c

lstar2: lstar2.c arrondi512.o
	gcc lstar2.c -o lstar2

run_lstar2:
	./lstar2	lstar2.c

arrondi512: arrondi512.c
	gcc arrondi512.c -o arrondi512

exec_arrondi512:
	./arrondi512 arrondi512.c

clean: 
	rm -f lstar arrondi512

.PHONY:
	tous clean