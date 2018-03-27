README2 file from PROOL
Файл от Пруля

INSTALLATION

- download and unpacked MUD

- install packages (see README.txt)

mkdir build
cd build
cmake ..
make

mkdir /home/realms
mkdir /home/realms/realms

(Эти команды могут потребовать sudo. После создания каталога /home/realms/realms надо сделать ему chmod на вас как
пользователя Linux и проверить, чтобы обычный пользовтель (вы) могли туда писать)

cd ..
cp -r MUDhome/* /home/realms/realms

cp build/RealmsCode /home/realms/realms/bin
cp build/List /home/realms/realms/bin

./RealmsCode &

telnet localhost 3333 (или войти своим любимым MUD-клиентом, желательно из другого окна, чтобы консоль мад-сервера
не мешала)

Create player with name Dominus - is must be admin and dungeonmaster (DM). (See file server/global.cpp)
First password of Dominus - is general DM password - dmpass1984 (see file /home/realms/realms/config/config.xml)

Create another playes for play and enjoy

У меня все собралось: ОС Ubuntu 16.10 x86_64

gcc (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005

---

Prool, <proolix@gmail.com>, http://mud.kharkov.org

spring 2018, Kharkiv-city, Ukraine
