echo "On accorde les droits d'acces pour tous les utilisateurs sur le fichier test.txt";
chmod 777 test.txt
echo "Test droit de lecture";
./maccess test.txt -r;
echo "Resultat: $?";
echo "Test droits -r -w -x";
./maccess test.txt -r -w -x
echo "Resultat: $?";

echo "On retire les droits d'acces pour les utilisateurs sur le fichier test.txt";
chmod 000 test.txt
echo "Test droit de lecture";
./maccess test.txt -r;
echo "Resultat: $?";
echo "Test droits -r -w -x";
./maccess test.txt -r -w -x
echo "Resultat: $?";
