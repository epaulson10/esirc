#include <iostream>
#include <boost/thread.hpp>
#include "main.h"
#include "protocol.h"
#include "connect.h"

using std::cout;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    if (argc != 3){
        std::cerr << "USAGE: esirc <server> <port>\n";
        return 1;
    }
    Protocol p;
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator iter = resolver.resolve(query);
    //boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
    Connect client(io_service, iter,p);
    io_service.run();

    return 0;
}
