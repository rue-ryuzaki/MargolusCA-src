# MargolusCA-src
MargolusCA source code

In project uses libconfig++, libpng, libmysqlcppconn

INSTALLATION
Use NetBeans IDE to work with project, or use this commands to build from terminal:

for debug:
/usr/bin/make -f Makefile CONF=Debug

for release:
/usr/bin/make -f Makefile CONF=Release

WORK
Program use libconfig++ configuration file.
Use `margolusca --help` to see help information
Use `margolusca --example > outFile` to generate example configuration file to outFile
