#include "RelationshipManager.h"
#include "Misc.h"

int CCountry::m_s_sizeMap(0);

CRelationshipManager::CRelationshipManager():
	m_newPlayerId(0),
	m_newCountryId(0),
	m_selectedCountry(nullptr),
	m_drawType(ownerColor),
	m_infoWnd("assets/GuiInfo.png", 346.f, 53.f,
			  "assets/btnGuiInfo.png", 66.f, 185.f,
			  "assets/btnGuiInfo.png", 191.f, 185.f),
	m_mapModeView("assets/highlight.png"),
	m_currentMap(62,
	3, 9, 61, 4,					41, 112, 155,	50, 1056, 455, 178, //0
	1, 2, 							167, 14, 19,	57, 62, 272, 327,
	2, 1, 3,						238, 28, 36,	213, 220, 172, 165,
	2, 2, 12,						139, 3, 4,		199, 315, 233, 137,
	4, 0, 18, 60, 61,				148, 190, 230,	478, 1027, 242, 169,
	3, 6, 7, 8,						46, 5, 87,		82, 739, 164, 132,
	3, 5, 8, 9,						46, 12, 65,		58, 856, 152, 164,
	4, 5, 8, 10, 11,				82, 46, 145,	213, 745, 249, 186,
	5, 5, 6, 7, 9, 19,				59, 2, 86,		195, 849, 166, 204,
	3, 0, 6, 8,						79, 18, 104,	121, 943, 155, 122,

	3, 7, 11, 12,					0, 89, 150,		306, 565, 183, 215, //10
	5, 7, 10, 12, 14, 15,			0, 89, 129,		391, 625, 187, 175,
	5, 3, 10, 11, 13, 14,			0, 124, 178,	224, 446, 317, 208,
	3, 12, 14, 32,					0, 138, 170,	421, 361, 194, 156,
	6, 11, 12, 13, 15, 32, 33,		0, 103, 109,	534, 443, 135, 208,
	5, 11, 14, 16, 17, 19,			79, 75, 114,	542, 605, 177, 128,
	4, 15, 17, 20, 33,				134, 131, 163,	687, 602, 156, 167,
	3, 15, 16, 18,					91, 87, 166,	664, 689, 153, 179,
	4, 4, 17, 19, 21,				135, 129, 189,	697, 808, 205, 256,
	3, 8, 15, 18,					187, 184, 220,	389, 773, 254, 228,

	5, 16, 21, 22, 33, 36,			0, 76, 122,		825, 595, 167, 186, //20
	5, 18, 20, 22, 23, 24,			35, 33, 118,	939, 767, 209, 242,
	4, 20, 21, 23, 36,				23, 71, 158,	957, 684, 162, 120,
	4, 21, 22, 25, 27,				0, 61, 123,		1089, 655, 184, 214,
	4, 21, 25, 26, 29,				140, 0, 81,		1067, 995, 363, 76,
	4, 23, 24, 26, 27,				96, 0, 51,		1158, 839, 175, 148,
	5, 24, 25, 27, 28, 29,			209, 31, 92,	1254, 893, 237, 112,
	4, 23, 25, 26, 28,				240, 103, 167,	1254, 781, 225, 123,
	6, 26, 27, 29, 45, 46, 49,		237, 15, 105,	1388, 809, 230, 147,
	6, 24, 26, 28, 49, 54, 56,		143, 86, 69,	1439, 948, 161, 186,

	3, 31, 32, 35,					49, 132, 50,	502, 225, 221, 179, //30
	1, 30,							0, 166, 81,		623, 38, 335, 201,
	6, 13, 14, 30, 33, 34, 35,		14, 108, 40,	598, 333, 290, 228,
	7, 14, 15, 16, 20, 32, 34, 36,	31, 79, 34,		641, 498, 246, 129,
	7, 32, 33, 35, 36, 37, 38, 39,	140, 155, 28,	752, 328, 323, 228,
	4, 30, 32, 34, 39,				99, 123, 25,	705, 225, 299, 124,
	5, 20, 22, 33, 34, 37,			0, 96, 175,		859, 526, 189, 188,
	4, 34, 36, 38, 40,				240, 78, 62,	977, 522, 319, 193,
	5, 34, 37, 39, 40, 41,			240, 78, 35,	1012, 322, 396, 216,
	4, 34, 35, 38, 41,				246, 130, 32,	974, 80, 382, 302,

	4, 37, 38, 41, 43,				246, 141, 88,	1241, 395, 461, 295, //40
	5, 38, 39, 40, 42, 43,			251, 166, 26,	1307, 179, 569, 340,
	3, 41, 43, 44,					204, 190, 0,	1729, 214, 430, 437,
	4, 40, 41, 42, 45,				150, 141, 0,	1486, 513, 354, 235,
	2, 42, 47,						255, 243, 62,	1882, 634, 347, 341,
	3, 28, 43, 46,					99, 100, 103,	1614, 723, 287, 139,
	4, 28, 45, 48, 49,				138, 140, 143,	1568, 810, 304, 159,
	4, 44, 48, 50, 52,				255, 246, 121,	1982, 911, 252, 191,
	5, 46, 47, 49, 52, 53,			137, 129, 127,	1702, 919, 292, 177,
	6, 28, 29, 46, 48, 53, 54,		82, 74, 72,		1523, 909, 206, 177,

	3, 47, 51, 52,					150, 142, 35,	1983, 1083, 230, 238, //50
	2, 50, 52,						172, 138, 28,	1873, 1148, 219, 161,
	5, 47, 48, 50, 51, 53,			249, 229, 0,	1823, 1035, 294, 172,
	4, 48, 49, 52, 54,				149, 146, 109,	1666, 1006, 204, 251,
	5, 29, 49, 53, 55, 56,			195, 146, 105,	1448, 1045, 410, 416,
	1, 54,							109, 87, 66,	1604, 1321, 421, 290,
	3, 29, 54, 57,					217, 178, 135,	1361, 1113, 172, 188,
	3, 56, 58, 59,					207, 18, 140,	1169, 1192, 281, 235,
	1, 57, 							172, 33, 142,	1289, 1394, 372, 301,
	3, 57, 60, 61,					237, 0, 140,	918, 1169, 297, 168,

	3, 4, 59, 61,					60, 105, 138,	626, 1149, 315, 123, //60
	4, 0, 4, 59, 60,				118, 152, 183,	332, 1115, 597, 223)
{
	m_clock.restart();
	CCountry::setSizeMap(m_currentMap.getSizeMap());
	m_font.loadFromFile("assets/FRAMDCN.ttf");

	m_infoWnd.addNewText("(wasteland)", 37.f, 10.f, m_font, 18u);
	m_infoWnd.addNewText("-", 190.f, 66.f, m_font);
	m_infoWnd.addNewText("-", 190.f, 96.f, m_font);
	m_infoWnd.addNewText("-", 190.f, 126.f, m_font);
	m_infoWnd.addNewText("-", 190.f, 156.f, m_font);
	m_infoWnd.setAdditionZone(66.f, 41, sf::Vector2f(233.f, 8.f));

	m_mapModeView.addNewButton("assets/terra.png", 721.f, 488.f, true);
	m_mapModeView.addNewButton("assets/countries.png", 797.f, 488.f, true);
	m_mapModeView.addNewButton("assets/diplomacy.png", 873.f, 488.f, false);
	m_mapModeView.addNewButton("assets/expansion.png", 949.f, 488.f, false);
	m_mapModeView.setCheckedButton(1);
}

void CRelationshipManager::updateAI()
{	
	if (!m_botEvent.empty())
		while (m_botEvent.front()->executeRoll(m_clock.getElapsedTime().asSeconds()))
		{
			if (!m_botEvent.front()->getCountryExtension())
			{
				cout << "Country " << m_botEvent.front()->getCountryName() << " defeat!\n";
				m_botEvent.pop();		//TODO: delete country, manage players
				continue;
			}
			if (m_botEvent.front()->getCountryExtension() == m_currentMap.getSizeMap())
			{
				cout << "Country " << m_botEvent.front()->getCountryName() << " won!\n";
				while (!m_botEvent.empty()) //TODO: delete all country, players| lock state
					m_botEvent.pop();
				return;
			}

			if (m_botEvent.front()->getTargetPower())
				releaseBotPower();

			if (m_botEvent.size() > 1)
			{
				m_botEvent.push(m_botEvent.front());
				m_botEvent.pop();
			}
		}
}

void CRelationshipManager::addBot() //TODO: make exception
{
	CBotEvent *botEvent(nullptr);
	CCountry *country(nullptr);
	CPlayer *player(new CPlayer(m_newPlayerId++));
	int pos(m_currentMap.getRandomFreeProv());
	
	if (((rand() % 10) || m_countries.empty()) && (pos > -1))
	{
		country = new CCountry(gw::generateRandomWord(), pos,
			Color(rand() % 256, rand() % 256, rand() % 256, 255), 
			m_currentMap, player);
		botEvent = new CBotEvent(player, country, m_clock.getElapsedTime().asSeconds());
	}
	else
	{
		int dest(rand() % m_countries.size()), i(0);
		for (auto iter = m_countries.begin(); iter != m_countries.end(); iter++, i++)
			if (i == dest)
			{
				iter->second->addPlayer(player);
				botEvent = new CBotEvent(player, iter->second, 
					m_clock.getElapsedTime().asSeconds());
				break;
			}
	}

	m_players.push_front(player);
	if (country != nullptr)
		m_countries.insert(std::make_pair(country->getCountryColor(), country));
	if (botEvent != nullptr)
		m_botEvent.push(botEvent);
}

void CRelationshipManager::releaseBotPower()
{
	while (m_botEvent.front()->getTargetPower())
	{
		if (m_botEvent.front()->canExpand())
		{
			int availableLand(m_botEvent.front()->findAvailableLand(m_currentMap));
			if (availableLand != -1)
			{
				Color conqueredProv(m_currentMap.getProvOwnerColor(availableLand));
				m_botEvent.front()->executeAddProv(availableLand, m_currentMap);
				if (conqueredProv != Color(0, 0, 0, 0))
					m_countries[conqueredProv]->loseProv();
				m_botEvent.front()->decrementPower();
			}
			else
				m_botEvent.front()->setExpandAbility(false);
		}
		else
		{
			Color enemyCountryColor(m_botEvent.front()->findWay2Expand(m_currentMap));
			if (enemyCountryColor == Color(0, 0, 0, 0))
				return;

			cout << "Country ";
			m_botEvent.front()->declareWar(enemyCountryColor);
			cout << " declare war to ";
			m_countries[enemyCountryColor]->declareWar(m_botEvent.front()->getCountryColor());
			cout << endl;
			m_botEvent.front()->setExpandAbility(true);
		}
	}
}

void CRelationshipManager::clickHuman(sf::Vector2f viewCenter, sf::Vector2i pixelPos, 
	sf::RenderWindow &a_window)
{
	int buffAnswer;
	if (m_infoWnd.getAvailableStatus() && 
		(buffAnswer = m_infoWnd.checkClick(sf::Vector2f(pixelPos))) > -1)
	{
		if  (0 == buffAnswer)
			;
		else if (1 == buffAnswer)
			m_infoWnd.changeAvailable(false);
	}
	else if ((buffAnswer =  m_mapModeView.checkClick(sf::Vector2f(pixelPos))) > -1)
		setDrawType(EDrawType(buffAnswer));
	else
	{
		sf::Vector2f pos(a_window.mapPixelToCoords(pixelPos));
		if (0 > pos.x) pos.x = 0;
		if (0 > pos.y) pos.y = 0;
		if (pos.x >= m_currentMap.getAspectMap().x) 
			pos.x = float(m_currentMap.getAspectMap().x - 1);
		if (pos.y >= m_currentMap.getAspectMap().y) 
			pos.y = float(m_currentMap.getAspectMap().y - 1);

		cout << pos.x << ' ' << pos.y << endl;
		int provId;
		if ((provId = m_currentMap.getProvIdFromColor(
			m_currentMap.getColorFromProvMap(unsigned(pos.x), unsigned(pos.y)))) != -1)
		{
			m_infoWnd.changeAvailable(true);
			Color owner(m_currentMap.getProvOwnerColor(provId));
			auto buffCountry(std::find_if(m_countries.begin(), m_countries.end(), 
				[&owner](std::pair<Color, CCountry*> l_pair)
			{
				return l_pair.second->getCountryColor() == owner;
			}));

			if (buffCountry != m_countries.end())
			{
				std::string buffString;
				buffCountry->second->showStats(m_countries);
				m_selectedCountry = buffCountry->second;
				m_infoWnd.changeText(m_selectedCountry->getCountryName(), 0);
				buffString += std::to_string((long long) m_selectedCountry->getExtension());
				m_infoWnd.changeText(buffString, 1);
				m_infoWnd.changeText(m_selectedCountry->getGenerals(), 2);
				m_infoWnd.changeText(m_selectedCountry->getEnemies(m_countries), 3);
				m_infoWnd.setAdditionZoneColor(m_selectedCountry->getCountryColor());
			}
			else
			{
				m_infoWnd.changeText("(wasteland)", 0);
				for (int i = 1; i < 4; i++)
					m_infoWnd.changeText("-", i);
				m_infoWnd.setAdditionZoneColor(Color(0, 0, 0, 0));
			}

			if (isSelectedCountry())
			{
				m_mapModeView.changeAvailable(2, true);
				m_mapModeView.changeAvailable(3, true);
			}
		}

	}
}