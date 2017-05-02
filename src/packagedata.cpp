#include "packagedata.h"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

packagedata::packagedata():version_("1.0.0.0"), type_(0), command_(0), subcommand_(0), data_("")
{

}

packagedata::~packagedata()
{

}

int packagedata::type()
{
	return type_;
}

int packagedata::command()
{
	return command_;	
}

int packagedata::subcommand()
{
	return subcommand_;
}

std::string packagedata::data()
{
	return data_;
}

std::string packagedata::version()
{
	return version_;
}


void packagedata::settype(int type)
{
	type_ = type;
}

void packagedata::setcommand(int command)
{
	command_ = command;
}

void packagedata::setsubcommand(int subcommand)
{
	subcommand_ = subcommand;
}

void packagedata::setdata(std::string data)
{
	data_ = data;
}

void packagedata::setversion(std::string version)
{
	version_ = version;
}
