#pragma once

#include "Country.h"
#include "BotEvent.h"
#include "CButton.h"
#include "CRadioButton.h"
#include "CInfoWnd.h"

#include <queue>
#include <assert.h>

enum EDrawType 
{
	noDraw,
	ownerColor,
	diplomacy,
	provNear
};

enum EPlayerMode
{
	observe,
	conv,
	conquest
};

class CRelationshipManager
{
public:
	CRelationshipManager();
	void drawPlayers(sf::RenderWindow &a_window)	
	{
		switch (m_drawType)
		{
		 case noDraw:
			return;

		 case ownerColor:
			m_currentMap.drawPlayersColor(a_window);
			return;

		 case diplomacy:
			m_selectedCountry->drawDiplamacy(a_window, m_currentMap);
			return;

		 case provNear:
			m_currentMap.drawProvNearPlayer(a_window, m_selectedCountry->getCountryColor());
			return;
		}
	}

	void drawInfoWnd(sf::RenderWindow &a_window)	{m_infoWnd.drawWnd(a_window);}
	void drawMapModeView(sf::RenderWindow &a_window){m_mapModeView.drawButtons(a_window);}

	void updateAI();
	void addBot();

	bool isSelectedCountry()						{return m_selectedCountry != nullptr;}
	void setDrawType(EDrawType a_drawType)			{m_drawType = a_drawType;}
	void clickHuman(sf::Vector2f viewCenter, sf::Vector2i pixelPos, sf::RenderWindow &a_window);

private:
	void releaseBotPower();
	
private:
	std::queue<CBotEvent*> m_botEvent;
	std::map<Color, CCountry*, colorComparator> m_countries;
	std::list<CPlayer*> m_players;
	
	CMap m_currentMap;
	int m_newPlayerId;
	int m_newCountryId;
	sf::Clock m_clock;

	EDrawType m_drawType;
	CCountry *m_selectedCountry;

	sf::Font m_font;
	gui::CInfoWnd m_infoWnd;
	gui::CRadioButton m_mapModeView;
};