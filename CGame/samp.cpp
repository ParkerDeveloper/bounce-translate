#include "samp.h"
#include "loader.h"

template<typename T>
T GetSAMPPtrInfo(uint32_t offset)
{
	if (g_handle.samp == nullptr)
		throw "g_handle.samp has null";
	return *(T *)(g_handle.dwSAMP + offset);
}

void stSAMP::updateScoreboard()
{
	typedef void(__thiscall *stSAMP__updateScoreboard)(stSAMP *_this);
	(stSAMP__updateScoreboard(g_handle.dwSAMP + SAMP_FUNC_UPDATESCOREBOARDDATA))(this);
}

struct stChatInfo *stSAMP::chat()
{
	return GetSAMPPtrInfo<stChatInfo *>(SAMP_CHAT_INFO_OFFSET);
}

struct stInputInfo *stSAMP::input()
{
	return GetSAMPPtrInfo<stInputInfo *>(SAMP_CHAT_INPUT_INFO_OFFSET);
}

struct stKillInfo *stSAMP::kill()
{
	return GetSAMPPtrInfo<stKillInfo *>(SAMP_KILL_INFO_OFFSET);
}

struct stScoreboardInfo *stSAMP::scoreboard()
{
	return GetSAMPPtrInfo<stScoreboardInfo *>(SAMP_SCOREBOARD_INFO);
}

stMiscInfo *stSAMP::misc()
{
	return GetSAMPPtrInfo<stMiscInfo *>(SAMP_MISC_INFO);
}

SRColor stPlayerPool::playerColor(int id)
{
	if (g_handle.samp == nullptr)
		return 0;

	if (id < 0 || id > SAMP_MAX_PLAYERS)
		return 0;

	D3DCOLOR *color_table = ( D3DCOLOR * ) ( (uint8_t *)g_handle.samp + SAMP_VAR_COLOR_OFFSET );
	D3DCOLOR color = color_table[id];
	return (color << 24) | (color >> 8);
}

void stLocalPlayer::say(QString msg)
{
	typedef void(__thiscall *stLocalPlayer__say)(stLocalPlayer *_this, char* msg);
	(stLocalPlayer__say(g_handle.dwSAMP + SAMP_FUNC_SAY))(this, (char*)msg.toLocal8Bit().toStdString().c_str());
}

bool stInputInfo::addChatCommand(QString cmd, CMDPROC proc)
{
	if (iCMDCount == 144)
		return false;
	if (cmd.isEmpty())
		return false;
	if (cmd.length() > 32)
		return false;
	if (proc == nullptr)
		return false;

	strcpy(szCMDNames[iCMDCount], cmd.toLocal8Bit());
	pCMDs[iCMDCount] = proc;
	++iCMDCount;
	return true;
}

bool stInputInfo::deleteCommand(QString cmd)
{
	bool find = false;
	for (int i = 0; i < iCMDCount; ++i){
		if (cmd == szCMDNames[i])
			find = true;
		else if (find){
			strcpy(szCMDNames[i - 1], szCMDNames[i]);
			pCMDs[i - 1] = pCMDs[i];
		}
	}
	if (find)
		--iCMDCount;
	return find;
}

bool stInputInfo::sendCommand(QString cmdWithParams)
{
	if (cmdWithParams.isEmpty())
		return false;
	if (cmdWithParams.length() > 172)
		return false;

	if (cmdWithParams[0] != '/')
		cmdWithParams.push_front('/');

	typedef void(__thiscall *stInputInfo__sendCommand)(stInputInfo *_this, char* cmd);
	(stInputInfo__sendCommand(g_handle.dwSAMP + SAMP_FUNC_SENDCMD))(this, (char*)cmdWithParams.toLocal8Bit().toStdString().c_str());

	return true;
}

bool stInputInfo::execCommand(QString cmd, QString params)
{
	if (cmd.isEmpty())
		return  false;
	if (cmd.length() > 32)
		return false;
	if (params.length() > 128)
		return false;

	if (cmd[0] == '/')
		cmd.remove(0, 1);

	CMDPROC command = nullptr;
	for (int i = 0; i < iCMDCount; ++i){
		if (cmd == szCMDNames[i]){
			command = pCMDs[i];
			break;
		}
	}

	if (command == nullptr)
		return false;

	command((char*)params.toLocal8Bit().toStdString().c_str());
	return true;
}

bool stInputInfo::execCommand(int cmdId, QString params)
{
	if (cmdId < 0)
		return false;
	if (cmdId > iCMDCount)
		return false;
	if (params.length() > 128)
		return false;

	CMDPROC command = pCMDs[cmdId];
	if (command == nullptr)
		return false;

	command((char*)params.toLocal8Bit().toStdString().c_str());
	return true;
}

int stInputInfo::getCommandId(QString cmd)
{
	if (cmd.isEmpty())
		return  -1;
	if (cmd.length() > 32)
		return -1;

	if (cmd[0] == '/')
		cmd.remove(0, 1);

	for (int i = 0; i < iCMDCount; ++i)
		if (cmd == szCMDNames[i])
			return i;

	return -1;
}

bool stInputInfo::changeCommand(int cmdId, QString cmd, CMDPROC proc)
{
	if (cmdId < 0)
		return false;
	if (cmdId > iCMDCount)
		return false;
	if (cmd.isEmpty())
		return  false;
	if (cmd.length() > 32)
		return false;
	if (proc == nullptr)
		return false;

	strcpy(szCMDNames[cmdId], cmd.toLocal8Bit());
	pCMDs[cmdId] = proc;
	return true;
}

bool stInputInfo::changeCommand(int cmdId, QString cmd)
{
	return changeCommand(cmdId, cmd, pCMDs[cmdId]);
}

bool stInputInfo::changeCommand(int cmdId, CMDPROC proc)
{
	return changeCommand(cmdId, szCMDNames[cmdId], proc);
}

bool stInputInfo::changeCommand(QString cmd, CMDPROC proc)
{
	int cmdId = getCommandId(cmd);
	return changeCommand(cmdId, proc);
}

bool stInputInfo::changeCommand(QString cmd, QString new_cmd)
{
	int cmdId = getCommandId(cmd);
	return changeCommand(cmdId, new_cmd);
}

bool stInputInfo::changeCommand(QString cmd, QString new_cmd, CMDPROC proc)
{
	int cmdId = getCommandId(cmd);
	return changeCommand(cmdId, new_cmd, proc);
}

bool stChatInfo::addChatMessage(QString message, SRColor color)
{
	if (message.isEmpty())
		return false;
	if (message.length() > 143)
		return false;

	memcpy(chatEntry, (void*)((int)chatEntry + sizeof(stChatEntry)), 99 * sizeof(stChatEntry));
	chatEntry[99].clPrefixColor = 0;
	chatEntry[99].clTextColor = color.argb;
	chatEntry[99].iType = 8;
	strcpy(chatEntry[99].szText, message.toLocal8Bit());
	updateChat();
	return true;
}

bool stChatInfo::addChatMessage(std::string message, SRColor color)
{
	if (message.length() == 0)
		return false;
	if (message.length() > 143)
		return false;

	memcpy(chatEntry, (void*)((int)chatEntry + sizeof(stChatEntry)), 99 * sizeof(stChatEntry));
	chatEntry[99].clPrefixColor = 0;
	chatEntry[99].clTextColor = color.argb;
	chatEntry[99].iType = 8;
	strcpy(chatEntry[99].szText, message.c_str());
	updateChat();
	return true;
}

bool stChatInfo::addChatDebugMessage(QString message)
{
	return addChatMessage(message, clDebugColor);
}

bool stChatInfo::addChatTextMessage(QString message)
{
	return addChatMessage(message, clTextColor);
}

bool stChatInfo::addChatInfoMessage(QString message)
{
	if (addChatMessage(message, clInfoColor)){
		chatEntry[99].iType = 4;
		return true;
	}
	return false;
}

bool stChatInfo::addChatFullMessage(QString prefix, SRColor prefixColor, QString message, SRColor color)
{
	if (prefix.isEmpty())
		return false;
	if (prefix.length() > 27)
		return false;

	if (message.isEmpty())
		return false;
	if (message.length() > 143)
		return false;

	memcpy(chatEntry, (void*)((int)chatEntry + sizeof(stChatEntry)), 99 * sizeof(stChatEntry));
	chatEntry[99].clPrefixColor = prefixColor.argb;
	chatEntry[99].clTextColor = color.argb;
	chatEntry[99].iType = 2;
	strcpy(chatEntry[99].szPrefix, prefix.toLocal8Bit());
	strcpy(chatEntry[99].szText, message.toLocal8Bit());
	updateChat();
	return true;
}

void stChatInfo::addBlankChat()
{
	memcpy(chatEntry, (void*)((int)chatEntry + sizeof(stChatEntry) * pagesize), (100 - pagesize) * sizeof(stChatEntry));
	memset((void*)((int)chatEntry + sizeof(stChatEntry) * (100 - pagesize)), 0, sizeof(stChatEntry) * pagesize);
	updateChat();
}

void stChatInfo::deleteMessage(int id)
{
	deleteMessageNoUpdateChat(id);
	updateChat();
}

void stChatInfo::deleteDebugMessages()
{
	for (int i = 0; i < 100; ++i){
		while (chatEntry[i].iType == 8 && chatEntry[i].clTextColor == clDebugColor)
			deleteMessageNoUpdateChat(i);
	}
	updateChat();
}

void stChatInfo::deleteInfoMessages()
{
	for (int i = 0; i < 100; ++i){
		while (chatEntry[i].iType == 4 && chatEntry[i].clTextColor == clInfoColor)
			deleteMessageNoUpdateChat(i);
	}
	updateChat();
}

void stChatInfo::deleteUserMessages()
{
	for (int i = 0; i < 100; ++i){
		while (chatEntry[i].iType == 8 && chatEntry[i].clTextColor != clInfoColor && chatEntry[i].clTextColor != clDebugColor)
			deleteMessageNoUpdateChat(i);
	}
	updateChat();
}

void stChatInfo::clearChat()
{
	memset(chatEntry, 0, 100 * sizeof(stChatEntry));
	updateChat();
}

void stChatInfo::setPagesizeForce(int pagesize)
{
	typedef void(__thiscall *stChatInfo_setPagesizeForce)(stChatInfo* _this, int pagesize);
	(stChatInfo_setPagesizeForce(g_handle.dwSAMP + SAMP_FUNC_CHANGECHATSCROLLSIZE))(this, pagesize);
}

void stChatInfo::setChatPosition(POINT pos)
{
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x63fd6), pos.x);
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x63da0), pos.y);
	updateChat();
}

void stChatInfo::setInputBoxPosition(POINT pos)
{
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x65858), pos.x);
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x63FE6), pos.y);
}

void stChatInfo::setScrollBarPosition(POINT pos)
{
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x63647), pos.x);
	memsafe::write<int>((void*)(g_handle.dwSAMP + 0x6364E), pos.y);
	pDXUTScrollBar->pos[0] = pos.x;
	pDXUTScrollBar->pos[1] = pos.y;
	pDXUTScrollBar->update();
	//updateScrollBar();
}

POINT stChatInfo::getChatPosition()
{
	POINT pos;
	pos.x = memsafe::read<int>((void*)(g_handle.dwSAMP + 0x63fd6));
	pos.y = memsafe::read<int>((void*)(g_handle.dwSAMP + 0x63da0));
	return pos;
}

POINT stChatInfo::getInputBoxPosition()
{
	POINT pos;
	pos.x = memsafe::read<WORD>((int*)(g_handle.dwSAMP + 0x65858));
	pos.y = memsafe::read<WORD>((int*)(g_handle.dwSAMP + 0x63FE6));
	return pos;
}

POINT stChatInfo::getScrollBarPosition()
{
	POINT pos;
	pos.x = memsafe::read<int>((void*)(g_handle.dwSAMP + 0x63647));
	pos.y = memsafe::read<int>((void*)(g_handle.dwSAMP + 0x6364E));
	return pos;
}

void stChatInfo::updateChat()
{
	m_nPrevScrollBarPosition = 1;
}

void stChatInfo::updateScrollBar()
{
	typedef void(__thiscall *stChatInfo_setPagesizeForce)(stChatInfo* _this);
	(stChatInfo_setPagesizeForce(g_handle.dwSAMP + SAMP_FUNC_UPDATECHATSCROLLBAR))(this);
}

void stChatInfo::deleteMessageNoUpdateChat(int id)
{
	if (id != 99)
		memcpy((void*)((int)chatEntry + sizeof(stChatEntry) * id), (void*)((int)chatEntry + sizeof(stChatEntry) * (id + 1)), (99 - id) * sizeof(stChatEntry));
	memcpy((void*)((int)chatEntry + sizeof(stChatEntry)), chatEntry, 99 * sizeof(stChatEntry));
	memset(chatEntry, 0, sizeof(stChatEntry));
}

bool stKillInfo::addDead(int idKiller, int idVictim, uint8_t weapon)
{
	stPlayerPool *pPlayer = g_class.samp->pPools->pPlayer;

	if (!pPlayer->iIsListed[idKiller])
		return false;
	if (!pPlayer->iIsListed[idVictim])
		return false;

	memcpy(killEntry, (void*)((int)killEntry + sizeof(stKillEntry)), 4 * sizeof(stKillEntry));
	strcpy(killEntry[4].szKiller, pPlayer->pRemotePlayer[idKiller]->strPlayerName.c_str());
	strcpy(killEntry[4].szVictim, pPlayer->pRemotePlayer[idVictim]->strPlayerName.c_str());
	killEntry[4].clKillerColor = pPlayer->playerColor(idKiller).argb;
	killEntry[4].clVictimColor = pPlayer->playerColor(idVictim).argb;
	killEntry[4].byteType = weapon;
	return true;
}

void stMiscInfo::toggleCursor(bool iToggle)
{
	if (cursorType == eCursorType::System)
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	g_vars.isLocalCursorShowed = false;
	static POINT lastPos = {-1, -1};
	void		*obj = *(void **)(g_handle.dwSAMP + SAMP_MISC_INFO);
	((void(__thiscall *) (void *, int, bool)) (g_handle.dwSAMP + SAMP_FUNC_TOGGLECURSOR))(obj, iToggle ? 2 : 0, !iToggle);
	if (!iToggle)
	{
		GetCursorPos(&lastPos);
		((void(__thiscall *) (void *)) (g_handle.dwSAMP + SAMP_FUNC_CURSORUNLOCKACTORCAM))(obj);
		SetCursor(LoadCursor(NULL, NULL));
	} else if (lastPos.x != -1 && lastPos.y != -1) {
		SetCursorPos(lastPos.x, lastPos.y);
		g_vars.isLocalCursorShowed = true;
		if (cursorType == eCursorType::SAMP)
			return;
		SetCursor(LoadCursor(NULL, cursorType == eCursorType::System ? IDC_ARROW : NULL));
	}
}
