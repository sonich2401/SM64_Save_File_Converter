#pragma once
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <iostream>
namespace sb {
	inline std::string openfn(std::string Title)
	{
		std::wstringstream cls;
		std::wstring src;
		cls.clear();
		cls << Title.c_str();
		const std::wstring title = cls.str();
		std::wstring filename(MAX_PATH, L'\0');
		OPENFILENAMEW ofn = { };
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"Any File\0*";
		ofn.lpstrFile = &filename[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = title.c_str();
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameW(&ofn))
		{
			src = filename;
			std::string str(src.begin(), src.end());
			return str;
		}
		return "NULL";
	}
	inline std::string savefn(std::string Title)
	{
		std::wstringstream cls;
		std::wstring src;
		std::wstring filetypes = cls.str();
		cls.clear();
		cls << Title.c_str();
		const std::wstring title = cls.str();
		std::wstring filename(MAX_PATH, L'\0');
		OPENFILENAMEW ofn = { };
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"Any File\0*";
		ofn.lpstrFile = &filename[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = title.c_str();
		ofn.Flags = OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT;
		if (GetSaveFileNameW(&ofn))
		{
			src = filename;
			std::string str(src.begin(), src.end());
			return str;
		}
		return "NULL";
	}
}
