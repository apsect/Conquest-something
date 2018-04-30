#include "CRadioButton.h"

namespace gui
{
CRadioButton::CRadioButton(const char *highlightWay)
{
	m_tex_highlight.loadFromFile(highlightWay);
	m_spr_highlight.setTexture(m_tex_highlight);
}

void CRadioButton::addNewButton(const char *way, float posX, float posY, bool a_available)
{
	m_buttons.push_back(new CButton(way, posX, posY, a_available));
}

int CRadioButton::checkClick(sf::Vector2f pos)
{
	for (unsigned i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isClick(pos))
		{
			m_spr_highlight.setPosition(m_buttons[i]->getSprite()->getPosition());
			return m_currentItem = i;
		}
	return -1;
}

void CRadioButton::changeAvailable(unsigned item, bool a_available)
{
	if (item < m_buttons.size())
		m_buttons[item]->setAvailableMode(a_available);
}

void CRadioButton::setCheckedButton(unsigned item)
{
	if (item < m_buttons.size())
	{
		m_currentItem = item;
		m_spr_highlight.setPosition(m_buttons[item]->getSprite()->getPosition());
	}
}

void CRadioButton::drawButtons(sf::RenderWindow &a_window) 
{
	for (auto iter = m_buttons.begin(); iter != m_buttons.end(); iter++)
		a_window.draw(*(*iter)->getSprite());
	a_window.draw(m_spr_highlight);
}
};