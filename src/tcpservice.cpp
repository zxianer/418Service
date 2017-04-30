#include "tcpservice.h"
#include <string>
#include <algorithm>
#include <boost/bind.hpp>
using namespace boost::asio;

extern io_service service;

talk_to_client::talk_to_client () : sock_(service), started_(false)
{

}

void talk_to_client::start()
{
	started_ = true;
	do_read();
}

talk_to_client::ptr talk_to_client::new_()
{
	ptr new_(new talk_to_client);
	return new_;
}

void talk_to_client::stop()
{
	if (!started_) return;
	started_ = false;
	sock_.close();
}

ip::tcp::socket& talk_to_client::sock()
{
	return sock_;
}

void talk_to_client::on_read(const error_code& err, size_t bytes)
{
	if ( !started_ ) return;
	
	do_write("receive data ok");
}

void talk_to_client::on_write(const error_code& err, size_t bytes)
{
	do_read();
}

void talk_to_client::do_read() 
{
	sock_.async_read_some(buffer(read_buffer_), boost::bind(&talk_to_client::on_read, shared_from_this(), _1, _2));
}

void talk_to_client::do_write(const std::string& msg)
{
	if ( !started_ ) return;
	std::copy( msg.begin(), msg.end(), write_buffer_ );
	sock_.async_write_some(buffer(write_buffer_, msg.size()), boost::bind(&talk_to_client::on_write, shared_from_this(), _1, _2));
}
