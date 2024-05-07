#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>

struct client {
    // Define client structure as needed
};

struct server {
    int sock;
    int listen_fd;
    std::string name;
    int listen;
    std::vector<struct pollfd> _fds;
};

struct conf {
    int serversNumber;
    std::vector<server> ser;
    std::vector<int> vec; // Not sure what this is for
};

void getSocket(conf* conf) {
    for (int i = 0; i < conf->serversNumber; i++) {
        struct addrinfo hints, *result;
        std::stringstream ss;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)
        hints.ai_flags = AI_PASSIVE;     // Fill in my IP for me

        ss << conf->ser[i].listen;
        if (getaddrinfo(conf->ser[i].name.c_str(), ss.str().c_str(), &hints, &result) != 0)
            throw std::runtime_error("Error in getaddrinfo");

        conf->ser[i]._fds.reserve(10); // Reserve space for pollfd

        if ((conf->ser[i].sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1)
            throw std::runtime_error("Error creating socket");

        if (bind(conf->ser[i].sock, result->ai_addr, result->ai_addrlen) == -1) {
            close(conf->ser[i].sock);
            continue;
        }

        freeaddrinfo(result);

        if (listen(conf->ser[i].sock, SOMAXCONN) == -1) {
            close(conf->ser[i].sock);
            continue;
        }

        // Set socket to non-blocking
        int flags = fcntl(conf->ser[i].sock, F_GETFL, 0);
        fcntl(conf->ser[i].sock, F_SETFL, flags | O_NONBLOCK);
    }
}

void addFdPool(int fd, std::vector<struct pollfd>& _fds) {
    struct pollfd newPollfd;
    newPollfd.fd = fd;
    newPollfd.events = POLLIN;
    _fds.push_back(newPollfd);
}

void multiplexing(conf* conf) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    std::map<int, client> mycl;
    struct sockaddr_in client_addr;
    socklen_t clientAddrSize = sizeof(sockaddr_in);

    getSocket(conf);

    for (int i = 0; i < conf->serversNumber; i++) {
        addFdPool(conf->ser[i].sock, conf->ser[i]._fds);
    }

    std::cout << "Multiplexing... Start\n";
    while (true) {
        int ret = poll(conf->ser[0]._fds.data(), conf->ser[0]._fds.size(), -1);
        if (ret == -1)
            throw std::runtime_error("Error in poll");

        for (size_t i = 0; i < conf->ser[0]._fds.size(); i++) {
            if (conf->ser[0]._fds[i].revents & POLLIN) {
                // Handle new connections
                printf("{%d}\n", conf->ser[0]._fds[i].fd);
                int newFd = accept(conf->ser[0]._fds[i].fd, NULL, NULL);
                if (newFd == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // No new connections available right now, continue polling
                        continue;
                    } else {
                        // Another error occurred, handle it appropriately
                        perror("accept");
                        exit(1);
                    }
                }

        std::cout << "New connection\n";

        // Store client information
        client tmp; // Define your client structure as needed
        mycl.insert(std::pair<int, client>(newFd, tmp));
        conf->vec.push_back(newFd);

// Add new socket to _fds for polling
        addFdPool(newFd, conf->ser[0]._fds);

            } else {
                // Handle request data from existing clients
                std::map<int, client>::iterator iter = mycl.lower_bound(conf->ser[0]._fds[i].fd);
                client& cl = iter->second;
                int nbytes  = recv(conf->ser[0]._fds[i].fd, buffer, 1023, 0);

                if (nbytes == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // No data available right now, continue polling
                    continue;
                    } else {
                    // Another error occurred, handle it appropriately
                    perror("recv");
                    // You might want to close the socket or take other actions here
                    continue;
                    }
                    }
            }
        }
    }
}

int main() {
    // Example usage
    conf myConf;
    myConf.serversNumber = 1; // Adjust as needed
    server myServer;
    myServer.name = "localhost"; // Adjust as needed
    myServer.listen = 8080; // Adjust as needed
    myConf.ser.push_back(myServer);

    try {
        multiplexing(&myConf);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
