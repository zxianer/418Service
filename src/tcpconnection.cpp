#include <string>
#include <algorithm>
#include <boost/bind.hpp>
#include "tcpconnection.h"
#include "packagedata.h"
using namespace boost::asio;

extern io_service service;

tcpconnection::tcpconnection () : sock_(service), started_(false)
{

}

void tcpconnection::start()
{
	started_ = true;
	do_read();
}

tcpconnection::ptr tcpconnection::new_()
{
	ptr new_(new tcpconnection);
	return new_;
}

void tcpconnection::stop()
{
	if (!started()) return;
	started_ = false;
	sock_.close();
}

ip::tcp::socket& tcpconnection::sock()
{
	return sock_;
}


bool tcpconnection::started()
{
	return started_;
}

void tcpconnection::on_read(const error_code& err, size_t bytes)
{
	if ( !started() ) return;
	std::string msg(read_buffer_, bytes);
	do_write("receive data ok");
}

void tcpconnection::on_write(const error_code& err, size_t bytes)
{
	do_read();
}

void tcpconnection::do_read() 
{
	sock_.async_read_some(buffer(read_buffer_), boost::bind(&tcpconnection::on_read, shared_from_this(), _1, _2));
}

void tcpconnection::do_write(const std::string& msg)
{
	if ( !started() ) return;
	std::copy( msg.begin(), msg.end(), write_buffer_ );
	sock_.async_write_some(buffer(write_buffer_, msg.size()), boost::bind(&tcpconnection::on_write, shared_from_this(), _1, _2));
}
