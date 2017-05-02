#include <iostream>
#include <cstdio>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "tcpconnection.h"
#include "packagedata.h"

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
	/*
	tcpconnection::ptr client = tcpconnection::new_();
	acceptor.async_accept(client->sock(), boost::bind(&handle_accept, client, _1));
	service.run();
	*/
	packagedata pd;
	std::ostringstream os;
	boost::archive::xml_oarchive oa(os);
	oa & BOOST_SERIALIZATION_NVP(pd);
	std::string content = os.str();
	std::cout << content << std::endl;
	getchar();
	return 0;
}
