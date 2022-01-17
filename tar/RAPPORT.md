## Exercice 17
on a cree deux fichier le premier `test` qui contient 19 characters de 0 donc qui est de taille 20octets. Et le deuxieme un fichier `vide` donc 0 octets.
on cree une archive `test.tar` en lancant la commande `tar -H ustar -c vide test > test.tar`
On utilise la commande `od` pour lire le contenu de l'archive et le decoder a la main, par exemple on execute la commande: `od -Ad -t x1z -v test.tar`
on voit sur le terminal:
```
...
..
.
0010064 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010080 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010096 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010112 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010128 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010144 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010160 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010176 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010192 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010208 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010224 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  >................<
0010240
```
aux positions 636 (512 + 124) à 647 on a:
```
0000624 33 31 36 00 30 30 30 32 34 32 34 00 30 30 30 30  >316.0002424.0000<
0000640 30 30 30 30 30 32 34 00 31 34 31 33 31 35 35 36  >0000024.14131556<
```
la taille du fichier `test.tar` est:
```
00 30 30 30 30  >316.0002424.0000<
0000640 30 30 30 30 30 32 34
```
(donc 00000000024) 

Pour visualiser le contenue du fichier .tar sans l'avoir cree on utilise la commande: `tar -H ustar -c vide test | od -Ad -t x1z -v | less` et éviter ainsi de créer un fichier temporaire test.tar juste pour les tests.

## Exercice 18 (Arrondi au multiple de 512)
* on a cree la fonction arrondi512 de maniere mathematique, le seul cas unique est lorsque `n%512 == 0` le resultat sera le meme nombre passe en parametre `n`. Donc sans arrondissment. 
* Pour remplir un tampon systeme en utilise la commande `read`, pass au deuxieme parametre de la commande une adresse de la structure donne dans l'enonce `posix_header`.
* Pour verifier que le tampon a ete bien rempli on verifie que la valeur retourne par la commande read correspond bien a la taille du structure dans la memoire (et pas -1)
* on compile le programme avec la commande: `gcc arrondi512.c` et on l'execute sur le fichier test.tar avec la commande: `./a.out test.tar` on obtien un valeur en octal donc on doit la convertir en hexadecimal.

* 

## Exercice 19
* on a creer un main dans le fichier lstar , lstar2 pour recuperer la taille du fichier "bien evidamenet lstar2 et ameliorer pour recuperer la taille de tous les fichiers dans le dossier tar avec le nombre qu'on veut " . Dans la 1 ere version on a un probleme dans ` assert(r == sizeof(ph)); ` donc ` r = read(STDIN_FILENO, &ph, sizeof(ph)); ` n'a pa pu convertir le dossier a la structure une solution a été proposer dans lstar2 avec un ouvreture simple plus une affectation `fd = STDIN_FILENO; ` .
* Pour compiler et executer le prog do : `run_lstar test` , `run_lstar2 test`
* Pour verifier ` tar -H ustar -c test | lstar `

## Exercice 20
* La fonction et presque identique a la fonction precedante il y a juste un petite modification au niveux d'ajout une boucle pour passer par tous les fichiers dans le dossier avec le nombre qu'on veut ce nombre on peut le definire on avant par `#define nb 2 ` . 
* Pour compiler et executer le prog : `run_lstar2 test`

## Exercice 21
* La fonction et presque identique a la fonction precedante il y a juste un petite modification au niveux de la boucle pour passer par tous les fichiers dans le dossier 'elemination du compteur i ' . Mais on doit verifier que les donnes de la version et magic sont compatible avec la structure alors on recupere la version du fichier avec `memcpy(version , &hs.version[0],2);` on a choisi memcpy pour prendre les 2 premieres entiers  `if(strcmp(TMAGIC,hs.magic) != 0 || strcmp(TVERSION,version) != 0) ` 
* Pour compiler et executer le prog : `run_lstar2 test`

## Exercice 22
* On reste toujours dans le mecanisme de traiter tous les fichiers dans un dosier tar , On recuperant plusieurs nouveaux données size , name , drwx ... etc , on a fait un skip des octets du fichier avec lseek pour passer au fichier suivant .

## Exercice 23
* On a ajouter des operations pour verifier que le checksum est bon ; ` memset(hs.chksum, ' ', 8);
	    hs.chksum[6]='\0';
	    hs.chksum[7]=' ';
	    size_t checksum = 0;
	    const unsigned char* bytes= &hs; // get bytes of data's struct
	    for ( int i = 0; i < sizeof(struct posix_header); i++ ){
	    	    checksum += bytes[i]; //made the sum of all bytses
	        }

	    snprintf( hs.chksum, 8, "%06o", decimalToOctal(checksum ));
`

## Exercice 24
* Une petite verification avec asssert que le checksum qu'on a dans les données du fichier dans la structure et egale a le checksum qu'on a calculer `assert(hs.chksum == decimalToOctal(checksum));`
