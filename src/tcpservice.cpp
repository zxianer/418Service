#include "tcpservice.h"
#include <string>
using namespace boost::asio;

io_service service;

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

}

void talk_to_client::on_write(const error_code& err, size_t bytes)
{

}
