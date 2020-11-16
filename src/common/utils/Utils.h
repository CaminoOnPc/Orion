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

	static bool string_replace(std::string& str, const std::string& from, const std::string& to)
	{
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;

		str.replace(start_pos, from.length(), to);
		return true;
	}

	static void string_remove_line(std::string& str, const std::string& to)
	{
		size_t m = str.find(to);
		size_t n = str.find_first_of("\n", m + to.length());
		str.erase(m, n - m + 1);
	}

	static bool is_string_float(const std::string& str)
	{
		std::istringstream iss(str);
		float f;
		iss >> std::noskipws >> f; 
		return iss.eof() && !iss.fail();
	}

	static bool is_string_int(const std::string& str)
	{
		std::string::const_iterator it = str.begin();
		while (it != str.end() && std::isdigit(*it)) ++it;
		return !str.empty() && it == str.end();
	}

	static std::string get_current_directory()
	{
		return boost::filesystem::current_path().make_preferred().string();
	}

	static std::string get_font_directory()
	{
		WCHAR winDir[MAX_PATH];
		GetWindowsDirectory(winDir, MAX_PATH);

		std::wstring wsFontFile;
		wsFontFile.clear();

		std::wstringstream ss;
		ss << winDir << "\\Fonts\\" << wsFontFile;
		wsFontFile = ss.str();

		return std::string(wsFontFile.begin(), wsFontFile.end());
	}
}