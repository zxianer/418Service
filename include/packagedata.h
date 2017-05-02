#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

class packagedata 
{
private:
	friend class boost::serialization::access;
	
	friend std::ostream& operator << (std::ostream& out, packagedata& pd)
	{
		out << "type:" << pd.type_ << "command:" << pd.command_ << "subcommand:"\
		   	<< pd.subcommand_ << "version:" << pd.version_ << "data:" << pd.data_;
		return out;
	}

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(type_);
		ar & BOOST_SERIALIZATION_NVP(command_);
		ar & BOOST_SERIALIZATION_NVP(subcommand_);
		ar & BOOST_SERIALIZATION_NVP(version_);
		ar & BOOST_SERIALIZATION_NVP(data_);
	}

public:
	packagedata();
	~packagedata();

	int type();
	void settype(int type);
	int command();
	void setcommand(int command);
	int subcommand();
	void setsubcommand(int subcommand);
	std::string data();
	void setdata(std::string data);
	std::string version();
	void setversion(std::string version);

private:
	std::string version_;
	int type_;
	int command_;
	int subcommand_;
	std::string data_; 
};
