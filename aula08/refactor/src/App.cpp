#include "App.h"

#define DEBUG std::cout << "aqui" << std::endl;

#include <string>
#include <iostream>
#include <fstream>

App::App(std::string& filename) : diary(filename)
{

}

int App::run(int argc, char* argv[])
{
  if (argc == 1)
  {
    return show_usage();
  }
  std::string action = argv[1];
  if (action == "add")
  {
    if (argc == 2)
    {
      add();
    }
    else
    {
      add(argv[2]);
    }
  }
  else if (action == "list")
  {
    list_messages();
  }
  else return show_usage();
  
  return 0;
}


void App::add()
{
  std::string message;
  std::cout << "Enter your message:" << std::endl;
  std::getline(std::cin, message);
  add(message);
}

void App::add(const std::string& message)
{
  if ( !diary.add(message) ) std::cerr << "Número máximo de mensagens excedido." << std::endl;
  if ( !diary.write()      ) std::cerr << "Erro na escrita do arquivo." << std::endl;
}

void App::list_messages()
{
  std::ifstream file(diary.filename);
  while (!file.eof())
  {
    std::string line;
    std::getline(file, line);
    if (line.size() != 0) std::cout << line << std::endl;
  }
  file.close();
}

int App::show_usage()
{
  std::cout << "Usage:\tdiary [option]\nOptions:" << std::endl;
  std::cout << "\tadd [message]\tAdiciona mensagem ao diário" << std::endl;
  std::cout << "\tlist\t\tLista mensagens do diário" << std::endl;
  return 1;
}
