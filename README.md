# MargolusCA-src
MargolusCA source code

In project uses libconfig++, libpng, libmysqlcppconn

INSTALLATION

c++11 supported compiler (-std=c++11 option, g++ 4.8.1 or higher)

g++:

`apt-get install g++`

libpng:

`apt-get install libpng12-dev`

libmysqlcppconn (you must have mysql-server):

`apt-get install libmysqlcppconn-dev`

libconfig++:

`apt-get install libconfig++8-dev`

BUILD

Use NetBeans IDE to work with project, or use this commands to build from terminal:

for debug:

`/usr/bin/make -f Makefile CONF=Debug`

for release:

`/usr/bin/make -f Makefile CONF=Release`

WORK

Use `margolusca --help` to see help information

Usage:	margolusca [ARGUMENT] CONFIG	Run the program with current settings

	margolusca --help		Display this help and exit

	margolusca --version		Output version information and exit

	margolusca --name		Display program name and exit

	margolusca --path		Display program path and exit

	margolusca --example		Generate example of configuration file and exit

	margolusca --output filename	Print half-life in output file and exit

	margolusca --squareNx-Ny-Nz filename	Print surface square in output file and exit

	margolusca [filename]		Use filename configuration file

	margolusca [] -extra		Use express database out

	margolusca [] -retention	Use retention out

	margolusca [] -print		Print field parameters

	margolusca -testrun		Run test calculation

Program use libconfig++ configuration file.

Use `margolusca --example > outFile` to generate example configuration file to outFile
