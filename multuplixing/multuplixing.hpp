#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP


#include "../conf/configFile.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstdlib>
#include <string>
#include <csignal>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

class request
{
    public:
        int fd;
        std::string file;
        int fileIndex;
        char buff[1024];
        std::ofstream fileD;
    public:
        request(){};
        request (const request &copy){(void)copy;};
        request& operator=(const request &copy){
            (void)copy;
            return *this;
            };
};

class client{
    public:
        request req;
    public:
        // int     creatFile(int fd, char *buf);
        // void    getMethodes(std::string buf);


};

// std::vector <client> mycl;




class request;
void multuplixing (server *ser);
// int randomNum(); //get rendom number to add it in file[number].extention (post method)
// void getMethodes(std::string buf, client *cl); //check if the method is post to work with
// int creatFile(int fd, char *buf, client *cl); //creat the file (file+'random number' +.'extention)
void getRequestLenght(char *buf, client *cl); //get the request lenght of post so to know how many time i nead to read(post)
std::string getExtention(char *buf); //get the extention of what i receive (post)
// int getBody(char *buf);//get the only the body to put it in file to get the (image video or whatever the client want to post) (post method)
void handleCtrlZ(int signum, int i);
int maxFd(server *ser);
void clearSets(int i, fd_set *master_re, fd_set *master_wr); //clear the sets and initialze some variables(select)
int validSocket(int j, server *ser); //check if the j is a socket (need to be socket if want to work with methodes)
void addSocket(server *ser);
void getSocket(server *ser);

#endif
