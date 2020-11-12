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
	static bool string_replace(std::string& str, const std::string& from, const std::string& to)
	{
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;

		str.replace(start_pos, from.length(), to);
		return true;
	}

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