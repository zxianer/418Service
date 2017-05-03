#include "packagedata.h"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

packagedata::packagedata():length_(0), type_(0), command_(0), subcommand_(0), version_("1.0.0.0"), data_("")
{

}

packagedata::~packagedata()
{

}

uint64_t packagedata::length()
{
	return length_;
}

uint64_t packagedata::type()
{
	return type_;
}

uint64_t packagedata::command()
{
	return command_;	
}

uint64_t packagedata::subcommand()
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

void packagedata::setlength(uint64_t length)
{
	length_ = length;
}

void packagedata::settype(uint64_t type)
{
	type_ = type;
}

void packagedata::setcommand(uint64_t command)
{
	command_ = command;
}

void packagedata::setsubcommand(uint64_t subcommand)
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
