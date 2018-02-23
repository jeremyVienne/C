touch test.txt;
echo -n "abcedfh\n" > test.txt;
echo -n "azerty\n" >> test.txt;
echo -n "qwerty\n" >> test.txt;
make tail;
make tail_efficace;
make tac_lseek;

echo;
echo "Test version simpliste de tail:";

echo "lecture par défaut:";
echo;

./tail test.txt;

echo;
echo "lecture des 2 dernieres lignes:";
echo;
./tail -n 2 test.txt;


echo;
echo;
echo "Test version efficace de tail:";
echo "Tampon= 16";

echo "lecture par défaut: ";
./tail_efficace test.txt;

echo;
echo "lecture des 2 dernieres ligne: "
./tail_efficace -n 2 test.txt;

echo;
echo "lecture des 5 dernieres lignes:"
./tail_efficace -n 5 test.txt;

echo;
echo;
echo "Test tac_lseek sur le fichier test.txt:"
echo;
./tac_lseek test.txt;
echo;
make clean;
rm -f test.txt
