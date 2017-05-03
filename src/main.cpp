#include <iostream>
#include <cstdio>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <inttypes.h>
#include "tcpconnection.h"

using namespace boost::asio;

io_service service;

ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),8001));

void handle_accept(tcpconnection::ptr client, const boost::system::error_code& err)
{
	std::cout << "handle accept"<< std::endl;
	client->start();
	tcpconnection::ptr new_client = tcpconnection::new_();
	acceptor.async_accept(new_client->sock(), boost::bind(&handle_accept, new_client, _1));
}

int main()
{
	tcpconnection::ptr client = tcpconnection::new_();
	acceptor.async_accept(client->sock(), boost::bind(&handle_accept, client, _1));
	service.run();

	/*
	packagedata pd1, pd2;
	std::string datastream1, datastream2;
	Util::make_stream_data(pd1, datastream1);
	Util::make_stream_data(pd2, datastream2);

	std::string content;
    content	+= datastream1;
	content += datastream2;

	std::vector<packagedata> pdlist;
	Util::param_stream_data(content, pdlist);	
	for ( uint64_t i = 0; i < pdlist.size(); i++ )
	{
		std::cout<< pdlist[i].version() << " " << pdlist[i].type() << " " << pdlist[i].length() << std::endl;
	}
	*/

	return 0;
}
