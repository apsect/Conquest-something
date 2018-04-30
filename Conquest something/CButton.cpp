#include "CButton.h"

namespace gui
{
CButton::CButton(const char *way, float posX, float posY, bool a_available = true): 
	m_available(a_available), m_visible(true)
{
	if (m_available)
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
	else
		m_sprite.setColor(sf::Color(160, 160, 160, 255));

	m_texture.loadFromFile(way);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(posX, posY);
}

bool CButton::isClick(sf::Vector2f pos) const
{
	if (m_available)
		return m_sprite.getGlobalBounds().contains(pos);
	return false;
}

void CButton::setAvailableMode(bool a_available) 
{
	m_available = a_available;
	if (m_available)
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
	else
		m_sprite.setColor(sf::Color(160, 160, 160, 255));
}
};