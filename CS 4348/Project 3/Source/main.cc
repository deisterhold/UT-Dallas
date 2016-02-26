//Daniel Eisterhold
//CS4348 Project 2
//10 November 2015

#include <iostream>
#include <string.h>
#include <tclap/CmdLine.h>

#include "Server.h"
#include "FileManager.h"
#include "Client.h"

using namespace std;

int main(int argc, char* argv[]) {
  //Get the name of the executable
  char* programName = argv[0];
  if(strstr(programName, "server") != NULL) {
    try {
      TCLAP::CmdLine cmd("Creates a simple file server", ' ', "0.0.1");
      TCLAP::ValueArg<uint16_t> portArg("p", "port", "Port that the Server will accept connections on", true, 1234, "server port");
      cmd.add(portArg);
      cmd.parse(argc, argv);

      Server server;
      server.start(portArg.getValue());
    }
    catch(TCLAP::ArgException &e) {
      fprintf(stderr, "Error parsing: %s for arg %s\n", e.error().c_str(), e.argId().c_str());
    }
  }
  else if(strstr(programName, "client") != NULL) {
    try {
      TCLAP::CmdLine cmd("Creates a client to connect to a simple file server", ' ', "0.0.1");
      TCLAP::ValueArg<std::string> hostnameArg("n", "hostname", "Hostname of the machine that the client will connect to", true, "cs1", "hostname");
      TCLAP::ValueArg<uint16_t> portArg("p", "port", "Port that the client will connect to the server on", true, 1234, "port of server");
      cmd.add(portArg);
      cmd.add(hostnameArg);
      cmd.parse(argc, argv);
      Client client;
      client.start(hostnameArg.getValue(), portArg.getValue());
    }
    catch(TCLAP::ArgException &e) {
      fprintf(stderr, "Error parsing: %s for arg %s\n", e.error().c_str(), e.argId().c_str());
    }
  }

  return 0;
}
