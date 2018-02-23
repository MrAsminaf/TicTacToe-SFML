#pragma once

#include <SFML\Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button(int width = 60, int height = 30, std::string name = "Button");
	void Logic(const sf::RenderWindow& window);
	void SetPosition(float x, float y);
	void SetFillColor(sf::Color);
	void SetSize(float width, float height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;

private:
	sf::RectangleShape m_buttonShape;
	sf::Text m_caption;
	sf::Font m_font;
};