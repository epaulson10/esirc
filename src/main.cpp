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
    Connect client(io_service, iter,p);

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    char line [MAX_MSG_LEN];
    while (std::cin.getline(line, MAX_MSG_LEN))
    {
      using namespace std; // For strlen and memcpy.
      string msg(line);
      msg += "\r\n";
      client.write(msg);
    }

    t.join();
    client.close();

    return 0;
}
