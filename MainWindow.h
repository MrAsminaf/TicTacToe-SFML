#pragma once

// SFML headers
#include <SFML\Graphics.hpp>

// my headers
#include "Button.h"
#include "Scoreboard.h"

// other imports...
#include <vector>

class MainWindow
{
public:
	MainWindow();
	void RunGameLoop();

private:
	void PlayerInput();
	void Logic();
	void RoundEnd(float x_winningLine, float y_winningLine);
	void SetField(int);
	void ResetWinnerLine();

private:
	sf::RenderWindow m_mainWindow;

	sf::Sprite m_boardSprite;
	sf::Texture m_boardTexture;

	std::vector<sf::Sprite> m_xSprites;
	sf::Texture m_xTexture;

	std::vector<sf::Sprite> m_oSprites;
	sf::Texture m_oTexture;

	sf::Font m_font;
	sf::Text m_currentPlayerText;
	sf::Text m_endText;

	// the green line that shows up when one player beats the other one
	sf::RectangleShape m_winningLine;

	Button m_restartButton;
	Scoreboard m_scoreBrd;

	bool m_gameEnded = false;

	// ------------------- //

	enum CurrentPlayer {
		ENUM_O,
		ENUM_X,
	};
	CurrentPlayer m_currentPlayer = CurrentPlayer::ENUM_O;

	struct BoardFields
	{
		int coords[4];
		bool isValid = true;
		CurrentPlayer occupiedBy;
	};

	// coordinates for each field in order: x1, y1, x2, y2 
	BoardFields m_boardField[9]{
		{ 8, 8,   192, 192 }, { 208, 8,   392, 192 }, { 408, 8,   592, 192 },
		{ 8, 208, 192, 392 }, { 208, 208, 392, 392 }, { 408, 208, 592, 392 },
		{ 8, 408, 192, 592 }, { 208, 408, 392, 592 }, { 408, 408, 592, 592 }
	};
};