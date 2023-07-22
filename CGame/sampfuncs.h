#ifndef SAMPFUNCS_H
#define SAMPFUNCS_H

#include <vector>
#include <QString>
#include <windows.h>

typedef void(__stdcall *CommandProc) (std::string params);
struct stCommandInfo
{
	enum CommandType { NOPE, SCRIPT, PLUGIN };

	stCommandInfo(std::string, CommandType, void*);

	std::string					name;
	CommandType					type;
	void                        *owner;
};

class origSF
{
public:
	void *pPlugin;
};

class SAMPFUNCS
{
public:
	SAMPFUNCS();
	~SAMPFUNCS();
	bool isLoaded();

	void Log(const char*, ...);
	void Log(const QString &);
	void LogConsole(const char*, ...);
	void LogFile(const char*, ...);

	unsigned getAPIVersion();
	unsigned getSFVersion();

	void execConsoleCommand(std::string);
	std::vector<stCommandInfo> getConsoleCommands();
	void registerConsoleCommand(std::string, CommandProc);
	void setConsoleCommandDescription(std::string, std::string);
	void unregisterConsoleCommand(std::string);

	bool isConsoleOpened();

private:
	HMODULE lib = 0;
	origSF *SF;

	void (*_Log)(origSF*, const char*, ...);
	void (*_Log_str)(origSF*, const std::string &);
	void (*_LogConsole)(origSF*, const char*, ...);
	void (*_LogFile)(origSF*, const char*, ...);
	unsigned (*_getAPIVersion)(origSF*);
	unsigned (*_getSFVersion)(origSF*);
	void (*_execConsoleCommand)(origSF*, std::string);
	std::vector<stCommandInfo> (*_getConsoleCommands)(origSF*);
	void (*_registerConsoleCommand)(origSF*, std::string, CommandProc);
	void (*_setConsoleCommandDescription)(origSF*, std::string, std::string);
	void (*_unregisterConsoleCommand)(origSF*, std::string);
	bool (*_isConsoleOpened)(origSF*);
};

#endif // SAMPFUNCS_H
