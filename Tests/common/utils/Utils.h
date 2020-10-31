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

	static std::string convert_to_utf_8(const std::wstring& wstr)
	{
		const int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		const std::unique_ptr<char[]> buffer(new char[bufferSize]);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, buffer.get(), bufferSize, nullptr, nullptr);
		return std::string(buffer.get());
	}

	static std::wstring convert_to_utf_16(const std::string& str)
	{
		const int bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[bufferSize]);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.get(), bufferSize);
		return std::wstring(buffer.get());
	}

	template<typename T> static constexpr T get_mipmap_levels(T width, T height)
	{
		T levels = 1;
		while ((width | height) >> levels) {
			++levels;
		}
		return levels;
	}

	template<typename T> static constexpr T round_to_power_of_two(T value, int POT)
	{
		return (value + POT - 1) & -POT;
	}

	template<typename T> static constexpr bool is_power_of_two(T value)
	{
		return value != 0 && (value & (value - 1)) == 0;
	}
}