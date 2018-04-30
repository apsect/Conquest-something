#pragma once

#include "Map.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

using std::cout;
using std::endl;
using sf::Color;

const char *const iplList[] = {"double", "triple", "quadruple", "doubledouble"};

//class CPlayer;
//class CBot;
//class CHuman;

class CPlayer
{
public:
	CPlayer(int a_playerId): m_playerId(a_playerId), m_power(0) {cout << "Player " << a_playerId << " was join.\n";}
	
	int getPlayerId() const		{return m_playerId;}
	unsigned getPower()	const	{return m_power;}
	void decrementPower()		{m_power--;}
	//bool canRoll(float a_time) const		{return (m_lastRoll + 5.f + (rand() % 3) < a_time)? true : false;}, m_lastRoll(0.f)
	//void setLastRollTime(float a_lastRoll)	{m_lastRoll = a_lastRoll;}
	//void setNoPower()						{m_power = 0;}
	
	//void addProv(CMap &a_currentMap, Color a_countryColor);//, std::vector<CBot> &a_bots, CHuman *a_human);

	//void setData(int a_playerId, int a_capitalId, sf::Color a_color, CMap &m_currentMap);
	//void addProv(sf::Color a_whatProv, CMap &m_currentMap);

	bool roll();

private:
	const int m_playerId;
	unsigned m_power;
	//float m_lastRoll;

private:
	int genRandNum() const {return rand() % 10000;}
	int checkIpl(int value) const;
};

/*class CBot : public CPlayer
{
public:
	CBot(int a_playerId, int a_capitalId, Color a_color, CMap &a_currentMap) :
		CPlayer(a_playerId, a_capitalId, a_color, a_currentMap) {}
	
	void addProv(CMap &a_currentMap, std::vector<CBot> &a_bots, CHuman *a_human);
};

class CHuman : public CPlayer
{
public:
	CHuman(int a_playerId, int a_capitalId, Color a_color, CMap &a_currentMap) :
		CPlayer(a_playerId, a_capitalId, a_color, a_currentMap) {}
	
	void addProv(Color a_whatProv, CMap &a_currentMap, std::vector<CBot> &a_bots);
};*/

