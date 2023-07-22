#ifndef IniFile_H
#define IniFile_H

#include <windows.h>
#include <iostream>~`~
#include <string>
#include <vector>

class IniFile
{
public:
	IniFile(std::string ini_file_name, std::string ini_file_path, bool bcreate = true)
	{
		//if (ini_file_name.find(".ini") == std::string::npos)
		//	m_sIniFileName = ini_file_name + ".ini";
		//else
		m_sIniFileName = ini_file_name;
		if (ini_file_path.empty())
			m_sIniFilePath = getWorkingDirectory();
		else
		{
			createDirectory(ini_file_path);
			m_sIniFilePath = ini_file_path;
		}
		if (bcreate)
			create_new_ini_file();
	}
	~IniFile() {};

	bool	deleteIniFile()
	{
		if (ini_file_exist())
		{
			remove(getIniFileFullPath().c_str());
			return true;
		}
		return false;
	}
	std::string	getIniFileName()
	{
		return m_sIniFileName;
	}
	std::string	getIniFilePath()
	{
		return m_sIniFilePath;
	}
	std::string	getIniFileFullPath()
	{
		return m_sIniFilePath + m_sIniFileName;
	}

	std::string getWorkingDirectory()
	{
		char ppath[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, ppath);
		return std::string(ppath) + "\\";
	};
	std::string createDirectory(std::string ini_file_directory)
	{
		size_t first_splash = ini_file_directory.find_first_of('\\'), next_splash = std::string::npos;
		std::string dir = ini_file_directory.substr(0, first_splash);
		ini_file_directory = ini_file_directory.substr(first_splash, ini_file_directory.length());
		while ((next_splash = ini_file_directory.find("\\", 1)) != std::string::npos)
		{
			dir = dir + ini_file_directory.substr(0, next_splash);
			ini_file_directory = ini_file_directory.substr(next_splash, ini_file_directory.length());
			CreateDirectoryA(dir.c_str(), NULL);
		}
		return dir + "\\";
	}

	//SECTIONS
	bool existSection(std::string section_name)
	{
		DWORD asd = GetPrivateProfileStringA(section_name.c_str(), NULL, "", szBuffer, 3000, getIniFileFullPath().c_str());
		return (asd > 0) ? true : false;
	}
	std::vector <std::string> readSections()
	{
		int sections_count = ::GetPrivateProfileSectionNamesA(szBuffer, 3000, getIniFileFullPath().c_str());
		for (int i = 0; i < sections_count; i++)
			if (szBuffer[i] == '\0') szBuffer[i] = '\\';

		std::string sBuffer = szBuffer;
		std::vector <std::string> sections;
		size_t first_splash = 0, next_splash = std::string::npos;
		while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
		{
			sections.push_back(sBuffer.substr(first_splash, next_splash));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}
		return sections;
	}
	void deleteSection(std::string section_name)
	{
		WritePrivateProfileStringA(section_name.c_str(), NULL, NULL, getIniFileFullPath().c_str());
	}

	//KEYS
	bool existKey(std::string section_name, std::string key_name)
	{
		DWORD asd = GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), "", szBuffer, 3000, getIniFileFullPath().c_str());
		return (asd > 0) ? true : false;
	}
	std::vector <std::string> readKeys(std::string section_name)
	{
		int keys_count = ::GetPrivateProfileSectionA(section_name.c_str(), szBuffer, 3000, getIniFileFullPath().c_str());
		for (int i = 0; i < keys_count; i++)
			if (szBuffer[i] == '\0') szBuffer[i] = '\\';

		std::string sBuffer = szBuffer;
		std::vector <std::string> keys;
		size_t first_splash = 0, next_splash = std::string::npos;
		while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
		{
			keys.push_back(sBuffer.substr(first_splash, next_splash));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}
		for (size_t i = 0; i < keys.size(); i++)
			keys[i] = keys[i].substr(0, keys[i].find_first_of('='));

		return keys;
	}
	void deleteKey(std::string section_name, std::string key_name)
	{
		WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, getIniFileFullPath().c_str());
	}

	//GET FUNCTIONS
	int getInteger(std::string section_name, std::string key_name)
	{
		if (!ini_file_exist() || !existSection(section_name) || !existKey(section_name, key_name))
			return 0x80000000;

		return GetPrivateProfileIntA(section_name.c_str(), key_name.c_str(), 0, getIniFileFullPath().c_str());
	}
	float getFloat(std::string section_name, std::string key_name)
	{
		if (!ini_file_exist() || !existSection(section_name) || !existKey(section_name, key_name))
			return 0.0f;

		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		return std::stof(szBuffer);
	}
	std::string getString(std::string section_name, std::string key_name)
	{
		if (!ini_file_exist() || !existSection(section_name) || !existKey(section_name, key_name))
			return "";

		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		return szBuffer;
	}
	bool getBoolean(std::string section_name, std::string key_name)
	{
		if (!ini_file_exist() || !existSection(section_name) || !existKey(section_name, key_name))
			return false;

		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		if (!_stricmp("true", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("1", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("yes", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("on", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("���", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("��������", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("��������", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("�������", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("��", (char*)convToLowercase(szBuffer).c_str()))
			return true;
		return false;
	}
	DWORD getHex(std::string section_name, std::string key_name)
	{
		if (!ini_file_exist() || !existSection(section_name) || !existKey(section_name, key_name))
			return 0;

		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		DWORD HEX = 0;
		sscanf(szBuffer, "%X", &HEX);
		return HEX;
	}
	//ARRAYS
	std::vector <std::string> getArrayString(std::string section_name, std::string key_name)
	{
		int keys_count = ::GetPrivateProfileSectionA(section_name.c_str(), szBuffer, 3000, getIniFileFullPath().c_str());
		for (int i = 0; i < keys_count; i++)
			if (szBuffer[i] == '\0') szBuffer[i] = '\\';

		std::string sBuffer = szBuffer, szBuff;
		std::vector <std::string> keys_value;
		size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
		while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
		{
			unk = sBuffer.find_first_of('=');
			szBuff = sBuffer.substr(first_splash, unk);
			if (!strcmp(szBuff.c_str(), key_name.c_str()))
				keys_value.push_back(sBuffer.substr(unk + 1, next_splash - unk - 1));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}

		return keys_value;
	}
	void setArrayString(std::string key_name, std::vector <std::string> value)
	{
		FILE *f;
		f = fopen(getIniFileFullPath().c_str(), "at");
		char str[1000], tmp[1000];
		for (int i = 0; i < value.size(); i++)
		{
			memset(str, 0, sizeof(str));
			if (!i)sprintf(str, "%s = \"%s\"", key_name.c_str(), value[i].c_str());
			else sprintf(str, "%s \"%s\"", tmp, value[i].c_str());
			memset(tmp, 0, sizeof(tmp));
			strcpy(tmp, str);
		}
		strcat(str, "\n");
		size_t size = 0;
		while (str[size] != 0)
			size++;
		fwrite(str, size, 1, f);
		fclose(f);
	}
	std::vector <int> getArrayInt(std::string section_name, std::string key_name)
	{
		int keys_count = ::GetPrivateProfileSectionA(section_name.c_str(), szBuffer, 3000, getIniFileFullPath().c_str());
		for (int i = 0; i < keys_count; i++)
			if (szBuffer[i] == '\0') szBuffer[i] = '\\';

		std::string sBuffer = szBuffer, szBuff;
		std::vector <int> keys_int_value;
		size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
		while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
		{
			unk = sBuffer.find_first_of('=');
			szBuff = sBuffer.substr(first_splash, unk);
			if (!strcmp(szBuff.c_str(), key_name.c_str()))
				keys_int_value.push_back(atoi(sBuffer.substr(unk + 1, next_splash - unk - 1).c_str()));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}

		return keys_int_value;
	}
	std::vector <float> getArrayFloat(std::string section_name, std::string key_name)
	{
		int keys_count = ::GetPrivateProfileSectionA(section_name.c_str(), szBuffer, 3000, getIniFileFullPath().c_str());
		for (int i = 0; i < keys_count; i++)
			if (szBuffer[i] == '\0') szBuffer[i] = '\\';

		std::string sBuffer = szBuffer, szBuff;
		std::vector <float> keys_float_value;
		size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
		while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
		{
			unk = sBuffer.find_first_of('=');
			szBuff = sBuffer.substr(first_splash, unk);
			if (!strcmp(szBuff.c_str(), key_name.c_str()))
				keys_float_value.push_back(std::stof(sBuffer.substr(unk + 1, next_splash - unk - 1).c_str()));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}

		return keys_float_value;
	}

	std::vector <std::string> getParams(std::string str)
	{
		std::vector <std::string> params;
		size_t start_ip = std::string::npos, end_ip = std::string::npos;
		while ((start_ip = str.find('"')) != std::string::npos)
		{
			end_ip = str.find('"', start_ip + 1);
			params.push_back(str.substr(start_ip + 1, end_ip - 1));
			str = str.erase(0, str.find('"', end_ip + 1));
		}
		return params;
	}
	std::vector <std::string> getParams(std::string str, char *delimiter)
	{
		std::vector <std::string> params;
		size_t start_ip = std::string::npos, end_ip = std::string::npos;
		while ((start_ip = str.find(delimiter)) != std::string::npos)
		{
			end_ip = str.find(delimiter, start_ip + 1);
			params.push_back(str.substr(start_ip + 1, end_ip - 1));
			str = str.erase(0, str.find(delimiter, end_ip + 1));
		}
		return params;
	}
	std::vector <std::string> getParams(std::string str, char *s_delimiter, char *e_delimiter)
	{
		size_t slen = strlen(s_delimiter), elen = strlen(s_delimiter);
		std::vector <std::string> params;
		size_t start_ip = std::string::npos, end_ip = std::string::npos;
		while ((start_ip = str.find(s_delimiter)) != std::string::npos)
		{
			end_ip = str.find(e_delimiter, start_ip + slen);
			params.push_back(str.substr(start_ip + slen, end_ip - elen));
			str = str.erase(0, str.find(s_delimiter, end_ip + slen));
		}
		return params;
	}

	//SET FUNCTIONS
	void setInteger(std::string section_name, std::string key_name, DWORD value)
	{
		if (!ini_file_exist()) return;

		WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
	}
	void setFloat(std::string section_name, std::string key_name, float value)
	{
		if (!ini_file_exist()) return;

		WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
	}
	void setString(std::string section_name, std::string key_name, std::string text)
	{
		if (!ini_file_exist()) return;

		WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), text.c_str(), getIniFileFullPath().c_str());
	}
	void setBoolean(std::string section_name, std::string key_name, bool value, bool rus = false)
	{
		if (!ini_file_exist()) return;

		if (value) WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "��" : "true", getIniFileFullPath().c_str());
		else WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "���" : "false", getIniFileFullPath().c_str());
	}
	void setHex(std::string section_name, std::string key_name, DWORD HEX)
	{
		if (!ini_file_exist()) return;
		char szBuf[32];
		sprintf(szBuf, "%X", HEX);

		WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), szBuf, getIniFileFullPath().c_str());
	}

	//ADD FUNCTIONS
	void addInteger(std::string section_name, std::string key_name, DWORD value)
	{
		if (!ini_file_exist()) return;
		if (!existKey(section_name, key_name))
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
	}
	void addFloat(std::string section_name, std::string key_name, float value)
	{
		if (!ini_file_exist()) return;
		if (!existKey(section_name, key_name))
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
	}
	void addString(std::string section_name, std::string key_name, std::string text)
	{
		if (!ini_file_exist()) return;
		if (!existKey(section_name, key_name))
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), text.c_str(), getIniFileFullPath().c_str());
	}
	void addBoolean(std::string section_name, std::string key_name, bool value, bool rus = false)
	{
		if (!ini_file_exist()) return;
		if (!existKey(section_name, key_name))
			if (value) WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "��" : "true", getIniFileFullPath().c_str());
			else WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "���" : "false", getIniFileFullPath().c_str());
	}
	void addHex(std::string section_name, std::string key_name, DWORD HEX)
	{
		if (!ini_file_exist()) return;
		char szBuf[32];
		sprintf(szBuf, "%X", HEX);

		if (!existKey(section_name, key_name))
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), szBuf, getIniFileFullPath().c_str());
	}
	/*bool IniFile::AddArrayText(std::string section_name, std::string key_name, std::string text)
	{
	SF->Log("___trace AddArrayText");
	if (!ini_file_exist())
	return false;
	SF->Log("file exist");

	std::vector<char> file;
	loadfl(file, (char*)getIniFileFullPath().c_str());
	SF->Log("file loaded");

	char szInto[256];
	sprintf(szInto, "\r\n%s=%s", key_name.c_str(), text.c_str());
	SF->Log("key formated");
	for (int i = 0; i < strlen(szInto); ++i)
	file.push_back(0);
	SF->Log("add space");

	char szSection[256];
	sprintf(szSection, "[%s]", section_name.c_str());
	SF->Log("create section");
	char *pSection = strstr(file.data(), szSection);
	SF->Log("find section");
	if (!pSection)
	return false;
	SF->Log("Before: %d", (DWORD)(pSection - file.data()));
	pSection += section_name.length();
	SF->Log("After: %d", (DWORD)(pSection - file.data()));

	for (int i = file.size() - 1; i > pSection - file.data(); --i)
	file[i] = file[i - (pSection - file.data())];
	for (int i = pSection - file.data(); i < strlen(szInto); ++i)
	file[i] = szInto[i - (pSection - file.data())];

	savefl(file, (char*)getIniFileFullPath().c_str());
	return true;
	}*/

	int esgInteger(std::string section_name, std::string key_name, DWORD value)
	{
		if (!ini_file_exist()) return NULL;
		if (!existKey(section_name, key_name))
		{
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
			return value;
		}
		return GetPrivateProfileIntA(section_name.c_str(), key_name.c_str(), 0, getIniFileFullPath().c_str());
	}
	float esgFloat(std::string section_name, std::string key_name, float value)
	{
		if (!ini_file_exist()) return NULL;
		if (!existKey(section_name, key_name))
		{
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), std::to_string(value).c_str(), getIniFileFullPath().c_str());
			return value;
		}
		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		return std::stof(szBuffer);
	}
	std::string esgString(std::string section_name, std::string key_name, std::string text)
	{
		if (!ini_file_exist()) return NULL;
		std::string t = "empty";
		if (!existKey(section_name, key_name))
		{
			t = text;
			for (int i = 0; i < t.length(); ++i){
				if (t[i] == '\n')
					t.replace(i, 1, "\\n");
				else if (t[i] == '\t')
					t.replace(i, 1, "\\t");
			}
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), t.c_str(), getIniFileFullPath().c_str());
			return text;
		}
		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		t = szBuffer;
		for (int i = 0; i < t.length(); ++i){
			if (t[i] == '\\'){
				if (t[i + 1] == 'n')
					t.replace(i, 2, "\n");
				else if (t[i + 1] == 't')
					t.replace(i, 2, "\t");
			}
		}
		return t;
	}
	bool esgBoolean(std::string section_name, std::string key_name, bool value, bool rus = false)
	{
		if (!ini_file_exist()) return false;
		if (!existKey(section_name, key_name))
		{
			if (value) WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "��" : "true", getIniFileFullPath().c_str());
			else WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), rus ? "���" : "false", getIniFileFullPath().c_str());
			return value;
		}
		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		std::string str = (const char*)szBuffer;
		if (!_stricmp("true", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("1", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("yes", (char*)convToLowercase(szBuffer).c_str()) ||
			!_stricmp("��", (char*)convToLowercase(szBuffer).c_str()))
			return true;
		return false;
	}
	DWORD esgHex(std::string section_name, std::string key_name, DWORD HEX)
	{
		if (!ini_file_exist()) return 0;
		char szBuf[32];
		sprintf(szBuf, "%X", HEX);

		if (!existKey(section_name, key_name))
		{
			WritePrivateProfileStringA(section_name.c_str(), key_name.c_str(), szBuf, getIniFileFullPath().c_str());
			return HEX;
		}
		GetPrivateProfileStringA(section_name.c_str(), key_name.c_str(), NULL, szBuffer, sizeof(szBuffer), getIniFileFullPath().c_str());
		sscanf(szBuffer, "%X", &HEX);
		return HEX;
	}

private:
	char szBuffer[3000];
	std::string m_sIniFilePath;
	std::string m_sIniFileName;

	bool ini_file_exist()
	{
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFindIni;

		hFindIni = FindFirstFileA(getIniFileFullPath().c_str(), &FindFileData);
		if (hFindIni != INVALID_HANDLE_VALUE)
		{
			FindClose(hFindIni);
			return true;
		}

		FindClose(hFindIni);
		return false;
	}
	bool create_new_ini_file()
	{
		if (!ini_file_exist())
		{
			FILE *fp = fopen(getIniFileFullPath().c_str(), "w");
			if (fp != NULL)
				fclose(fp);

			return true;
		}
		return false;
	}
	std::string convToLowercase(char *str)
	{
		int sz = strlen(str);
		char ch[1024];
		memset(ch, 0, sizeof(ch));

		strcpy(ch, str);
		for (int i = 0; i < sz; i++)
		{
			if (ch[i] >= 0x41 && ch[i] <= 0x5a) ch[i] += 0x20;
			else if (ch[i] >= 0xc0 && ch[i] <= 0xdf) ch[i] += 0x20;
		}

		return (const char*)ch;
	}
};

#endif //IniFile_H
