#include "configFile.hpp"

int checkForPort(char *port)
{
    for (size_t i = 0; i < std::strlen(port); i++)
    {
        if (port[i] < '0' || port[i] > '9'){
            printf("%c\n", port[i]);
            throw std::runtime_error("Invalid port");
    }}
    if (std::atoi(port) > 65535)
        throw (std::runtime_error("Invalid range of port"));
    return (1);
}



server *parseUser(int ac, char **av)
{
    User *myUser = new User;
    server *myServer = new server;
    std::string pswd(av[2]);
    if (ac != 3)
        throw std::runtime_error("ERROR: example of using: ./ircserv <port> <password> ");
    if (checkForPort(av[1]))
        myServer->port = std::atoi(av[1]);
    if (pswd.empty())
        throw std::runtime_error("Password invalid");
    myServer->password = av[2];
    myServer->name = "localhost";
    myServer->Users.push_back(*myUser);
    return (myServer);
}
