#include "translator.h"
#include "CGame/methods.h"

translator::translator(QObject *parent) : QObject(parent)
{
	// Constructor
	g_class.SF->Log("{FF00FF00}Plugin %s has loaded", PROJECT_NAME);
	ini = new IniFile(QString(QString(PROJECT_NAME) + ".ini").toStdString(), "");
	translateAll();
}

translator::~translator()
{
	// Destructor
	g_class.SF->Log("{FFFF0000}Plugin %s has unloaded", PROJECT_NAME);
	restoreAll();
	delete ini;
}

void translator::Loop()
{
	// Main loop
}

bool translator::Event(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Events
	if (g_class.keys.isKeyDown(VK_SHIFT) && uMsg == WM_MBUTTONDBLCLK){
		restoreAll();
		translateAll();
		g_class.samp->chat()->addChatMessage(reloadMsg, g_class.samp->chat()->clInfoColor);
	}
	return true;
}

void translator::translateAll()
{
	reloadMsg = ini->esgString("translator", "reloadMsg", "~> All translates has been reloaded");
	translateCommands();
	translateScoreboard();
	translateHelpDialog();
	translateDL();
	translateNetStat();
	translateScreenshot();
	translateWarning();
	translateRejected();
	translateConnect();
	translateChat();
	translateNotif();
	translateCustom();
}

void translator::restoreAll()
{
	restoreCommands();
	restoreScoreboard();
	restoreHelpDialog();
	restoreDL();
	restoreNetStat();
	restoreScreenshot();
	restoreWarning();
	restoreRejected();
	restoreConnect();
	restoreChat();
	restoreNotif();
	restoreCustom();
}

void translator::translateCommands()
{
	aPagesize1020Li = new translate(ini, 0x64A88, "cmd/pagesize", 0xD7AC8);
	aValidFontsize3 = new translate(ini, 0x64B34, "cmd/fontsize", 0xD7AF0);
	aAudioMessage_0 = new translate(ini, 0x64C17, "cmd/audioMsgOff", 0xD7B20);
	aAudioMessagesO = new translate(ini, 0xD7B35, "cmd/audioMsgOn", 0xD7B34);
	aMemoryU = new translate(ini, 0x64C4D, "cmd/mem", 0xD7B48);
	aFrameLimiterVa = new translate(ini, 0x64CD6, "cmd/fpslimitError", 0xD7B54);
	aFrameLimiterU = new translate(ini, 0x64CBE, "cmd/fpsLimitSuccess", 0xD7B80);
	aHeadMovementsE = new translate(ini, 0x64D58, "cmd/headMoveOn", 0xD7BA4);
	aHeadMovementsD = new translate(ini, 0x64D25, "cmd/headMoveOff", 0xD7BC0);
	aUsagePlayer_sk = new translate(ini, 0x650B9, "cmd/playerSkin", 0xD7DA0);
	aUsageVVehicleI = new translate(ini, 0x65135, "cmd/spawnCar", 0xD7E08);
	aUsageSet_weath = new translate(ini, 0x65285, "cmd/setWeather", 0xD7E20);
	aInvalidTime_Us = new translate(ini, 0x65341, "cmd/invalidTime", 0xD7E44);
	aUsageSet_timeH = new translate(ini, 0x652D6, "cmd/helpTime", 0xD7E84);
	aIDonTKnowThatC = new translate(ini, {0x65E05, 0x65E53}, "cmd/unknownCommand", 0xD7F70);
	aOnfootPosition = new translate(ini, 0x64EEE, "cmd/onfootPos", 0xD7BEC);
	aAddplayerclass = new translate(ini, 0x64ED7, "cmd/addPlayerClass", 0xD7C08);
	aIncarPositionS = new translate(ini, 0x64E78, "cmd/incarPos", 0xD7C44);
	aAddstaticvehic = new translate(ini, 0x64E61, "cmd/AddStaticCar", 0xD7C5C);
	aICanTOpenTheSa = new translate(ini, 0x64DE0, "cmd/errorSavePos", 0xD7C94);
	aOnfootPosSaved = new translate(ini, 0x6507B, "cmd/onfootSaved", 0xD7CE0);
	aICanTOpenTheRa = new translate(ini, 0x6502A, "cmd/errorRawVeh", 0xD7D10);
	aIncarPosSaved = new translate(ini, 0x64FCB, "cmd/incarSaved", 0xD7D58);
	aNoRegisteredCo = new translate(ini, 0x1CE1C, "cmd/notRegistered", 0xD423C);
}

void translator::restoreCommands()
{
	delete aPagesize1020Li;
	delete aValidFontsize3;
	delete aAudioMessage_0;
	delete aAudioMessagesO;
	delete aMemoryU;
	delete aFrameLimiterVa;
	delete aFrameLimiterU;
	delete aHeadMovementsE;
	delete aHeadMovementsD;
	delete aUsagePlayer_sk;
	delete aUsageVVehicleI;
	delete aUsageSet_weath;
	delete aInvalidTime_Us;
	delete aUsageSet_timeH;
	delete aIDonTKnowThatC;
	delete aOnfootPosition;
	delete aAddplayerclass;
	delete aIncarPositionS;
	delete aAddstaticvehic;
	delete aICanTOpenTheSa;
	delete aOnfootPosSaved;
	delete aICanTOpenTheRa;
	delete aIncarPosSaved;
	delete aNoRegisteredCo;
}

void translator::translateScoreboard()
{
	aPing = new translate(ini, 0x6AD0A, "scoreboard/ping", 0xD8280);
	aScore = new translate(ini, 0x6ACCC, "scoreboard/score", 0xD8288);
	aName = new translate(ini, 0x6AC88, "scoreboard/name", 0xD8290);
	aId = new translate(ini, 0x6AC46, "scoreboard/id", 0xD8298);
	aPlayersD = new translate(ini, 0x6AAEB, "scoreboard/players", 0xD82B0);
	aPlayers10000 = new translate(ini, 0x6AB6F, "scoreboard/players10k", 0xD82A0);
}

void translator::restoreScoreboard()
{
	delete aPing;
	delete aScore;
	delete aName;
	delete aId;
	delete aPlayersD;
	delete aPlayers10000;
}

void translator::translateHelpDialog()
{
	aSaMpKeys = new translate(ini, 0x6746F, "help_dialog/title", 0xD8030);
	aBb9999F1Bbbbbb = new translate(ini, 0x6746A, "help_dialog/text", 0xD8040);
	aOk = new translate(ini, 0x67465, "help_dialog/key", 0xD81E4);
}

void translator::restoreHelpDialog()
{
	delete aSaMpKeys;
	delete aBb9999F1Bbbbbb;
	delete aOk;
}

void translator::translateDL()
{
	aIdDTypeDDistan = new translate(ini, 0x69455, "dl/unknown", 0xD8234);
	aIdDTypeDSubtyp = new translate(ini, 0x712CF, "dl/vehicles", 0xD83A8);
}

void translator::restoreDL()
{
	delete aIdDTypeDDistan;
	delete aIdDTypeDSubtyp;
}

void translator::translateNetStat()
{
	aClientNetworkS = new translate(ini, 0x5D6E9, "NetStat/title", 0xD7444);
	aProcessMemUkbW = new translate(ini, 0x5D60D, "NetStat/procMem", 0xD745C);
	aStreamingMemUm = new translate(ini, 0x5D57C, "NetStat/streamMem", 0xD7484);
	aIncarSendRateU = new translate(ini, 0x5D503, "NetStat/incarSendRate", 0xD74B4);
	aOnfootSendRate = new translate(ini, 0x5D4F6, "NetStat/onfootSendRate", 0xD74CC);
	aVehiclesUVehic = new translate(ini, 0x5D49D, "NetStat/vehInfo", 0xD74E8);
	aDownloadRate_2 = new translate(ini, 0x5D38C, "NetStat/downloadRate", 0xD7574);
}

void translator::restoreNetStat()
{
	delete aClientNetworkS;
	delete aProcessMemUkbW;
	delete aStreamingMemUm;
	delete aIncarSendRateU;
	delete aOnfootSendRate;
	delete aVehiclesUVehic;
	delete aDownloadRate_2;
}

void translator::translateScreenshot()
{
	aUnableToSaveSc = new translate(ini, 0x710EE, "Screenshot/error", 0xD8364);
	aScreenshotTake = new translate(ini, 0x710D8, "Screenshot/success", 0xD8380);
}

void translator::restoreScreenshot()
{
	delete aUnableToSaveSc;
	delete aScreenshotTake;
}

void translator::translateWarning()
{
	aWarningSExcept = new translate(ini, 0x5CF27, "Warning/except", 0xD73D0);
	aWarningOpcode0 = new translate(ini, 0x5CF10, "Warning/opcode", 0xD73F4);
	aWarningCould_0 = new translate(ini, {0xA18D9, 0x21FCCE}, "Warning/spawn", 0xD3DA8);
	aWarningBadObje = new translate(ini, 0xF506, "Warning/object", 0xD3DD0);
	aWarningActorUW = new translate(ini, 0x191F, "Warning/actor", 0xD35FC);
	aWarningIgnorin = new translate(ini, 0x19415, "Warning/largeTextDraw", 0xD411C);
	aWarningVehicle = new translate(ini, 0x1B5AD, "Warning/vehicle", 0xD4180);
}

void translator::restoreWarning()
{
	delete aWarningSExcept;
	delete aWarningOpcode0;
	delete aWarningCould_0;
	delete aWarningBadObje;
	delete aWarningActorUW;
	delete aWarningIgnorin;
}

void translator::translateRejected()
{
	aConnectionRe_0 = new translate(ini, {0x2AC46B, 0x2AE433, 0x2C4623}, "Rejected/slot", 0xD3C4C);
	aConnectionReje = new translate(ini, 0x26E071, "Rejected/badMod", 0xD3C84);
	aConnectionRe_1 = new translate(ini, 0x29A313, "Rejected/nick", 0xD3D38);
	aConnectionRe_2 = new translate(ini, 0x27375A, "Rejected/version", 0xD3D64);
}

void translator::restoreRejected()
{
	delete aConnectionRe_0;
	delete aConnectionReje;
	delete aConnectionRe_1;
	delete aConnectionRe_2;
}

void translator::translateConnect()
{
	aConnectingToSD = new translate(ini, {0x28E3B2, 0x2EEDAF}, "Connect/connecting", 0xD3998);
	aFailedToInitia = new translate(ini, {0x8856, 0xAE4B}, "Connect/failEncrypt", 0xD39EC);
	aYouAreBannedFr = new translate(ini, {0x8876, 0xAE36}, "Connect/banned", 0xD3A10);
	aServerHasAccep = new translate(ini, 0x8896, "Connect/accept", 0xD3A34);
	aTheServerIsFul = new translate(ini, {0x88B7, 0xAE5B}, "Connect/full", 0xD3A58);
	aServerClosedTh = new translate(ini, 0x88E7, "Connect/closed", 0xD3A78);
	aWrongServerPas = new translate(ini, {0x8927, 0xAE7C}, "Connect/password", 0xD3A98);
	aTheServerDidnT = new translate(ini, {0x8967, 0xAE9B}, "Connect/respone", 0xD3AB0);
	aTheServerIsRes = new translate(ini, 0xA23C, "Connect/restart", 0xD3B34);
	aLostConnection = new translate(ini, 0xA81D, "Connect/lost", 0xD3B50);
	aConnected_Join = new translate(ini, {0x282268, 0x293265, 0x308265}, "Connect/join", 0xD3B8C);
	aConnectedToB9c = new translate(ini, {0x24CE75, 0x2747F1, 0x2CF150}, "Connect/connected", 0xD3D8C);
}

void translator::restoreConnect()
{
	delete aConnectingToSD;
	delete aFailedToInitia;
	delete aYouAreBannedFr;
	delete aServerHasAccep;
	delete aTheServerIsFul;
	delete aServerClosedTh;
	delete aWrongServerPas;
	delete aTheServerDidnT;
	delete aTheServerIsRes;
	delete aLostConnection;
	delete aConnected_Join;
	delete aConnectedToB9c;
}

void translator::translateChat()
{
	aFfffffSaMpB9c9 = new translate(ini, {0x838A, 0x2647C9, 0x307432}, "Chat/startSamp", 0xD396C);
	aUseQuitToExitO = new translate(ini, 0x28DA0C, "Chat/exit", 0xD3CAC);
	aPleaseUseOnlyA = new translate(ini, 0x284496, "Chat/validNick", 0xD3CE0);
	aPleaseChooseAn = new translate(ini, 0x285245, "Chat/nickLen", 0xD3D00);
	aReturningToCla = new translate(ini, 0x799B, "Chat/changeClass", 0xD3910);
}

void translator::restoreChat()
{
	delete aFfffffSaMpB9c9;
	delete aUseQuitToExitO;
	delete aPleaseUseOnlyA;
	delete aPleaseChooseAn;
	delete aReturningToCla;
}

void translator::translateNotif()
{
	aRCarJackedW = new translate(ini, 0x12B8A, "Notif/carJacked", 0xD3EA8);
	aStayWithinTheR = new translate(ini, {0x3E11, 0x3EAC}, "Notif/worldBounds", 0xD3818);
}

void translator::restoreNotif()
{
	delete aRCarJackedW;
	delete aStayWithinTheR;
}

void translator::translateCustom()
{
	std::vector <std::string> arr = ini->getArrayString("translator", "custom");
	for (std::string p : arr){
		std::vector <std::string> params = ini->getParams(p);
		if (params.size() != 3)
			return;

		QString tr = params[1].c_str();
		if (tr.isEmpty())
			return;

		uint sampOffset = QString(params[0].c_str()).toUInt(nullptr, 16);
		if (sampOffset == 0)
			return;

		uint origOffset = QString(params[2].c_str()).toUInt(nullptr, 16);
		if (origOffset == 0)
			return;

		custom.push_back(new translate(ini, sampOffset, tr, origOffset));
	}
}

void translator::restoreCustom()
{
	for (translate *&tr : custom){
		if (tr == nullptr)
			continue;
		custom.removeOne(tr);
		delete tr;
		tr = nullptr;
	}
}
