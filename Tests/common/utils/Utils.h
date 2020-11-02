/*
	File: Utils.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <Includes.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace Utils
{
	template <typename T> static std::string string_round(const T a_value, const int n = 2)
	{
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << a_value;
		return out.str();
	}

	static std::string get_current_directory()
	{
		return boost::filesystem::current_path().make_preferred().string();
	}
}