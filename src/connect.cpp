#include "connect.h"

using boost::asio::io_service;
using boost::asio::ip::tcp;
using std::cout;


Connect::Connect(io_service& io, tcp::resolver::iterator iter, Protocol& prot)
    : _io_service(io), _socket(io), _protocol(prot), _queue()
{
    tcp::endpoint endpoint = *iter;
    _socket.async_connect(endpoint, 
            boost::bind(&Connect::handle_connect, this, boost::asio::placeholders::error, ++iter));
}

void Connect::write(std::string msg)
{
     _io_service.post(boost::bind(&Connect::do_write, this, msg));}

void Connect::handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iter)
{
    if (!error)
    {
        boost::asio::async_read_until(_socket, _msgBuffer, "\r\n",
                boost::bind(&Connect::handle_read, this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    }
    else if (endpoint_iter != tcp::resolver::iterator())
    {
        tcp::endpoint endpoint = *endpoint_iter;
        _socket.close();
        _socket.async_connect(endpoint,boost::bind(&Connect::handle_connect, 
                    this, boost::asio::placeholders::error, ++endpoint_iter));
    }
}

void Connect::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error)
    {
        std::istream is(&_msgBuffer);
        std::string line;
        std::getline(is, line);
        std::cout << line << "\n";
        boost::asio::async_read_until(_socket, _msgBuffer,"\r\n",
                boost::bind(&Connect::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cerr << "Error in handle_read: " << error << "\n";
        _socket.close();
    }
}

void Connect::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        _queue.pop_front();
        if(!_queue.empty())
        {
            boost::asio::async_write(_socket,boost::asio::buffer(_queue.front().c_str(),
            _queue.front().size()), boost::bind(&Connect::handle_write, this,
            boost::asio::placeholders::error));
        }
    }
    else
    {
        std::cerr << "Error in handle_write " << error << "\n";
        _socket.close();
    }
}

void Connect::do_write(std::string msg)
{
    bool writeInProgress = !_queue.empty();
    _queue.push_back(msg);
    if (!writeInProgress)
    {
        boost::asio::async_write(_socket, boost::asio::buffer(_queue.front().c_str(), _queue.front().size()),
                boost::bind(&Connect::handle_write, this, boost::asio::placeholders::error));
    }
}

void Connect::close()
{
    _socket.close();
}
