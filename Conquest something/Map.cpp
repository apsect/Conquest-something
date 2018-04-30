#include "Map.h"

#include <iostream>
#include <ctime>
#include <Windows.h>
#pragma comment( lib, "Winmm.lib" )
#include <assert.h>
#include <set>
#include <map>

void CProv::setSprite(sf::Image &a_img_spriteProv)
{
	m_tex_spriteProv.loadFromImage(a_img_spriteProv);
	m_spr_spriteProv.setTexture(m_tex_spriteProv);
	m_spr_spriteProv.setPosition(float(m_br_topX), float(m_br_topY));
}

void CProv::setBoundRect(unsigned a_br_topX, unsigned a_br_topY, 
				  unsigned a_br_width, unsigned a_br_height)
{
	m_br_topX = a_br_topX;
	m_br_topY = a_br_topY;
	m_br_width = a_br_width;
	m_br_height = a_br_height;
}

int CProv::isNear(Color a_playerColor)
{
	int provCount(0);
	for (auto iter = m_neighbor.begin(); iter != m_neighbor.end(); iter++)
		if ((*iter)->getOwnerColor() == a_playerColor)
			provCount++;
	return provCount;
}

CMap::CMap(int a_countProv, ...)
{
	m_img_province.loadFromFile("map/province.bmp");

	Color colorBuff;
	sf::Image spriteField;
	spriteField.create(m_img_province.getSize().x, m_img_province.getSize().y);
	unsigned sfh(m_img_province.getSize().y), sfw(m_img_province.getSize().x);
	m_aspectMap.x = sfw;
	m_aspectMap.y = sfh;
	for (unsigned i = 0; i < sfw; i++)
		for (unsigned j = 0; j < sfh; j++)
		{
			colorBuff = m_img_province.getPixel(i, j);
			colorBuff.a = sf::Uint8(255);
			spriteField.setPixel(i, j, colorBuff);
		}

	m_provinces.reserve(a_countProv);
	for (int i = 0; i < a_countProv; i++)
		m_provinces.push_back(CProv(i));

	unsigned br_topXBuff, br_topYBuff, br_widthBuff, br_heightBuff;
	int *ptrMain(&a_countProv + 1), countNeighbor;
	for (int i = 0; i < a_countProv; i++)
	{
		countNeighbor = *ptrMain++;
		for (int j = 0; j < countNeighbor; j++)
			m_provinces[i].addEdge(*ptrMain++, m_provinces);

		colorBuff.r = *ptrMain++;
		colorBuff.g = *ptrMain++;
		colorBuff.b = *ptrMain++;
		colorBuff.a = sf::Int8(0);
		m_provinces[i].setColor(colorBuff);

		br_topXBuff = *ptrMain++;
		br_topYBuff = *ptrMain++;
		br_widthBuff = *ptrMain++;
		br_heightBuff = *ptrMain++;
		m_provinces[i].setBoundRect(br_topXBuff, br_topYBuff, br_widthBuff, br_heightBuff);

		colorBuff.a = sf::Int8(255);
		sf::Image img_spriteProv;
		img_spriteProv.create(br_widthBuff, br_heightBuff);
		img_spriteProv.copy(spriteField, 0, 0, 
				sf::IntRect(br_topXBuff, br_topYBuff, br_widthBuff, br_heightBuff), false);
		unsigned h(img_spriteProv.getSize().y), w(img_spriteProv.getSize().x);
		for (unsigned k = 0; k < w; k++)
			for (unsigned j = 0; j < h; j++)
				if (img_spriteProv.getPixel(k, j) != colorBuff)
					img_spriteProv.setPixel(k, j, Color(255, 255, 255, 0));
				else 
					img_spriteProv.setPixel(k, j, Color(255, 255, 255, 255));

		m_provinces[i].setSprite(img_spriteProv);
	} 
}

sf::Vector2f CMap::getDataToCentralizeView(int a_provId)
{
	return sf::Vector2f( 
		(float) m_provinces[a_provId].getTopX() + (m_provinces[a_provId].getWidth() / 2.f),
		(float) m_provinces[a_provId].getTopY() + (m_provinces[a_provId].getHeight() / 2.f));
}

int CMap::getRandomFreeProv()
{
	srand(static_cast<unsigned int>(time(0)));
	int countFreeProv(0), targetProv, sizeMap(getSizeMap());
	for (int i = 0; i < sizeMap; i++)
		if (m_provinces[i].getOwnerColor() == Color(0, 0, 0, 0))
			countFreeProv++;

	if (countFreeProv)
	{
		while (m_provinces[targetProv = rand() % sizeMap].getOwnerColor() != Color(0, 0, 0, 0));
		return targetProv;
	}
	else
		return -1;
}

int CMap::getProvIdFromColor(Color a_color)
{
	for (auto iter = m_provinces.begin(); iter != m_provinces.end(); iter++)
		if (a_color == iter->getColor())
			return iter->getId();
	return -1;
}

int CMap::findAvailableLand(Color a_playerColor, std::set<Color, colorComparator> &a_enemyColor)
{
	size_t sizeMap(getSizeMap()), countNeighbor(0);
	std::set<SPairProv2Near> freeNearProvId;
	std::set<SPairProv2Near>::iterator iter;
	for (unsigned i = 0; i < sizeMap; i++)
		if ((std::find(a_enemyColor.begin(), a_enemyColor.end(), m_provinces[i].getOwnerColor()) 
				!= a_enemyColor.end()) && (countNeighbor = isPlayerNear(i, a_playerColor)))//isCurrentOwnerIsEnemy(m_provinces[i].getOwnerColor(), a_enemyColor) &&//m_provinces[i].getOwnerColor() == Color(0, 0, 0, 0) && 
			if ((iter = freeNearProvId.find(SPairProv2Near(countNeighbor))) != freeNearProvId.end())
				iter->m_prov.push_back(m_provinces[i].getId());
			else
				freeNearProvId.insert(SPairProv2Near(countNeighbor, m_provinces[i].getId()));

	if (freeNearProvId.empty())
		return -1;
	auto lastInSet(std::prev(freeNearProvId.end()));
	return lastInSet->m_prov[rand() % lastInSet->m_prov.size()];
}

Color CMap::findWay2Expand(Color a_playerColor)
{
	std::vector<Color> neighbors;
	for (int i = 0; i < getSizeMap(); i++)
		if (isPlayerNear(i, a_playerColor) && (m_provinces[i].getOwnerColor() != a_playerColor))
			neighbors.push_back(m_provinces[i].getOwnerColor());

	if (neighbors.empty())
	{
		cout << "Something wrong\n";
		return Color(0, 0, 0, 0);
	}
	return neighbors[rand() % neighbors.size()];

	/*bool incremented(false);
	std::vector<Color> owners;
	std::vector<int> countNeighbor;
	for (unsigned i = 0; i < sizeMap; i++, incremented = false)
		if (isPlayerNear(i, a_playerColor))
		{
			Color ownerColorBuff(m_provinces[i].getOwnerColor());
			if (ownerColorBuff == a_playerColor)
				continue;
			for (int j = 0; j < owners.size(); j++)
				if (owners[j] == ownerColorBuff)
				{
					countNeighbor[j]++;
					incremented = true;
					break;
				}
			if (!incremented)
			{
				owners.push_back(m_provinces[i].getOwnerColor());
				countNeighbor.push_back(1);
			}
		}

		if (countNeighbor.size() > 1)
		{
			int numBuff(0);
			for (int i = 1; i < countNeighbor.size(); i++)
				if(countNeighbor[numBuff] < countNeighbor[i])
					numBuff = i;

			assert(a_playerColor != owners[numBuff]);
			return owners[numBuff];
		}
		else if (!countNeighbor.empty())
		{
			assert(a_playerColor != owners[0]);
			return owners[0];
		}
		else
		{
			//assert(false);
			return Color(0, 0, 0, 0);
		}*/
				
}

void CMap::addProvToCountry(int a_provId, Color a_playerColor)		
{
	m_provinces[a_provId].setOwnerColor(a_playerColor); 
}

void CMap::drawPlayersColor(sf::RenderWindow &a_window)
{
	sf::Sprite buffSprite;
	Color buffColor;
	for (unsigned i = 0; i < m_provinces.size(); i++)
	{
		buffColor = m_provinces[i].getOwnerColor();
		if (buffColor != Color(0, 0, 0, 0))
		{
			buffColor.a = sf::Int8(175);
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(buffColor);
			a_window.draw(buffSprite);
		}
	}
}

void CMap::drawPlayersDiplomacy(sf::RenderWindow &a_window, 
	std::set<Color, colorComparator> &a_enemies, Color a_ownerColor)
{
	sf::Sprite buffSprite;
	Color buffColor;
	for (unsigned i = 0; i < m_provinces.size(); i++)
	{
		buffColor = m_provinces[i].getOwnerColor();
		if (buffColor == a_ownerColor)
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(0, 255, 0, 175));
			a_window.draw(buffSprite);
		}
		else if(a_enemies.find(buffColor) != a_enemies.end())
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(255, 0, 0, 175));
			a_window.draw(buffSprite);
		}
		else if (buffColor != Color(0, 0, 0, 0))
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(128, 128, 128, 175));
			a_window.draw(buffSprite);
		}
	}
}

void CMap::drawProvNearPlayer(sf::RenderWindow &a_window, Color a_ownerColor)
{
	sf::Sprite buffSprite;
	Color buffColor;
	for (unsigned i = 0; i < m_provinces.size(); i++)
	{
		buffColor = m_provinces[i].getOwnerColor();
		if (buffColor == a_ownerColor)
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(0, 255, 0, 175));
			a_window.draw(buffSprite);
		}
		else if(m_provinces[i].isNear(a_ownerColor))
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(0, 0, 255, 175));
			a_window.draw(buffSprite);
		}
		else if (buffColor != Color(0, 0, 0, 0))
		{
			buffSprite = m_provinces[i].getSprite();
			buffSprite.setColor(Color(128, 128, 128, 175));
			a_window.draw(buffSprite);
		}
	}
}