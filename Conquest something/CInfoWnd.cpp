#include <iostream>
#include "CInfoWnd.h"

namespace gui
{
CInfoWnd::CInfoWnd(const char *infoWndWay, float iPosX, float iPosY, 
			const char *actionBtnWay, float aPosX, float aPosY, 
			const char *closeBtnWay, float cPosX, float cPosY):
	m_action(actionBtnWay, iPosX + aPosX, iPosY + aPosY, false),
	m_close(closeBtnWay, iPosX + cPosX, iPosY + cPosY, false), 
	m_drawInfoWnd(false)
{
	m_tex_infoWnd.loadFromFile(infoWndWay);
	m_spr_infoWnd.setTexture(m_tex_infoWnd);
	m_spr_infoWnd.setPosition(iPosX, iPosY);
}


void CInfoWnd::setAdditionZone(float posX, float posY, sf::Vector2f size)
{
	m_additionalZone.setPosition(m_spr_infoWnd.getPosition().x + posX, 
									m_spr_infoWnd.getPosition().y + posY);
	m_additionalZone.setSize(size);
}

void CInfoWnd::addNewText(std::string text, float posX, float posY, 
	sf::Font &a_font, unsigned charSize)
{
	sf::Text buffText(sf::Text(text, a_font, charSize));
	buffText.setPosition(m_spr_infoWnd.getPosition().x + posX, 
							m_spr_infoWnd.getPosition().y + posY);
	buffText.setFillColor(sf::Color::Black);
	m_textList.push_back(buffText);
}

void CInfoWnd::changeText(std::string text, unsigned item)
{
	if (item < m_textList.size())
		m_textList[item].setString(text);
}

int CInfoWnd::checkClick(sf::Vector2f pos)
{
	if (m_action.isClick(pos))
		return 0;
	else if (m_close.isClick(pos)) 
		return 1;
	else 
		return -1;
}

void CInfoWnd::changeAvailable(bool a_available, int item) // -1-window, 0-action, 1-close
{
	if (-1 == item)
	{
		m_drawInfoWnd = a_available;
		m_action.setAvailableMode(a_available);
		m_close.setAvailableMode(a_available);
	}
	else if (0 == item)
		m_action.setAvailableMode(a_available);
	else if (1 == item)
		m_close.setAvailableMode(a_available);
	else
		std::cout << "Wrong command\n";
}

void CInfoWnd::drawWnd(sf::RenderWindow &a_window) 
{
	if (m_drawInfoWnd)
	{
		a_window.draw(m_spr_infoWnd);
		a_window.draw(*m_action.getSprite());
		a_window.draw(*m_close.getSprite());
		for (auto iter = m_textList.begin(); iter != m_textList.end(); iter++)
			a_window.draw(*iter);

		if (m_drawAdditionalZone)
			a_window.draw(m_additionalZone);
	}
}
};