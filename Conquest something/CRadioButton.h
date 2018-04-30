#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "CButton.h"

namespace gui
{
class CRadioButton
{
public:
	CRadioButton(const char *highlightWay);
	void addNewButton(const char *way, float posX, float posY, bool a_available);
	int checkClick(sf::Vector2f pos);
	void changeAvailable(unsigned item, bool a_available);
	void setCheckedButton(unsigned item);
	void drawButtons(sf::RenderWindow &a_window); 

private:
	std::vector<CButton*> m_buttons;
	int m_currentItem;
	sf::Texture m_tex_highlight;
	sf::Sprite m_spr_highlight;
};
};