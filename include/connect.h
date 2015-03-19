#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "protocol.h"

typedef std::deque<std::string> msg_queue;

class Connect
{
    public:
        Connect(boost::asio::io_service& io, boost::asio::ip::tcp::resolver::iterator iter,  Protocol& prot);
        void write(std::string str);
        void close();
    private:
        boost::asio::io_service& _io_service;
        boost::asio::ip::tcp::socket _socket;
        Protocol& _protocol;
        msg_queue _queue;
        boost::asio::streambuf _msgBuffer;
        void handle_connect(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iter);
        void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_write(const boost::system::error_code& error);
        void do_write(std::string msg);
};

#endif
