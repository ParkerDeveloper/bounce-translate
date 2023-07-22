#include "SRKeys.h"
#include "../loader.h"

struct key_alias
{
	int		key;
	char	*name;
};
static struct key_alias key_alias[] =
{
{ VK_LBUTTON, "VK_LBUTTON" },
{ VK_RBUTTON, "VK_RBUTTON" },
{ VK_MBUTTON, "VK_MBUTTON" },
{ VK_XBUTTON1, "VK_XBUTTON1" },
{ VK_XBUTTON2, "VK_XBUTTON2" },
{ VK_BACK, "VK_BACK" },
{ VK_TAB, "VK_TAB" },
{ VK_CAPITAL, "VK_CAPITAL" },
{ VK_RETURN, "VK_RETURN" },
{ VK_SHIFT, "VK_SHIFT" },
{ VK_LSHIFT, "VK_LSHIFT" },
{ VK_RSHIFT, "VK_RSHIFT" },
{ VK_CONTROL, "VK_RSHIFT" },
{ VK_LCONTROL, "VK_LCONTROL" },
{ VK_RCONTROL, "VK_RCONTROL" },
{ VK_MENU, "VK_MENU" },
{ VK_LMENU, "VK_LMENU" },
{ VK_RMENU, "VK_RMENU" },
{ VK_SPACE, "VK_SPACE" },
{ VK_PRIOR, "VK_PRIOR" },
{ VK_NEXT, "VK_NEXT" },
{ VK_END, "VK_END" },
{ VK_HOME, "VK_HOME" },
{ VK_LEFT, "VK_LEFT" },
{ VK_UP, "VK_UP" },
{ VK_RIGHT, "VK_RIGHT" },
{ VK_DOWN, "VK_DOWN" },
{ VK_INSERT, "VK_INSERT" },
{ VK_DELETE, "VK_DELETE" },
{ VK_PAUSE, "VK_PAUSE" },
{ VK_NUMPAD0, "VK_NUMPAD0" },
{ VK_NUMPAD1, "VK_NUMPAD1" },
{ VK_NUMPAD2, "VK_NUMPAD2" },
{ VK_NUMPAD3, "VK_NUMPAD3" },
{ VK_NUMPAD4, "VK_NUMPAD4" },
{ VK_NUMPAD5, "VK_NUMPAD5" },
{ VK_NUMPAD6, "VK_NUMPAD6" },
{ VK_NUMPAD7, "VK_NUMPAD7" },
{ VK_NUMPAD8, "VK_NUMPAD8" },
{ VK_NUMPAD9, "VK_NUMPAD9" },
{ VK_MULTIPLY, "VK_MULTIPLY" },
{ VK_ADD, "VK_ADD" },
{ VK_SEPARATOR, "VK_SEPARATOR" },
{ VK_SUBTRACT, "VK_SUBTRACT" },
{ VK_DECIMAL, "VK_DECIMAL" },
{ VK_DIVIDE, "VK_DIVIDE" },
{ VK_F1, "VK_F1" },
{ VK_F2, "VK_F2" },
{ VK_F3, "VK_F3" },
{ VK_F4, "VK_F4" },
{ VK_F5, "VK_F5" },
{ VK_F6, "VK_F6" },
{ VK_F7, "VK_F7" },
{ VK_F8, "VK_F8" },
{ VK_F9, "VK_F9" },
{ VK_F10, "VK_F10" },
{ VK_F11, "VK_F11" },
{ VK_F12, "VK_F12" },
{ VK_F13, "VK_F13" },
{ VK_F14, "VK_F14" },
{ VK_F15, "VK_F15" },
{ VK_F16, "VK_F16" },
{ VK_F17, "VK_F17" },
{ VK_F18, "VK_F18" },
{ VK_F19, "VK_F19" },
{ VK_F20, "VK_F19" },
{ VK_F21, "VK_F21" },
{ VK_F22, "VK_F22" },
{ VK_F23, "VK_F23" },
{ VK_F24, "VK_F24" },
{ VK_OEM_PLUS, "VK_OEM_PLUS" },
{ VK_OEM_COMMA, "VK_OEM_COMMA" },
{ VK_OEM_MINUS, "VK_OEM_MINUS" },
{ VK_OEM_PERIOD, "VK_OEM_PERIOD" },
{ VK_OEM_1, "VK_OEM_1" },
{ VK_OEM_2, "VK_OEM_2" },
{ VK_OEM_3, "VK_OEM_3" },
{ VK_OEM_4, "VK_OEM_4" },
{ VK_OEM_5, "VK_OEM_5" },
{ VK_OEM_6, "VK_OEM_6" },
{ VK_OEM_7, "VK_OEM_7" },
{ VK_OEM_8, "VK_OEM_8" },
{ VK_BROWSER_BACK, "VK_BROWSER_BACK" },
{ VK_BROWSER_FORWARD, "VK_BROWSER_FORWARD" },
{ VK_BROWSER_REFRESH, "VK_BROWSER_REFRESH" },
{ VK_BROWSER_STOP, "VK_BROWSER_STOP" },
{ VK_BROWSER_SEARCH, "VK_BROWSER_SEARCH" },
{ VK_BROWSER_FAVORITES, "VK_BROWSER_FAVORITES" },
{ VK_BROWSER_HOME, "VK_BROWSER_HOME" },
{ VK_VOLUME_MUTE, "VK_VOLUME_MUTE" },
{ VK_VOLUME_UP, "VK_VOLUME_UP" },
{ VK_VOLUME_DOWN, "VK_VOLUME_DOWN" },
{ VK_MEDIA_NEXT_TRACK, "VK_MEDIA_NEXT_TRACK" },
{ VK_MEDIA_PREV_TRACK, "VK_MEDIA_PREV_TRACK" },
{ VK_MEDIA_STOP, "VK_MEDIA_STOP" },
{ VK_MEDIA_PLAY_PAUSE, "VK_MEDIA_PLAY_PAUSE" },
{ VK_LAUNCH_MAIL, "VK_LAUNCH_MAIL" },
{ VK_LAUNCH_MEDIA_SELECT, "VK_MEDIA_PREV_TRACK" },
{ VK_LAUNCH_APP1, "VK_LAUNCH_APP1" },
{ VK_LAUNCH_APP1, "VK_LAUNCH_APP1" },
{ 0, "&0" },
};

SRKeys::SRKeys(QObject *parent) : QObject(parent)
{
	memset(code, 0, sizeof(code));
	keys = 0;
}

SRKeys::~SRKeys()
{
	for (auto &buf : codes)
		codes.removeOne(buf);
}

bool SRKeys::isKeyDown(int key)
{
	return keyDown[key];
}

bool SRKeys::isCode(QString code)
{
	if (codeLen < code.length())
		return false;

	for (int i = codeLen - code.length(); i < codeLen; ++i)
		if (this->code[i] != (uint)(code.toUpper()[i - (codeLen - code.length())].toLatin1()))
			return false;

	memset(this->code, 0, sizeof(this->code));
	codeLen = 0;
	return true;
}

bool SRKeys::isKeyComboDown(KeyCombo combo)
{
	if (combo.isEmpty())
		return false;
	for (int key : combo){
		if (!keyDown[key])
			return false;
	}
	return true;
}

void SRKeys::addCode(QString code)
{
	codes.push_back(code);
}

void SRKeys::addCombo(KeyCombo combo, QString name)
{
	combos[name] = combo;
}

KeyCombo SRKeys::getCombo(QString name)
{
	return combos[name];
}

void SRKeys::deleteCode(QString code)
{
	for(auto &buf : codes)
		if (buf == code)
			codes.removeOne(buf);
}

void SRKeys::deleteCombo(QString comboName)
{
	combos.remove(comboName);
}

QString SRKeys::getKey(int key)
{
	if (key >= 'A' && key <= 'Z')
		return QString((char)key);
	if (key >= '0' && key <= '9')
		return QString((char)key);

	for (int i = 0; key_alias[i].key != 0; ++i)
		if (key == key_alias[i].key)
			return key_alias[i].name;
	return "&0";
}

int SRKeys::getKey(QString key)
{
	if (key.length() == 1){
		char ch = key[0].toUpper().toLatin1();
		if (ch >= 'A' && ch <= 'Z')
			return (int)ch;
		if (ch >= '0' && ch <= '9')
			return (int)ch;
	}
	for (int i = 0; key_alias[i].key != 0; ++i)
		if (key == key_alias[i].name)
			return key_alias[i].key;
	return 0;
}

KeyCombo SRKeys::createCombo(QString keys, QString sep)
{
	KeyCombo combo;
	QStringList keyList = keys.split(sep);

	for (QString key : keyList)
		combo.push_back(getKey(key));

	return combo;
}

void SRKeys::onEvent(UINT uMsg, WPARAM wParam)
{
	if (uMsg == WM_XBUTTONDOWN && (wParam == 0x10020 || wParam == 0x20040))
	{
		if (wParam == 0x10020)
			wParam = VK_XBUTTON1;
		else if (wParam == 0x20040)
			wParam = VK_XBUTTON2;
		processKeyDown(wParam);
	}
	else if (uMsg == WM_XBUTTONUP && (wParam == 0x10020 || wParam == 0x20040))
	{
		if (wParam == 0x10020)
			wParam = VK_XBUTTON1;
		else if (wParam == 0x20040)
			wParam = VK_XBUTTON2;
		processKeyUp(wParam);
	}
	else if (uMsg == WM_LBUTTONDOWN)
		processKeyDown(VK_LBUTTON);
	else if (uMsg == WM_LBUTTONUP)
		processKeyUp(VK_LBUTTON);
	else if (uMsg == WM_RBUTTONDOWN)
		processKeyDown(VK_RBUTTON);
	else if (uMsg == WM_RBUTTONUP)
		processKeyUp(VK_RBUTTON);
	else if (uMsg == WM_MBUTTONDOWN)
		processKeyDown(VK_MBUTTON);
	else if (uMsg == WM_MBUTTONUP)
		processKeyUp(VK_MBUTTON);
	else if (uMsg == WM_LBUTTONDBLCLK){
		processKeyDown(VK_LBUTTON);
		processKeyUp(VK_LBUTTON);
	}
	else if (uMsg == WM_RBUTTONDBLCLK){
		processKeyDown(VK_RBUTTON);
		processKeyUp(VK_RBUTTON);
	}
	else if (uMsg == WM_MBUTTONDBLCLK){
		processKeyDown(VK_MBUTTON);
		processKeyUp(VK_MBUTTON);
	}
	else if (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN){
		processKeyDown(wParam);
		if (codeLen == 128){
			memcpy(code, (void*)((uint)code + sizeof(uint8_t)), 127 * sizeof(uint8_t));
			code[127] = wParam;
		} else{
			code[codeLen++] = wParam;
		}
		processCodes();
	}
	else if (uMsg == WM_KEYUP || uMsg == WM_SYSKEYUP)
		processKeyUp(wParam);
	else if (uMsg == WM_MOUSEWHEEL){
		if ( GET_WHEEL_DELTA_WPARAM( wParam ) < 0 )
			emit eventScrollDown();
		else emit eventScrollUp();
	}
}

void SRKeys::processKeyDown(int key)
{
	if (!keyDown[key]){
		keys++;
		keyDown[key] = true;
		emit eventKeyPressed(key);
		for(auto combo : combos.toStdMap())
			processCombo(combo.first);
	}
	emit eventKeyDown(key);
}

void SRKeys::processKeyUp(int key)
{
	keyDown[key] = false;
	emit eventKeyUp(key);
	keys--;
}

void SRKeys::processCodes()
{
	for (QString buf : codes){

		if (codeLen < buf.length())
			continue;

		bool callCode = true;
		for (int i = codeLen - buf.length(); i < codeLen; ++i){
			if (this->code[i] != buf[i - (codeLen - buf.length())].toUpper().toLatin1()){
				callCode = false;
				break;
			}
		}
		if (callCode)
			emit eventCode(buf);
	}
}

void SRKeys::processCombo(QString comboName)
{
	KeyCombo combo = combos[comboName];
	for(int comboKey : combo)
		if (!keyDown[comboKey])
			return;
	emit eventCombo(comboName);
}

