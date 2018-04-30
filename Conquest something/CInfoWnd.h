#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "CButton.h"

namespace gui
{
class CInfoWnd
{
public:
	CInfoWnd(const char *infoWndWay, float iPosX, float iPosY, 
			 const char *actionBtnWay, float aPosX, float aPosY,
			 const char *closeBtnWay, float cPosX, float cPosY);

	bool getAvailableStatus()					{return m_drawInfoWnd;}
	///
	void setAdditionZoneColor(sf::Color color)	{m_additionalZone.setFillColor(color);}
	void changeAvailableAdZone(bool a_available){m_drawAdditionalZone = a_available;}
	void setAdditionZone(float posX, float posY, sf::Vector2f size);
	///
	void addNewText(std::string text, float posX, float posY, 
		sf::Font &a_font, unsigned charSize = 12u);
	void changeText(std::string text, unsigned item);
	int checkClick(sf::Vector2f pos);
	void changeAvailable(bool a_available, int item = -1);
	void drawWnd(sf::RenderWindow &a_window);

private:
	sf::Texture m_tex_infoWnd;
	sf::Sprite m_spr_infoWnd;
	std::vector<sf::Text> m_textList;
	CButton m_action;
	CButton m_close;
	bool m_drawInfoWnd;
	bool m_drawAdditionalZone;
	sf::RectangleShape m_additionalZone;
};
};