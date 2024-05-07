#include "multuplixing.hpp"
#include <poll.h> // Include for poll


void handleCtrlZ(int signum)
{
    (void )signum;

    // Raise the SIGINT signal to terminate the program
    std::raise(SIGINT);
}

int maxFd(server* ser)
{
    int tmp = 0;

    if (ser->sock > tmp)
            tmp = ser->sock;
    return tmp;

}

void multuplixing(server* ser)
{
    
    // std::map <int, client> mycl;
    // fd_set master_re, master_wr, read_fds, write_fds;    // master_re file descriptor list
    // int maxfd, newFd, in = 0;
    // getSocket(ser);
    // maxfd = maxFd(ser);

    // FD_ZERO(&master_re);
    // FD_ZERO(&master_wr);
    // FD_ZERO(&write_fds);
    // FD_ZERO(&read_fds); //clear the sets
    // // signal(SIGTSTP, handleCtrlZWrapper);
    // std::cout << "multuplixing...start\n";
    // FD_SET(ser->sock, &master_re);
    // for (;;)
    // {
    //     read_fds =  master_re;
    //     write_fds =  master_wr;
    //     printf("maxfd is:%d|%d\n",maxfd, ser->sock);

    //     if (select(maxfd + 1, &read_fds, &write_fds, NULL, NULL) == -1){
    //         perror("select");
    //         throw ("ERROR IN SELECT");
    //     }

    //     for (int i = 0; i  <= maxfd; i ++){
    //         if(FD_ISSET(i , &read_fds) || FD_ISSET(i , &write_fds))
    //         {
    //             if (!validSocket(i , ser))
    //             {
    //                 if ((newFd = accept(i , NULL, NULL)) == -1)
    //                     throw ("ERROR IN ACCEPTING\n");
    //                 std::cout << "new connection\n";
    //                 if (fcntl(newFd, F_SETFL, O_NONBLOCK) == -1)
    //                     throw std::runtime_error("Error: fcntl() failed");
    //                 // printf("accept...\n");
    //                 client tmp;
    //                 tmp.req.fd = newFd;
    //                 in++;
    //                 mycl.insert(std::pair<int, client>(newFd, tmp));
    //                 ser->client.push_back(newFd);
    //                 FD_SET(newFd, &master_re);
    //                 if (newFd > maxfd)
    //                     maxfd = newFd;
    //             }
    //             else
    //             {
    //                 if (FD_ISSET(i , &read_fds)){
    //                     std::map<int, client>::iterator iter = mycl.lower_bound(i );
    //                     client client = iter->second;
    //                     int nbytes = recv(i , iter->second.req.buff, sizeof(iter->second.req.buff), 0);
    //                     printf("---\n%s\n-----\n", iter->second.req.buff);
    //                     printf("her{%d}%d\n",nbytes,i);
    //                     sleep(1);
    //                     if (nbytes == -1){
    //                         std::cout << "errno set to " <<  strerror(errno) << '\n';
    //                         throw std::runtime_error("error in recv\n");
    //                     }
    //                     if (nbytes > 0){
    //                         //parse demande
    //                         clearSets(i , &master_re, &master_wr);
    //                         }
    //                     }
    //                     //working on request workRequest(buf);
    //                 }
    //                 if(FD_ISSET(i , &write_fds)){
    //                     send(i , "slma", 5, 0);
    //                     //send response
    //                     FD_CLR(i , &master_wr);
    //                     FD_CLR(i , &read_fds);
    //                     FD_CLR(i , &write_fds);
    //                     close (i );
    //                     mycl.erase(i );
    //                     // conf->vec.erase(std::remove(conf->vec.begin(), conf->vec.end(), i ));
    //                 }
    //         }
    //     }
    // }
}



//51154