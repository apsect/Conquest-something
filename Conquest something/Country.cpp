#include "Country.h"

CCountry::CCountry(std::string a_countryName, 
	int a_capitalId, Color a_color, CMap &a_currentMap, CPlayer *king): 
	m_countryColor(a_color), m_countryName(a_countryName), m_territory(1)
{
	m_commanders.push_back(king);
	a_currentMap.addProvToCountry(a_capitalId, m_countryColor);
	m_enemies.insert(Color(0, 0, 0, 0));
	cout << "Player " << king->getPlayerId() << " formed new country(" 
		 << a_countryName << ") in " << a_capitalId << endl;
}

void CCountry::addProv(int whatProv, CMap &a_currentMap)
{
	/*int whatProv;
	if ((whatProv = a_currentMap.getFreeNearProv(m_countryColor, m_enemies)) == -1)
	{
		m_canExpand = false;
		return Color(300, 300, 300, 300);
	}*/

	//Color conqeredProvColor(a_currentMap.getProvOwnerColor(whatProv));
	a_currentMap.addProvToCountry(whatProv, m_countryColor);
	cout << "Country " << m_countryName << " conquered " << whatProv << endl;
	cout << "Territory: " << ++m_territory << endl;
	//return conqeredProvColor;
}

int CCountry::checkVictory(CMap &a_currentMap) const
{
	int vStatus(0);
	for (int i = 0; i < m_s_sizeMap; i++)
		if (a_currentMap.getProvOwnerColor(i) == m_countryColor)
			vStatus++;

	return vStatus;
}

void  CCountry::showStats(std::map<Color, CCountry*, colorComparator> &a_countries) const
{
	cout << "Country: " << m_countryName << endl;
	cout << "Territory: " << m_territory << endl;
	cout << "Players: ";
	for (auto iter = m_commanders.begin(); iter != m_commanders.end(); iter++)
		cout << (*iter)->getPlayerId() << ' ';
	cout << endl;

	cout << "Enemies: ";
	if (m_enemies.size() > 1)
		for (auto iter = std::next(m_enemies.begin()); iter != m_enemies.end(); iter++)
			cout << a_countries[*iter]->getCountryName() << ' ';
	else
		cout << "no one";
	cout << endl << endl;
}