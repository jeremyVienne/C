echo Construction arborescence de test;
mkdir test;
touch test/a;
touch test/b;
echo test > test/a;
make mdu;

echo Test 1: Arborescence du dossier de test:;
tree test;
echo;

echo; echo;
echo Test calcul taille apparente dossier test:;
./mdu -b test;

echo; echo;

echo Test calcul taille réelle dossier test:;
./mdu test;

echo;
echo;


mkdir test/e;
mkdir test/d;
touch test/d/f

echo Test 2: Arborescence du dossier de test:

cd test/e;
ln -s ../d;
echo;
cd ../../;
tree test;

echo;echo;

echo Test calcul taille apparente dossier test:;
./mdu -b test;

echo; echo;

echo Test calcul taille réelle dossier test:;
./mdu test;

echo;echo;
echo Test calcul en suivant les liens:;
./mdu -L test;
echo;
echo;

make clean;
