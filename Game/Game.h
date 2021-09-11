#pragma once
#include "../gamelib/Window/GameWindow.h"
#include "../gameLib/Input/KeyInputDI.h"
#include "../gamelib/th5DatFile/th5DatFile.h"
#include "../gamelib/PMDPlayer/PMDPlayer.h"
#include "../gamelib/MMDPlayer/MMDPlayer.h"
#include "../gameLib/se/SoundEffect.h"

#include "Scheme.h"
#include "SchemeSwitcher.h"

#include "GlobalVariableAndStatistics.h"

namespace th5w{

class CGame
{
public:
	static CGame *s_pCurGame;
	__forceinline static CGlobalVariableAndStatistics& GVar() {return s_pCurGame->m_globalVar;}

	int m_windowWidth,m_windowHeight;
	RECT m_playArea;

	CScheme *m_pCurScheme;

	int m_curSchemeID;

public:
	CGameWindow m_gameWindow;
	CKeyInputDI m_input;
	CSoundEffect m_soundEffect;
	CSoundEffect m_soundEffect2;

	Cth5DatFile m_th5Dat1;
	Cth5DatFile m_th5Dat2;
	Cth5DatFile m_musicDat;
	Cth5DatFile m_modDat;

	CGlobalVariableAndStatistics m_globalVar;

public:
	LARGE_INTEGER m_lastFrameTime;
	LARGE_INTEGER m_performanceFreq;
	LARGE_INTEGER m_lastDeactivateTime;
	float m_fpsLimit;
	float m_thisFrameDuration;
	float m_thisFrameLostTime;
	LARGE_INTEGER m_fpsTimeArray[20];
	int m_fpsTimeIdx;
	double m_fps;

protected:
	bool Initialize();
	bool fileCheck();
	void UpdateFPS();
	void LoadModConfig();
public:
	Cth5DatFile* FindResource(const char *fileName);
public:
	void Run();
	void SetVSYNC(bool bOn);

public:
	void OnDeactivate();
	void OnActivate();
	void OnGameEnd();
	void OnPaintInactivate();

public:
	CGame(void);
	~CGame(void);
};

}