//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502


#include <map>
#include <string>
#include <tclap/CmdLine.h>

using namespace std;

map<string,string> parseCommandLine(int argc, char *argv[]) {
  map<string,string> arguments;

  arguments["daemonMode"] = "false";
  arguments["configFile"] = "cs3376dirmond.conf";

  try {
    TCLAP::CmdLine cmd("cs3376dirmond Directory Monitor Daemon", ' ', "1.0.0");
    TCLAP::SwitchArg daemonFlag("d","daemon","Run in daemon mode (forks to run as daemon).",cmd,false);
    
    TCLAP::UnlabeledValueArg<string> configFileName("configFile","The name of the configuration file. Defaults to cs3376dirmond.conf",false,"cs3376dirmond.conf","config filename",true);
    cmd.add(configFileName);
    
    cmd.parse(argc, argv);
    if(daemonFlag.getValue()) {
      std::cout<<"Running in daemon mode."<<std::endl;
      arguments["daemonMode"] = "true";
    }
    
    arguments["configFile"] = configFileName.getValue();
    
    std::cout<<"File name: \""<<configFileName.getValue()<<"\""<<std::endl;
    
  }
  catch(TCLAP::ArgException &e) {
    std::cerr<<"Error: "<<e.error()<<" for argument "<<e.argId()<<std::endl;
    exit(1);
  }
  return arguments;
}
