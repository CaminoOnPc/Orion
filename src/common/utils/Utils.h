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

	static std::string get_key()
	{
		std::string key;

		if (wiInput::Press((wiInput::BUTTON)'1'))
		{
			key.append("1");
		}
		else if (wiInput::Press((wiInput::BUTTON)'2'))
		{
			key.append("2");
		}
		else if (wiInput::Press((wiInput::BUTTON)'3'))
		{
			key.append("3");
		}
		else if (wiInput::Press((wiInput::BUTTON)'4'))
		{
			key.append("4");
		}
		else if (wiInput::Press((wiInput::BUTTON)'5'))
		{
			key.append("5");
		}
		else if (wiInput::Press((wiInput::BUTTON)'6'))
		{
			key.append("6");
		}
		else if (wiInput::Press((wiInput::BUTTON)'7'))
		{
			key.append("7");
		}
		else if (wiInput::Press((wiInput::BUTTON)'8'))
		{
			key.append("8");
		}
		else if (wiInput::Press((wiInput::BUTTON)'9'))
		{
			key.append("9");
		}
		else if (wiInput::Press((wiInput::BUTTON)'0'))
		{
			key.append("0");
		}

		if (wiInput::Press((wiInput::BUTTON)'A'))
		{
			key.append("a");
		}
		else if (wiInput::Press((wiInput::BUTTON)'B'))
		{
			key.append("b");
		}
		else if (wiInput::Press((wiInput::BUTTON)'C'))
		{
			key.append("c");
		}
		else if (wiInput::Press((wiInput::BUTTON)'D'))
		{
			key.append("d");
		}
		else if (wiInput::Press((wiInput::BUTTON)'E'))
		{
			key.append("e");
		}
		else if (wiInput::Press((wiInput::BUTTON)'F'))
		{
			key.append("f");
		}
		else if (wiInput::Press((wiInput::BUTTON)'G'))
		{
			key.append("g");
		}
		else if (wiInput::Press((wiInput::BUTTON)'H'))
		{
			key.append("h");
		}
		else if (wiInput::Press((wiInput::BUTTON)'I'))
		{
			key.append("i");
		}
		else if (wiInput::Press((wiInput::BUTTON)'J'))
		{
			key.append("j");
		}
		else if (wiInput::Press((wiInput::BUTTON)'K'))
		{
			key.append("k");
		}
		else if (wiInput::Press((wiInput::BUTTON)'L'))
		{
			key.append("l");
		}
		else if (wiInput::Press((wiInput::BUTTON)'M'))
		{
			key.append("m");
		}
		else if (wiInput::Press((wiInput::BUTTON)'N'))
		{
			key.append("n");
		}
		else if (wiInput::Press((wiInput::BUTTON)'O'))
		{
			key.append("o");
		}
		else if (wiInput::Press((wiInput::BUTTON)'P'))
		{
			key.append("p");
		}
		else if (wiInput::Press((wiInput::BUTTON)'Q'))
		{
			key.append("q");
		}
		else if (wiInput::Press((wiInput::BUTTON)'R'))
		{
			key.append("r");
		}
		else if (wiInput::Press((wiInput::BUTTON)'S'))
		{
			key.append("s");
		}
		else if (wiInput::Press((wiInput::BUTTON)'T'))
		{
			key.append("t");
		}
		else if (wiInput::Press((wiInput::BUTTON)'U'))
		{
			key.append("u");
		}
		else if (wiInput::Press((wiInput::BUTTON)'V'))
		{
			key.append("v");
		}
		else if (wiInput::Press((wiInput::BUTTON)'W'))
		{
			key.append("w");
		}
		else if (wiInput::Press((wiInput::BUTTON)'X'))
		{
			key.append("x");
		}
		else if (wiInput::Press((wiInput::BUTTON)'Y'))
		{
			key.append("y");
		}
		else if (wiInput::Press((wiInput::BUTTON)'Z'))
		{
			key.append("z");
		}

		if (wiInput::Press(wiInput::BUTTON::KEYBOARD_BUTTON_SPACE))
		{
			key.append(" ");
		}

		if (wiInput::Down(wiInput::BUTTON::KEYBOARD_BUTTON_LSHIFT) || wiInput::Down(wiInput::BUTTON::KEYBOARD_BUTTON_RSHIFT))
		{
			if (wiInput::Press((wiInput::BUTTON)VK_OEM_MINUS))
			{
				key.append("_");
			}
		}

		if (wiInput::Press((wiInput::BUTTON)VK_OEM_PERIOD))
		{
			key.append(".");
		}

		

		return key;
	}
}