#include "sampfuncs.h"

SAMPFUNCS::SAMPFUNCS()
{
	lib =LoadLibraryA("SAMPFUNCS.asi");
	SF = new origSF();

	_Log = (void(*)(origSF*, const char*, ...))GetProcAddress(lib, "?Log@SAMPFUNCS@@QAAXPBDZZ");
	_Log_str = (void(*)(origSF*, const std::string &))GetProcAddress(lib, "?Log@SAMPFUNCS@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	_LogConsole = (void(*)(origSF*, const char*, ...))GetProcAddress(lib, "?LogConsole@SAMPFUNCS@@QAAXPBDZZ");
	_LogFile = (void(*)(origSF*, const char*, ...))GetProcAddress(lib, "?LogFile@SAMPFUNCS@@QAAXPBDZZ");
	_execConsoleCommand = (void(*)(origSF*, std::string))GetProcAddress(lib, "?execConsoleCommand@SAMPFUNCS@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	_getAPIVersion = (unsigned(*)(origSF*))GetProcAddress(lib, "?getAPIVersion@SAMPFUNCS@@QAEIXZ");
	_getConsoleCommands = (std::vector<stCommandInfo>(*)(origSF*))GetProcAddress(lib, "?getConsoleCommands@SAMPFUNCS@@QAE?AV?$vector@UstCommandInfo@@V?$allocator@UstCommandInfo@@@std@@@std@@XZ");
	_getSFVersion = (unsigned(*)(origSF*))GetProcAddress(lib, "?getSFVersion@SAMPFUNCS@@QAEIXZ");
	_isConsoleOpened = (bool(*)(origSF*))GetProcAddress(lib, "?isConsoleOpened@SAMPFUNCS@@QAE_NXZ");
	_registerConsoleCommand = (void (*)(origSF*, std::string, CommandProc))GetProcAddress(lib, "?registerConsoleCommand@SAMPFUNCS@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@P6GX0@Z@Z");
	_setConsoleCommandDescription = (void (*)(origSF*, std::string, std::string))GetProcAddress(lib, "?setConsoleCommandDescription@SAMPFUNCS@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	_unregisterConsoleCommand = (void (*)(origSF*, std::string))GetProcAddress(lib, "?unregisterConsoleCommand@SAMPFUNCS@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
}

SAMPFUNCS::~SAMPFUNCS()
{
	delete SF;
}

bool SAMPFUNCS::isLoaded()
{
	return lib != 0 && lib != INVALID_HANDLE_VALUE;
}

void SAMPFUNCS::Log(const char *Text, ...)
{
	if (!isLoaded())
		return;
	char format[102400];
	va_list		ap;
	va_start( ap, Text );
	vsprintf( format, Text, ap );
	va_end( ap );
	_Log(SF, "%s", format);
}

void SAMPFUNCS::Log(const QString &Text)
{
	if (!isLoaded())
		return;
	_Log_str(SF, Text.toStdString());
}

void SAMPFUNCS::LogConsole(const char *Text, ...)
{
	if (!isLoaded())
		return;
	char format[102400];
	va_list		ap;
	va_start( ap, Text );
	vsprintf( format, Text, ap );
	va_end( ap );
	_LogConsole(SF, "%s", format);
}

void SAMPFUNCS::LogFile(const char *Text, ...)
{
	if (!isLoaded())
		return;
	char format[102400];
	va_list		ap;
	va_start( ap, Text );
	vsprintf( format, Text, ap );
	va_end( ap );
	_LogFile(SF, "%s", format);
}

unsigned SAMPFUNCS::getAPIVersion()
{
	if (!isLoaded())
		return 0;
	return _getAPIVersion(SF);
}

unsigned SAMPFUNCS::getSFVersion()
{
	if (!isLoaded())
		return 0;
	return _getSFVersion(SF);
}

void SAMPFUNCS::execConsoleCommand(std::string cmd)
{
	if (!isLoaded())
		return;
	_execConsoleCommand(SF, cmd);
}

std::vector<stCommandInfo> SAMPFUNCS::getConsoleCommands()
{
	std::vector<stCommandInfo> dummy;
	if (!isLoaded())
		return dummy;
	return _getConsoleCommands(SF);
}

void SAMPFUNCS::registerConsoleCommand(std::string cmd, CommandProc CP)
{
	if (!isLoaded())
		return;
	_registerConsoleCommand(SF, cmd, CP);
}

void SAMPFUNCS::setConsoleCommandDescription(std::string cmd, std::string desc)
{
	if (!isLoaded())
		return;
	_setConsoleCommandDescription(SF, cmd, desc);
}

void SAMPFUNCS::unregisterConsoleCommand(std::string cmd)
{
	if (!isLoaded())
		return;
	_unregisterConsoleCommand(SF, cmd);
}

bool SAMPFUNCS::isConsoleOpened()
{
	if (!isLoaded())
		return false;
	return _isConsoleOpened(SF);
}
