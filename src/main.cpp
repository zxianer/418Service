#include <iostream>
#include <cstdio>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <inttypes.h>
#include "tcpconnection.h"
#include "packagedata.h"
#include "util.h"

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
	pd.setlength(8);
	std::ostringstream os;
	boost::archive::xml_oarchive oa(os);
	oa & BOOST_SERIALIZATION_NVP(pd);
	std::string content = os.str();

	std::vector<packagedata> pdlist;
	Util::param_stream_data(content, pdlist);	
	for ( int i = 0; i < pdlist.size(); i++ )
	{
		std::cout<< pdlist[i].version() << " " << pdlist[i].type() << " " << pdlist[i].length() << std::endl;
	}

	return 0;
}
