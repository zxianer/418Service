#ifndef H_UTIL_H
#define H_UTIL_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "packagedata.h"

namespace Util
{
	bool param_stream_data(const std::string& datastream, std::vector<packagedata>& datalist);

	bool make_stream_data(const packagedata& data, std::string& datastream);
};

#endif
