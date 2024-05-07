#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
// #include <thread>
// #include <chrono>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>


class User{
    public:
        std::string password;
        std::string name;
        std::string nickname;
};

class server{
    public:
        int port;
        std::string password;
        std::vector<User> Users;
        std::string name;
        int sock;
        std::vector<int> client ;
};

server *parseUser(int ac, char **av);



#endif