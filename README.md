# MargolusCA-src
MargolusCA source code

In project uses libconfig++, libpng, libmysqlcppconn

INSTALLATION

c++11 supported compiler (-std=c++11 option, g++ 4.8.1 or higher)

g++:

    *`apt-get install g++`

libpng:

    *`apt-get install libpng12-dev`

libmysqlcppconn (you must have mysql-server):

    *`apt-get install libmysqlcppconn-dev`

libconfig++:

    *`apt-get install libconfig++8-dev`

*need root

BUILD

Use NetBeans IDE to work with project, or use this commands to build from terminal:

for debug:

`/usr/bin/make -f Makefile CONF=Debug`

for release:

`/usr/bin/make -f Makefile CONF=Release`

WORK
Program use libconfig++ configuration file.
Use `margolusca --help` to see help information
Use `margolusca --example > outFile` to generate example configuration file to outFile
