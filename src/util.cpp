#include "util.h"

namespace Util
{
	bool param_stream_data(const std::string& datastream, std::vector<packagedata>& datalist)
	{
		bool bRet = false;
		int previndex = -1;
		int nextindex = 0;
		std::string flag = "<?xml";
		while (true)
		{
			int index = datastream.find(flag,nextindex);
			if( index == 0 )
			{
				previndex = index;
				nextindex = previndex + flag.size();
				continue;
			}
			else if (index == -1 )
			{
				if( previndex != -1 )
				{
					std::string packagestream = datastream.substr(previndex, datastream.size() - previndex);
					packagedata pdata;
					std::istringstream is(packagestream);
					boost::archive::xml_iarchive ia(is);
					ia & BOOST_SERIALIZATION_NVP(pdata);
					datalist.push_back(pdata);
					bRet = true;
				}
				break;	
			}
			else 
			{
				std::string packagestream = datastream.substr(previndex, index - previndex);
				packagedata pdata;
				std::istringstream is(packagestream);
				boost::archive::xml_iarchive ia(is);
				ia & BOOST_SERIALIZATION_NVP(pdata);
				datalist.push_back(pdata);
				previndex = index;
				nextindex = previndex + flag.size();
				bRet = true;
			}
		}
		return bRet;
	}

	bool make_stream_data(const packagedata& data, std::string& datastream)
	{
		std::ostringstream os;
		boost::archive::xml_oarchive oa(os);
		oa & BOOST_SERIALIZATION_NVP(data);
		datastream = os.str();
		return true;
	}
};
