#pragma once

#include "Player.h"
#include <list>
#include <map>
#include <cmath>

class CCountry
{
public:
	CCountry(std::string a_countryName, 
		int a_capitalId, Color a_color, CMap &a_currentMap, CPlayer *king);

	void loseProv()									{--m_territory;}
	static void setSizeMap(int value)				{m_s_sizeMap = value;}
	std::string getCountryName()					{return m_countryName;}
	Color getCountryColor() const					{return m_countryColor;}
	int getExtension()	const						{return m_territory;}//return std::sqrt(static_cast<double>(m_territory + 1)) * (m_commanders.size() + 1);
	void addProv(int whatProv, CMap &a_currentMap);
	int checkVictory(CMap &a_currentMap) const;
	void showStats(std::map<Color, CCountry*, colorComparator> &a_countries) const;

	void drawDiplamacy(sf::RenderWindow &a_window, CMap &a_currentMap)	
	{
		a_currentMap.drawPlayersDiplomacy(a_window, m_enemies, m_countryColor);
	}

	void declareWar(Color a_enemyColor)		
	{
		m_enemies.insert(a_enemyColor);
		cout << m_countryName;
	}

	void addPlayer(CPlayer *a_player)	
	{
		m_commanders.push_back(a_player); 
		cout << "Player " << a_player->getPlayerId() 
			 << " join to country(" << m_countryName << ").\n";
	}

	int findAvailableLand(CMap &a_currentMap)	
	{
		return a_currentMap.findAvailableLand(m_countryColor, m_enemies);
	}

	std::string getGenerals() const
	{
		std::string buffString;
		for (auto iter = m_commanders.begin(); iter != m_commanders.end(); iter++)
			(buffString += std::to_string((long long)(*iter)->getPlayerId())) += " ";
		
		return buffString;
	}

	std::string getEnemies(std::map<Color, CCountry*, colorComparator> &a_countries) const
	{
		std::string buffString;
		if (m_enemies.size() > 1)
			for (auto iter = std::next(m_enemies.begin()); iter != m_enemies.end(); iter++)
				(buffString += a_countries[*iter]->getCountryName()) += ' ';
		else
			buffString += "-";
		return buffString;
	}

private:
	/*struct colorComparator
	{
		bool operator () (Color const &a, Color const &b) const 
		{
			return (int(a.r) + int(a.g) + int(a.b) + int(a.a))
				 < (int(b.r) + int(b.g) + int(b.b) + int(b.a));
		}
	};*/

private:
	std::list<CPlayer*> m_commanders;
	std::set<Color, colorComparator> m_allies;
	std::set<Color, colorComparator> m_enemies;
	int m_territory;

	std::string m_countryName;
	static int m_s_sizeMap;
	Color m_countryColor;
};