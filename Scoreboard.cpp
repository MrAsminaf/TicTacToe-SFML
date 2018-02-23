#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	m_container.setPosition(647.5f, 280.f);
	m_container.setSize(sf::Vector2f(150, 160));
	m_container.setFillColor(sf::Color(30, 30, 30, 255));

	m_font.loadFromFile("res/ABeeZee-Regular.ttf");
	m_scoreBrdText.setFont(m_font);
	m_oScoreText.setFont(m_font);
	m_xScoreText.setFont(m_font);

	m_scoreBrdText.setPosition(m_container.getPosition().x + 10, m_container.getPosition().y + 10);
	m_scoreBrdText.setString("SCOREBOARD");
	m_scoreBrdText.setCharacterSize(20);

	m_oScoreText.setPosition(m_container.getPosition().x + 15, m_container.getPosition().y + 80);
	m_oScoreText.setString("Player O: 0");
	m_oScoreText.setCharacterSize(18);

	m_xScoreText.setPosition(m_container.getPosition().x + 15, m_container.getPosition().y + 120);
	m_xScoreText.setString("Player X: 0");
	m_xScoreText.setCharacterSize(18);
}

void Scoreboard::ChangeScore(PlayerScore playerScore, int value)
{
	if (playerScore == PlayerScore::O_SCORE_ENUM)
	{
		m_oScore += value;
		m_oScoreText.setString("Player O: " + std::to_string(m_oScore));
	}
	else if (playerScore == PlayerScore::X_SCORE_ENUM)
	{
		m_xScore += value;
		m_xScoreText.setString("Player X: " + std::to_string(m_xScore));
	}
}

void Scoreboard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_container, states);
	target.draw(m_scoreBrdText, states);
	target.draw(m_oScoreText, states);
	target.draw(m_xScoreText, states);
}
