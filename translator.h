#ifndef translator_H
#define translator_H

#include <QObject>
#include "loader.h"
#include "d3d9/d3drender.h"
#include "d3d9/texture.h"
#include "d3d9/MenuManager/WidgetBase.h"
#include "d3d9/MenuManager/Node.h"
#include "d3d9/MenuManager/VerticalLayout.h"
#include "d3d9/MenuManager/Listing.h"
#include "d3d9/MenuManager/Slider.h"
#include "d3d9/MenuManager/Text.h"
#include "d3d9/MenuManager/Menu.h"
#include "d3d9/MenuManager/ContextMenu.h"
#include "IniFiles.hpp"
#include "translate.h"

class translator : public QObject
{
	Q_OBJECT
public:
	explicit translator(QObject *parent = 0);
	virtual ~translator();

	virtual void Loop();
	virtual bool Event(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	IniFile *ini;
	std::string reloadMsg;
	//cmd
	translate	  *aPagesize1020Li;
	translate	  *aValidFontsize3;
	translate	  *aAudioMessage_0;
	translate	  *aAudioMessagesO;
	translate	  *aMemoryU;
	translate	  *aFrameLimiterVa;
	translate	  *aFrameLimiterU;
	translate	  *aHeadMovementsE;
	translate	  *aHeadMovementsD;
	translate	  *aUsagePlayer_sk;
	translate	  *aUsageVVehicleI;
	translate	  *aUsageSet_weath;
	translate	  *aInvalidTime_Us;
	translate	  *aUsageSet_timeH;
	translate	  *aIDonTKnowThatC;
	translate	  *aOnfootPosition;
	translate	  *aAddplayerclass;
	translate	  *aIncarPositionS;
	translate	  *aAddstaticvehic;
	translate	  *aICanTOpenTheSa;
	translate	  *aOnfootPosSaved;
	translate	  *aICanTOpenTheRa;
	translate	  *aIncarPosSaved;
	translate	  *aNoRegisteredCo;
	//scoreboard
	translate	  *aPing;
	translate	  *aScore;
	translate	  *aName;
	translate	  *aId;
	translate	  *aPlayersD;
	translate	  *aPlayers10000;
	//help_dialog
	translate	  *aSaMpKeys;
	translate	  *aBb9999F1Bbbbbb;
	translate	  *aOk;
	//dl
	translate	  *aIdDTypeDDistan;
	translate	  *aIdDTypeDSubtyp;
	//NetStat
	translate	  *aClientNetworkS;
	translate	  *aProcessMemUkbW;
	translate	  *aStreamingMemUm;
	translate	  *aIncarSendRateU;
	translate	  *aOnfootSendRate;
	translate	  *aVehiclesUVehic;
	translate	  *aDownloadRate_2;
	//Screenshot
	translate	  *aUnableToSaveSc;
	translate	  *aScreenshotTake;
	//warning
	translate	  *aWarningSExcept;
	translate	  *aWarningOpcode0;
	translate	  *aWarningCould_0;
	translate	  *aWarningBadObje;
	translate	  *aWarningActorUW;
	translate	  *aWarningIgnorin;
	translate	  *aWarningVehicle;
	//rejected
	translate	  *aConnectionRe_0;
	translate	  *aConnectionReje;
	translate	  *aConnectionRe_1;
	translate	  *aConnectionRe_2;
	//connect
	translate	  *aConnectingToSD;
	translate	  *aFailedToInitia;
	translate	  *aYouAreBannedFr;
	translate	  *aServerHasAccep;
	translate	  *aTheServerIsFul;
	translate	  *aServerClosedTh;
	translate	  *aWrongServerPas;
	translate	  *aTheServerDidnT;
	translate	  *aTheServerIsRes;
	translate	  *aLostConnection;
	translate	  *aConnected_Join;
	translate	  *aConnectedToB9c;
	//chat
	translate	  *aFfffffSaMpB9c9;
	translate	  *aUseQuitToExitO;
	translate	  *aPleaseUseOnlyA;
	translate	  *aPleaseChooseAn;
	translate	  *aReturningToCla;
	//notif
	translate	  *aRCarJackedW;
	translate	  *aStayWithinTheR;
	//custom
	QList<translate*> custom;

	void translateAll();
	void restoreAll();

	void translateCommands();
	void restoreCommands();

	void translateScoreboard();
	void restoreScoreboard();

	void translateHelpDialog();
	void restoreHelpDialog();

	void translateDL();
	void restoreDL();

	void translateNetStat();
	void restoreNetStat();

	void translateScreenshot();
	void restoreScreenshot();

	void translateWarning();
	void restoreWarning();

	void translateRejected();
	void restoreRejected();

	void translateConnect();
	void restoreConnect();

	void translateChat();
	void restoreChat();

	void translateNotif();
	void restoreNotif();

	void translateCustom();
	void restoreCustom();

signals:

public slots:
};

#endif // translator_H
