#include "multuplixing.hpp"

void clearSets(int i, fd_set *master_re, fd_set *master_wr) //clear the sets and initialze some variables(select)
{
    printf("2\n");
    FD_CLR(i, master_re);
    printf("2\n");
    FD_SET(i, master_wr);
    printf("2\n");
}


int validSocket(int j, server *ser) //check if the j is a socket (need to be socket if want to work with methodes)
{
    if (ser->sock == j)
        return 0;
    return 1;
}


// void addSocket(conf *conf)
// {
//     for (int i = 0; i < conf->serversNumber; i++)
//         conf->vec.push_back(conf->ser[i].sock);
// }

void getSocket(server* ser) {
    struct addrinfo hints, *result;
    std::stringstream ss;
    // int socketAddr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)
    hints.ai_flags = AI_PASSIVE;     // Fill in my IP for me

    ss << ser->port;
    std::cout << ser->name << std::endl;

    if (getaddrinfo(ser->name.c_str(), ss.str().c_str(), &hints, &result) != 0) {
        throw std::runtime_error("Error in getting the address information");
    }

    if (result == nullptr) {
        throw std::runtime_error("Error in result");
    }

    if ((ser->sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1) {
        freeaddrinfo(result);
        throw std::runtime_error("Error in creating socket");
    }

    if (fcntl(ser->sock, F_SETFL, O_NONBLOCK) == -1) {
        close(ser->sock);
        freeaddrinfo(result);
        throw std::runtime_error("Error: fcntl() failed");
    }

    if (bind(ser->sock, result->ai_addr, result->ai_addrlen) == -1) {
        close(ser->sock);
        freeaddrinfo(result);
        throw std::runtime_error("Error in bind");
    }

    freeaddrinfo(result);

    if (listen(ser->sock, SOMAXCONN) == -1) {
        close(ser->sock);
        throw std::runtime_error("Error in listen");
    }
}