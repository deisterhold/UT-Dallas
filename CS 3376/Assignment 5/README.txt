This program demonstrates the use of static libraries, specifically rudeconfig and cryptopp, interprocess communication, inotify, and daemons.

This program should compile and run, but does not properly implement the use of inotify.

Compiling:
run "make"
To compile you will need the static libraries Crypto++ and RudeConfig installed

Running:
//Running program normally
type "./cs3376dirmond cs3376dirmond.conf"

//Running program as a daemon
type "./cs3376dirmon -d cs3376dirmond.conf"