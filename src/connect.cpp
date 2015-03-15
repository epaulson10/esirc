#include "connect.h"

using boost::asio::io_service;
using boost::asio::ip::tcp;
using std::cout;

Connect::Connect(io_service& io, tcp::resolver::iterator iter, Protocol& prot)
    : _io_service(io), _socket(io), _protocol(prot)
{
    tcp::endpoint endpoint = *iter;
    _socket.async_connect(endpoint, 
            boost::bind(&Connect::handle_connect, this, boost::asio::placeholders::error, ++iter));
}

void Connect::handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iter)
{
    if (!error)
    {
        boost::asio::async_read_until(_socket, _msgBuffer, "\r\n",
                boost::bind(&Connect::handle_read, this, boost::asio::placeholders::error));
    }
    else if (endpoint_iter != tcp::resolver::iterator())
    {
        tcp::endpoint endpoint = *endpoint_iter;
        _socket.close();
        _socket.async_connect(endpoint,boost::bind(&Connect::handle_connect, 
                    this, boost::asio::placeholders::error, ++endpoint_iter));
    }
}

void Connect::handle_read(const boost::system::error_code& error)
{
    if (!error)
    {
        std::string text = boost::asio::buffer_cast<const char*>(_msgBuffer.data());
        _msgBuffer.consume(text.size());
        cout << text << "\n";
        boost::asio::async_read_until(_socket, _msgBuffer,"\r\n",
                boost::bind(&Connect::handle_read, this, boost::asio::placeholders::error));
    }
    else
    {
        std::cerr << "Error in handle_read: " << error << "\n";
        _socket.close();
    }
}
