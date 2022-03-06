/*
Written by Musa Azeem
text client header
*/

#ifndef TEXTCLIENT
#define TEXTCLIENT
#include "../inc/Unix-Domain-Socket.h"
#include <string>

class TextClient: public UnixDomainSocket{
    public:
      explicit TextClient(const char *socket_path, const char *path_str, const char *search_str);
      void runClient();
      void print();
    private:
      // const size_t kRead_buffer_size = 64;
      const size_t kBuffer_size = 1024;
      char read_buffer[1024];
      std::string path_str;
      std::string search_str;
      void print_strings();
};

#endif