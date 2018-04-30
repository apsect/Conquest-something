#include "Player.h"

int CPlayer::checkIpl(int value) const
{
	if (!value)
		return 1;

	char num[32];
	_itoa_s(value, num, 10);
	int status(0);
	char base(num[strlen(num) - 1]);
	bool multipleStatus(false);

	for (int i = 1; i < int(strlen(num)); i++)
		if (base == num[strlen(num) - (i + 1)])
			status++;
		else if (status % 10)
		{
			base = num[strlen(num) - (i + 1)];
			status *= 10;
		}
		else
			break;

		*num = '\0';
		return status;
}

bool CPlayer::roll()
{
	int buff(genRandNum());
	cout << "Player " << m_playerId << " has a number: " << buff << endl;

	switch (checkIpl(buff))
	{
	case 11:
		cout << iplList[3] << endl;
		m_power += 2;
		return true;

	 case 1: case 10:
		cout << iplList[0] << endl;
		m_power += 1;
		return true;

	 case 2: case 20:
		cout << iplList[1] << endl;
		m_power += 2;
		return true;

	 case 3: case 30:
		cout << iplList[2] << endl;
		m_power += 3;
		return true;

	 default:
		 return false;
	}
}

/*void CHuman::addProv(Color a_whatProv, CMap &a_currentMap, std::vector<CBot> &a_bots)
{
	int prov(a_currentMap.getProvIdFromColor(a_whatProv));
	if ((a_currentMap.getProvOwnerColor(prov) != m_playerColor) &&
			a_currentMap.isPlayerNear(prov, m_playerColor) && m_power)
	{
		
		if (!inWar(a_currentMap.getProvOwnerColor(prov)))
		{
			auto foundBuff(std::find_if(a_bots.begin(), a_bots.end(), 
				[&](CBot &a)
				{
					return a.getPlayerColor() == a_currentMap.getProvOwnerColor(prov);
				}
				));
			if (foundBuff != a_bots.end())
			{
				declareWar(foundBuff->getPlayerColor());
				foundBuff->declareWar(getPlayerColor());
				cout << "Player " << m_playerId << " declare war to " << foundBuff->getPlayerId() << endl;
			}
			else
			{
				cout << "Here no such player!\n";
				return;
			}
		}
		a_currentMap.addProvToPlayer(prov, m_playerColor);
		cout << "Current power: " << --m_power << endl;
	}
	else
		cout << "This province is already your or too far away from your army.\n"
				"OR YOU HAVEN'T POWER HERE!\n"
				"Try to conquest other province.\n";
}*/

