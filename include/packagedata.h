#ifndef H_PACKAGEDATA_H
#define H_PACKAGEDATA_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <inttypes.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

class packagedata 
{
private:
	friend class boost::serialization::access;
	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(length_);
		ar & BOOST_SERIALIZATION_NVP(type_);
		ar & BOOST_SERIALIZATION_NVP(command_);
		ar & BOOST_SERIALIZATION_NVP(subcommand_);
		ar & BOOST_SERIALIZATION_NVP(version_);
		ar & BOOST_SERIALIZATION_NVP(data_);
	}

public:
	packagedata();
	~packagedata();

	uint64_t length();
	void setlength(uint64_t length);
	uint64_t type();
	void settype(uint64_t type);
	uint64_t command();
	void setcommand(uint64_t command);
	uint64_t subcommand();
	void setsubcommand(uint64_t subcommand);
	std::string data();
	void setdata(std::string data);
	std::string version();
	void setversion(std::string version);

private:
	uint64_t length_;
	uint64_t type_;
	uint64_t command_;
	uint64_t subcommand_;
	std::string version_;
	std::string data_; 
};

#endif
