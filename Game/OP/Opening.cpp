#include <windows.h>
#include ".\opening.h"
#include <time.h>
#include "../../gameLib/PMDPlayer/PMDPlayer.h"
#include "../Game.h"
#include "../../gameLib/CommonFunction/CommonFunctionMusicSE.h"
#ifdef _TRIAL
#include "../../gameLib/Graphic/PC98Font.h"
#endif

namespace th5w {

	COpening::COpening(void)
	{
		m_curFrame = 0;
		m_pBGImage = NULL;
	}

	COpening::~COpening(void)
	{
		if (m_pBGImage)
			m_pBGImage->Destroy();
		m_pBGImage = NULL;
	}

	void COpening::Initialize()
	{
		m_curFrame = -1;

		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, m_globalPalette, &CGame::s_pCurGame->m_th5Dat1, "ZUN00.PI");

		CCommonFunctionMusicSE::LoadMusicToPMDFromDat(&CGame::s_pCurGame->m_th5Dat1, "LOGO.M");//M2 Music Dose not exist
		th5w::CPMDPlayer::Play();

		m_particle.Initialize();

		m_curScrFade = 0;

		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN02.BFT", 0);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN04.BFT", 0);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN01.BFT", 0);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN03.BFT", 0);

		m_bKeyPressed = false;

		//this is a hacked fps, just to make the speed of the opening as close to that of PC98 ver as possible
		//CGame::s_pCurGame->m_fpsLimit=26;
		//twice faster than original
		//THis makes more smoothly.
		//I think
		CGame::s_pCurGame->m_fpsLimit = 26 * 2;
	}

	int COpening::Step()
	{
		m_curFrame++;

		if (m_curFrame >= 170 * 2)
		{
			m_curScrFade -= 6 / 2;
			if (m_curScrFade <= 0)
			{
				th5w::CPMDPlayer::Pause();
				return 1;
			}
			else
				return 0;
		}
		if (m_curFrame > 50 * 2) //50 IS TOO LONG...
		{
			CGame::s_pCurGame->m_input.UpdateKeyState();
			if (CGame::s_pCurGame->m_input.GetKeyState(DIK_Z) | CGame::s_pCurGame->m_input.GetKeyState(DIK_X))
				m_bKeyPressed = true;
		}

		switch (m_curFrame)
		{
		case 0:
			m_particle.AddParticles(0, 20, 180, 180);
			break;
		case 16 * 2:
			m_particle.AddParticles(10, 20, 460, 220);
			break;
		case 24 * 2:
			m_particle.AddParticles(0, 20, 220, 160);
			break;
		case 32 * 2:
			m_particle.AddParticles(10, 20, 380, 240);
			break;
		case 40 * 2:
			m_particle.AddParticles(0, 20, 220, 190);
			break;
		case 44 * 2:
			m_particle.AddParticles(10, 20, 340, 200);
			break;
		case 48 * 2:
			m_particle.AddParticles(0, 20, 280, 170);
			break;
		case 52 * 2:
			m_particle.AddParticles(10, 20, 380, 260);
			break;
		case 56 * 2:
			m_particle.AddParticles(0, 20, 220, 190);
			break;
		case 60 * 2:
			m_particle.AddParticles(10, 20, 440, 210);
			break;
		case 64 * 2:
			m_particle.AddParticles(0, 64, 320, 200);
			break;
		case 68 * 2:
			m_particle.AddParticles(10, 64, 320, 200);
			break;
		default:
			break;
		}

		m_playSound15 = false;
		m_particle.Step(&m_playSound15);
		if (m_playSound15)
			CCommonFunctionMusicSE::PlaySe(15);

		if (m_bKeyPressed)
		{
			if (m_curScrFade > 0)
				m_curScrFade -= (2 / 2);
			else
			{
				th5w::CPMDPlayer::Pause();
				return 1;
			}
		}
		else
		{
			if (m_curFrame >= 16 * 2)
				if (m_curScrFade < 100)
					m_curScrFade += (2 / 2);
		}

		return 0;
	}

	void COpening::Draw()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_pBGImage->Draw(0, 40);
		if (!m_bKeyPressed)
			CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
		m_particle.Draw(&m_patternArray);
		if (m_bKeyPressed)
			CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
	}

}
