#pragma once

#include <SFML\Graphics.hpp>

class Scoreboard : public sf::Drawable, sf::Transformable
{
public:
	Scoreboard();
	enum PlayerScore { O_SCORE_ENUM, X_SCORE_ENUM };
	void ChangeScore(PlayerScore playerScore, int value);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	sf::RectangleShape m_container;
	sf::Font m_font;
	sf::Text m_scoreBrdText;
	sf::Text m_oScoreText;
	sf::Text m_xScoreText;
	sf::String test;

	int m_oScore;
	int m_xScore;
};