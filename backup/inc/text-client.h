/*
Written by Musa Azeem
TextClient class header
This file defines the TextClient class, which connects to a server, sends it a file and string to search for, and prints results recieved
Class Variables:
  kRead_buffer_size:    maximum number of bytes that can be read from server
  read_buffer:  character array to hold found lines recieved from server - is of size kRead_buffer_size
  path_str:     path to file to be searched
  search_str:   string to search for
Class Functions:
  Constructor:    defines class variables
  runClient:      starts socket client
  print_strings:  prints found strings to stdout in formatted manner
*/

#ifndef TEXTCLIENT
#define TEXTCLIENT
#include "../inc/Unix-Domain-Socket.h"
#include <string>

class TextClient: public UnixDomainSocket{
    public:
      explicit TextClient(const char *socket_path, const char *path_str, const char *search_str);
      void runClient();
    private:
      const size_t kRead_buffer_size = 1024;
      char read_buffer[1024];
      std::string path_str;
      std::string search_str;
      void print_strings();
};

#endif