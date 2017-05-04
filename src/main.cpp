#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <inttypes.h>
#include <unistd.h>
#include "tcpconnection.h"
#include "easylogging++.h"
#include "backenddefine.h"
#include "network_event_listener.h"

using namespace boost::asio;

INITIALIZE_EASYLOGGINGPP

io_service service;

ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),8001));

void handle_accept(tcpconnection::ptr client, const boost::system::error_code& err)
{
	std::cout << "handle accept"<< std::endl;
	client->start();
	tcpconnection::ptr new_client = tcpconnection::new_();
	acceptor.async_accept(new_client->sock(), boost::bind(&handle_accept, new_client, _1));
}

std::string get_project_path()
{
	int index = -1;
	std::string logpath;
	char path[PATH_MAX];
	memset(path, 0, PATH_MAX);

	if ( readlink("/proc/self/exe", path, sizeof(path)) != -1 )
	{
		LOG(DEBUG) << "get_project_path success: " << path;
	}
	else 
	{
		LOG(DEBUG) << "get_project_path do not find project path";
	}

	logpath.assign(path);
	if( (index = logpath.find_last_of("/")) != -1 )
	{
		logpath = logpath.substr(0, index + 1 );
	}
	return logpath;
}

void initLogger()
{
	std::string logpath = get_project_path();
	logpath += "../conf/log.conf";
	el::Configurations conf(logpath.c_str());
	el::Loggers::reconfigureAllLoggers(conf);
}

int main()
{
	initLogger();

	/*
	tcpconnection::ptr client = tcpconnection::new_();
	acceptor.async_accept(client->sock(), boost::bind(&handle_accept, client, _1));
	service.run();
	*/

	return 0;
}
