//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <rude/config.h>

using namespace rude;
using std::string;
using std::map;

namespace parse
{
  template < typename T > std::string to_string( const T& v )
  {
    std::ostringstream stm ;
    return ( stm << v ) ? stm.str() : "{*** error ***}" ;
  }
}

map<string,string> parseConfigFile(string fileLocation) {
  map<string,string> settings;
  Config config;

  settings["verbose"] = "false";
  settings["logFile"] = "cs3376dirmond.log";
  settings["password"] = "mypassword";
  settings["numVersions"] = "10";
  settings["watchDirectory"] = "NULL";

  if(!config.load(fileLocation.c_str())) {
    std::cerr<<"Error loading configuration file: "<<config.getError()<<std::endl;
    return settings;
  }

  config.setSection("Parameters");
  bool verbose = config.getBoolValue("Verbose");
  string logFilename = config.getStringValue("LogFile");
  string password = config.getStringValue("Password");
  string numVersions = parse::to_string(config.getIntValue("NumVersions"));
  string directory = config.getStringValue("WatchDir");

  if(!(directory[directory.length()-1] == '/')) {
    directory += "/";
  }

  //Update settings from the default settings
  if(verbose) {
    settings["verbose"] = "true";
  }
  settings["logFile"] = logFilename;
  settings["password"] = password;
  settings["numVersions"] = numVersions;
  settings["watchDirectory"] = directory;

  if(settings["verbose"] == "true") std::cout<<"Verbose Logging."<<std::endl;
  else std::cout<<"Standard Logging."<<std::endl;
  std::cout<<"Log File: "<<settings["logFile"]<<std::endl;
  std::cout<<"Password: "<<settings["password"]<<std::endl;
  std::cout<<"Number of Versions: "<<settings["numVersions"]<<std::endl;
  std::cout<<"Watch Directory: "<<settings["watchDirectory"]<<std::endl;

  return settings;
}
