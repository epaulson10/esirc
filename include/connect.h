#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "protocol.h"

class Connect
{
    public:
        Connect(boost::asio::io_service& io, boost::asio::ip::tcp::resolver::iterator iter,  Protocol& prot);
    private:
        boost::asio::io_service& _io_service;
        boost::asio::ip::tcp::socket _socket;
        Protocol& _protocol;
        boost::asio::streambuf _msgBuffer;
        void handle_connect(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iter);
        void handle_read(const boost::system::error_code& error);
        void handle_write(std::string msg);
};

#endif
