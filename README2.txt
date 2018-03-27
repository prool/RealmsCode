README2 file from PROOL
Файл от Пруля

INSTALLATION

- download and unpacked MUD

- install packages (see README.txt)

mkdir build
cd build
cmake ..
make

- create directory /home/realms/realms

cp -r MUDhome/* /home/realms/realms

cp build/RealmsCode /home/realms/realms/bin
cp build/List /home/realms/realms/bin

./RealmsCode &

telnet localhost 3333

Create player with name Proolix - is must be admin and dungeonmaster

Create another playes for play and enjoy

Prool, <proolix@gmail.com>, http://mud.kharkov.org

spring 2018, Kharkiv-city, Ukraine
