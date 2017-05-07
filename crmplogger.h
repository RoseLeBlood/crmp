#ifndef CRMPLOGGER_H
#define CRMPLOGGER_H

#include <Qt>
#include <iostream>



class crmplogger
{
public:
  static void LogError(std::string Text, std::string Function)
  {
    std::cout << "Error: [" << Function << "] " << Text << std::endl;
  }
  static void LogOk(std::string Text, std::string Function)
  {
    std::cout << "OK: [" << Function << "] " << Text << std::endl;
  }
  static void LogInfo(std::string Text, std::string Function)
  {
    std::cout << "Info: [" << Function << "] " << Text << std::endl;
  }
};

#endif // CRMPLOGGER_H
