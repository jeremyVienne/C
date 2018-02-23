


#! /bin/sh -uf
# mcat -- campagne d'appels à mcat-scd
#
# Exemple de script shell, à compléter pour vos tests
 dd if=/dev/zero of=file.big bs=1k count=10000
make mcat;
# La commande à tester
MCAT=./mcat
# le fichier à lui mettre en entrée
MCAT_INPUT=file.big
# Le fichier de temps à générer
TIME_FILE=mcat-tm.dat

# la commande gnu time
TIME_CMD="/usr/bin/time"
# les options de cette commande
TIME_OPT="-f %e %U %S"
MCAT_BUFSIZ=1;

export MCAT_BUFSIZ;

# initialisation du fichier de résultats
rm -f $TIME_FILE && echo "# real user sys" > $TIME_FILE

# un autre exemple de boucle
for size in `awk 'BEGIN { for( i=1; i<=8388608; i*=2 ) print i }'`; do
    export MCAT_BUFSIZ=$size
    echo -n "$MCAT_BUFSIZ" >> $TIME_FILE;
    $TIME_CMD "$TIME_OPT" $MCAT $MCAT_INPUT > /dev/null 2>> $TIME_FILE

done

# un exemple de redirection des sorties standard et d'erreur
rm -f *.big;
make clean;

gnuplot run.gnu;
