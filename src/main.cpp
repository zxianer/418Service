#include <iostream>
#include <cstdio>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "tcpservice.h"

using namespace boost::asio;

io_service service;

ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),8001));

void handle_accept(talk_to_client::ptr client, const boost::system::error_code& err)
{
	std::cout << "handle accept"<< std::endl;
	client->start();
	talk_to_client::ptr new_client = talk_to_client::new_();
	acceptor.async_accept(new_client->sock(), boost::bind(&handle_accept, new_client, _1));
}

int main()
{
	talk_to_client::ptr client = talk_to_client::new_();
	acceptor.async_accept(client->sock(), boost::bind(&handle_accept, client, _1));
	service.run();
	return 0;
}
