## 1.2  Afficher les métadonnées d’un i-nœud
### Exercice 5 :

* 1 etape :  Creation du fichier test
    * touch test.txt / "creation du fichier"
    * cat > test.txt
    * ecrire dans le fichier 
    * ctr + D / "sauvgarder et sortir"

* 2 etape :  Tester la commande stat
    * representer dans le champ ou existe le fichier test 
    * cd /home/salmib/Desktop/pds-fs-el-ansari-salmi-gr-4/stat
    * stat test.txt 

* resultat :
```  
        File: test / "nom"
        Size: 8033 /"taille du fichier" Blocks: 16 /"nombre d'allocation Blocks utiliser par le fichier"                 IO Block: 4096 / "taille des bites par Block"  regular file / "type du fichier" (ex regular file, directory, symbolic link)
                      Device: 805h/2053d /"numero d'appareil en hexadicimal"	Inode: 1193131  /"inode numero"   Links: 1
                      Access: (0664/-rw-rw-r--) /"permssion du fichier " Uid: ( 1000/  salmib) /"utilisateur iD et nom"  Gid: ( 1000/  salmib) /"groupe ID et le nom du proprietaire"
                      Access: 2021-09-19 03:05:24.580623034 -0700 / "dernier fois acceder au fichier"
                      Modify: 2021-09-19 03:05:24.580623034 -0700 / "dernier fois de modification du fichier"
                      Change: 2021-09-19 03:05:24.580623034 -0700 / "dernier fois le fichier a été changé"
                      Birth: - / "date de creation du fichier"
```

### Exercice 6 : 
* etape 1 : whatis stat / "display manuel page dans une ligne"
* etage 2 : man 1 stat / "on type le nombre du section + nom du fichier"

### Exercice 7 :
revoir la question 5 ; on peut tout traduire en entier et utiliser ça dans notre programme C ,return negatif si faillure
il existe deja une fonction stat dans la biblioteque : `int stat(const char *path, struct stat *buf); / <sys/stat.h>`
plus y a des fonction deja preparer a (utiliser S_IRUSR    00400   )  le propriétaire a le droit de lecture?   S'il         réussit, cet appel système renvoie 0. S'il échoue, il renvoie -1 

### Exercice 8 :
        le numero du bloc ça commance par 0 si le fichier est vide car on n'a pas besoin d'allouer une memoire d'allocation
        apres si on ecrit quelque chose meme si un caractere ça augment a 8 ; en generale c'est 2 pow(n) n >= 0 "mais faut pas passer  la taille de la zone memoire"
        * creation du hard link : ln [source] [destination]
        * creation du soft link : ln [-sf [source] [destination]

### Exercice 9 :
        * creation du hard link : ln [source] [destination]
        * creation du soft link : ln [-s] [source :  "test"] [destination : ex "test_soft_link"]
        * creation du fichier copier : cp [source :  "test"] [destination : ex "test_hard_link"]

### Exercice 10 :
        * -BLOC- pour numero du bloc on remarque que le fichier test , copy-test on hard-link-test : ont le meme numero du bloc
          par contre pour le fichier soft-link-test est toujours a zero .
        * -INODE- 
            * test :            Inode: 1182147 / decalage par le fichier
            * test_copy :       Inode: 1193132 / suivi du nombre inode dans les fils du fichier test            
            * test_hard_link :  Inode: 1193133              
            * test_soft_link :  Inode: 1193134 

        *  On peut recuperer le contenue du fichier test par : `test_copy` , `test_hard_link`

### Exercice 11 / 12 / 13:
        * regarde le fichier stat.c

