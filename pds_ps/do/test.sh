make;

echo "Test: do -o 'echo test1' 'echo test2' 'echo test3':";
echo;
./do -o 'echo test1' 'echo test2' 'echo test3'

echo;
echo "Test: do -a 'echo test1' 'echo test2' 'echo test3':";
echo;
./do -a 'echo test1' 'echo test2' 'echo test3';

echo;
echo "Test: do -a -c 'echo test1' 'echo test2' 'echo test3':";
echo;
./do -a -c 'echo test1' 'echo test2' 'echo test3';

echo;
echo "Test: do -o -c 'echo test1' 'echo test2' 'echo test3':";
echo;
./do -o -c 'echo test1' 'echo test2' 'echo test3';

sleep 1;
echo;
echo "Test: do -o -c -k 'echo test1' 'gedit Makefile':";
echo;
./do -o -c -k 'echo test1' "gedit Makefile";

echo;
