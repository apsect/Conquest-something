#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using sf::Color;

struct colorComparator
{
	bool operator () (Color const &a, Color const &b) const 
	{
		return (int(a.r) + int(a.g) + int(a.b) + int(a.a))
				< (int(b.r) + int(b.g) + int(b.b) + int(b.a));
	}
};

class CProv
{
public:
	CProv(int a_provId) : 
			m_provId(a_provId), m_ownerColor(Color(0, 0, 0, 0)) {}
	void addEdge(int a_to, std::vector<CProv> &a_map)	{m_neighbor.push_back(&a_map[a_to]);}
	void setOwnerColor(Color a_playerColor)				{m_ownerColor = a_playerColor;}
	void setColor(Color a_provColor)					{m_provColor = a_provColor;}
	void setSprite(sf::Image &a_img_spriteProv);
	void setBoundRect(unsigned a_br_topX, 
					  unsigned a_br_topY, 
					  unsigned a_br_width, 
					  unsigned a_br_height);
	Color getOwnerColor() const							{return m_ownerColor;}
	Color getColor() const								{return m_provColor;}
	int getId() const									{return m_provId;}
	unsigned getTopX() const							{return m_br_topX;}
	unsigned getTopY() const							{return m_br_topY;}
	unsigned getWidth() const							{return m_br_width;}
	unsigned getHeight() const							{return m_br_height;}
	sf::Sprite getSprite() const						{return m_spr_spriteProv;}
	int isNear(Color a_playerColor);
	//void checkAllNear();

private:

	std::vector<CProv*> m_neighbor;

	sf::Texture m_tex_spriteProv;
	sf::Sprite m_spr_spriteProv;
	int m_provId;
	Color m_ownerColor;
	Color m_provColor;
	unsigned m_br_topX, m_br_topY, m_br_width, m_br_height;
};

class CMap
{
public:
	explicit CMap(int a_countProv, ...);
	Color getColorFromProvMap(unsigned x, unsigned y)	{return m_img_province.getPixel(x, y);}
	int getSizeMap()									{return m_provinces.size();}
	sf::Vector2i getAspectMap()							{return m_aspectMap;}

	Color getProvOwnerColor(int a_provId)					
	{
		return m_provinces[a_provId].getOwnerColor();
	}

	int isPlayerNear(int a_provId, Color a_playerColor)	
	{
		return m_provinces[a_provId].isNear(a_playerColor);
	}

	sf::Vector2f getDataToCentralizeView(int a_provId);
	int getRandomFreeProv();
	int getProvIdFromColor(Color a_color);
	Color findWay2Expand(Color a_playerColor);
	void addProvToCountry(int a_provId, Color a_playerColor);
	int findAvailableLand(Color a_playerColor, std::set<Color, colorComparator> &a_enemyColor);

	void drawPlayersColor(sf::RenderWindow &a_window);
	void drawProvNearPlayer(sf::RenderWindow &a_window, Color a_ownerColor);
	void drawPlayersDiplomacy(sf::RenderWindow &a_window, 
		std::set<Color, colorComparator> &a_enemies, Color a_ownerColor);
	
private:
	struct SPairProv2Near
	{
		mutable std::vector<int> m_prov;
		int m_countNear;

		SPairProv2Near(int a_countNear) : m_countNear(a_countNear) {}
		SPairProv2Near(int a_countNear, int a_prov) : m_countNear(a_countNear) 
			{m_prov.push_back(a_prov);}

		bool operator < (const SPairProv2Near &other) const 
			{return (m_countNear < other.m_countNear);}
	};

private:
	sf::Image m_img_province;
	std::vector<CProv> m_provinces;
	sf::Vector2i m_aspectMap;
};