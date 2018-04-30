#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace gui
{
class CButton
{
public:
	CButton(const char *way, float posX, float posY, bool a_available);
	bool isClick(sf::Vector2f pos) const;
	void setAvailableMode(bool a_available);
	bool getAvailableMode() const				{return m_available;}
	const sf::Sprite* getSprite() const			{return &m_sprite;}
	void setVisibleMode(bool a_visible)			{m_visible = a_visible;}

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_available;
	bool m_visible;
};
};