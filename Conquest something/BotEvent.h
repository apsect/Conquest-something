#pragma once

#include "Country.h"
#include "Map.h"

class CBotEvent
{
public:
	CBotEvent():
	  m_target(nullptr), m_targetCountry(nullptr), m_lastRollTime(0.f), m_canExpand(true) {}

	CBotEvent(CPlayer *a_target, CCountry *a_targetCountry, float a_lastRollTime): 
		m_target(a_target), m_targetCountry(a_targetCountry), m_lastRollTime(a_lastRollTime) 
	{
		cout << "Time created: " << m_lastRollTime << endl;
	}

	int getTargetPower() const				{return m_target->getPower();}
	int getTargetId() const					{return m_target->getPlayerId();}
	int getCountryExtension() const			{return m_targetCountry->getExtension();}
	std::string getCountryName()			{return m_targetCountry->getCountryName();}
	Color getCountryColor()	const			{return m_targetCountry->getCountryColor();}
	bool canExpand() const					{return m_canExpand;}
	void setExpandAbility(bool a_canExpand)	{m_canExpand = a_canExpand;}
	void decrementPower()					{m_target->decrementPower();}
	void declareWar(Color a_enemyColor)		{m_targetCountry->declareWar(a_enemyColor);}

	bool executeRoll(float currentTime)
	{
		//cout << "Execute roll: Player - " << m_target->getPlayerId() << "\tCurrTime - " << currentTime << "\tLastRollTime - " << m_lastRollTime << endl;
		if (currentTime > (m_lastRollTime + 5.f))
		{
			m_target->roll();
			m_lastRollTime = currentTime;
			return true;
		}
		return false;
	}

	Color findWay2Expand(CMap &a_currentMap)	
	{
		return a_currentMap.findWay2Expand(m_targetCountry->getCountryColor());
	}

	int findAvailableLand(CMap &a_currentMap)	
	{
		return m_targetCountry->findAvailableLand(a_currentMap);
	}

	void executeAddProv(int whatProv, CMap &a_currentMap)
	{
		m_targetCountry->addProv(whatProv, a_currentMap);
	}

private:
	CPlayer *m_target;
	CCountry *m_targetCountry;
	float m_lastRollTime;
	bool m_canExpand;
};