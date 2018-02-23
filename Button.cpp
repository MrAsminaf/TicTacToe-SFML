#include "Button.h"

Button::Button(int width, int height, std::string name)
{
	m_buttonShape.setSize(sf::Vector2f(width, height));
	m_buttonShape.setFillColor(sf::Color(66, 66, 66, 255));

	m_font.loadFromFile("res/ABeeZee-Regular.ttf");

	m_caption.setString(name);
	m_caption.setFont(m_font);
	m_caption.setCharacterSize(16);
}

void Button::SetPosition(float x, float y)
{
	m_buttonShape.setPosition(x, y);
	m_caption.setPosition(x + 50, y + 10);
}

void Button::SetFillColor(sf::Color color)
{
	m_buttonShape.setFillColor(color);
}

void Button::SetSize(float width, float height)
{
	m_buttonShape.setSize(sf::Vector2f(width, height));
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_buttonShape, states);
	target.draw(m_caption, states);
}

sf::Vector2f Button::GetSize() const
{
	return m_buttonShape.getSize();
}

sf::Vector2f Button::GetPosition() const
{
	return m_buttonShape.getPosition();
}

void Button::Logic(const sf::RenderWindow & window)
{
	// highlight button
	if (sf::Mouse::getPosition(window).x >= m_buttonShape.getPosition().x
		&& sf::Mouse::getPosition(window).x <= m_buttonShape.getSize().x + m_buttonShape.getPosition().x
		&& sf::Mouse::getPosition(window).y >= m_buttonShape.getPosition().y
		&& sf::Mouse::getPosition(window).y <= m_buttonShape.getSize().y + m_buttonShape.getPosition().y)
		m_buttonShape.setFillColor(sf::Color(90, 90, 90, 255));
	else
		m_buttonShape.setFillColor(sf::Color(60, 60, 60, 255));
}