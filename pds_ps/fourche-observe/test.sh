make;

echo "Test de multifourche.c:"
echo;


echo "Test avec ./multif true";
echo;
./multif true;

echo;
echo "Test avec ./multif true false true";
echo;
./multif true false true;

echo;
echo "execution course.c: "
echo;
./course;
make clean;
