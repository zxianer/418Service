#ifndef H_LOGICCONTROLLER_H
#define H_LOGICCONTROLLER_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "network_event_listener.h"

class logiccontroller : public boost::enable_shared_from_this<logiccontroller>, network_event_listener
{
public:
	logiccontroller();
	virtual ~logiccontroller();

	virtual void do_command();

private:

};

#endif
