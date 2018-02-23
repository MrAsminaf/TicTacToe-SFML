#include "MainWindow.h"

MainWindow::MainWindow()
	:
	m_mainWindow(sf::VideoMode(850, 600), "Tic Tac Toe", sf::Style::Close), // defining window mode, size, name and style
	m_restartButton(160,40, "Restart")
{
	m_mainWindow.setFramerateLimit(60);

	m_boardTexture.loadFromFile("res/board.png");
	m_boardSprite.setTexture(m_boardTexture);

	m_xTexture.loadFromFile("res/x.png");
	m_oTexture.loadFromFile("res/o.png");

	m_font.loadFromFile("res/ABeeZee-Regular.ttf");
	m_currentPlayerText.setFont(m_font);
	m_currentPlayerText.setString("Current Player: " + std::to_string(m_currentPlayer));
	m_currentPlayerText.setCharacterSize(25);
	m_currentPlayerText.setPosition(620.0f, 40.0f);

	m_endText.setCharacterSize(25);
	m_endText.setFont(m_font);
	m_endText.setPosition(615.0f, 200.0f);
	m_endText.setFillColor(sf::Color::Yellow);

	m_restartButton.SetPosition(640.f, 520.f);

	m_winningLine.setFillColor(sf::Color::Green);
	m_winningLine.setSize(sf::Vector2f(584, 5));
	m_winningLine.setPosition(0, -5000);
}

void MainWindow::RunGameLoop()
{
	while (m_mainWindow.isOpen())
	{
		sf::Event event;
		while (m_mainWindow.pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_mainWindow.close();

		if (!m_gameEnded)
		{
			PlayerInput();
			Logic();
		}

		m_restartButton.Logic(m_mainWindow);

		// if player clicks on restart button... 
		if (sf::Mouse::getPosition(m_mainWindow).x >= m_restartButton.GetPosition().x
			&& sf::Mouse::getPosition(m_mainWindow).x <= m_restartButton.GetSize().x + m_restartButton.GetPosition().x
			&& sf::Mouse::getPosition(m_mainWindow).y >= m_restartButton.GetPosition().y
			&& sf::Mouse::getPosition(m_mainWindow).y <= m_restartButton.GetSize().y + m_restartButton.GetPosition().y
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			// delete all displayed 'x's and 'o's
			while (m_oSprites.size() != 0)
				m_oSprites.pop_back();

			while (m_xSprites.size() != 0)
				m_xSprites.pop_back();

			// set each field back to default
			for (int i = 0; i < 9; ++i)
			{
				m_boardField[i].isValid = true;
			}

			m_gameEnded = false; 
			m_endText.setString("");
			m_winningLine.setPosition(0, -500);
		}

		m_mainWindow.clear( sf::Color( 40, 40, 40, 0) );
		m_mainWindow.draw(m_boardSprite);

		// displaying exery 'o' and 'x' sprite on field
		if (m_xSprites.size() > 0 )
			for(int i = 0; i < m_xSprites.size(); ++i)
			m_mainWindow.draw(m_xSprites[i]);

		if (m_oSprites.size() > 0)
			for (int i = 0; i < m_oSprites.size(); ++i)
				m_mainWindow.draw(m_oSprites[i]);

		m_mainWindow.draw(m_currentPlayerText);
		m_mainWindow.draw(m_endText);
		m_mainWindow.draw(m_restartButton);
		m_mainWindow.draw(m_scoreBrd);
		if (m_gameEnded)
			m_mainWindow.draw(m_winningLine);
		m_mainWindow.display();
	}
}

void MainWindow::PlayerInput()
{
	// if player clicks on any of the fields on the board
	for(int i = 0; i < 9; ++i)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
			sf::Mouse::getPosition(m_mainWindow).x > m_boardField[i].coords[0]
			&& sf::Mouse::getPosition(m_mainWindow).x < m_boardField[i].coords[2]
			&& sf::Mouse::getPosition(m_mainWindow).y > m_boardField[i].coords[1]
			&& sf::Mouse::getPosition(m_mainWindow).y < m_boardField[i].coords[3]
			&& m_boardField[i].isValid == true)
		{
			SetField(i);
		}
}

void MainWindow::Logic()
{
	// if statements for possible outcomes which may result in ending current round

	// top horizontal line
	if (m_boardField[0].isValid == false && m_boardField[1].isValid == false && m_boardField[2].isValid == false
		&& m_boardField[0].occupiedBy == m_boardField[1].occupiedBy && m_boardField[0].occupiedBy == m_boardField[2].occupiedBy)
	{
		RoundEnd(8.f, 96.f);
	}

	// middle horizontal
	else if (m_boardField[3].isValid == false && m_boardField[4].isValid == false && m_boardField[5].isValid == false
		&& m_boardField[3].occupiedBy == m_boardField[4].occupiedBy && m_boardField[3].occupiedBy == m_boardField[5].occupiedBy)
	{
		RoundEnd(8.f, 300.f);
	}

	// down horizontal
	else if (m_boardField[6].isValid == false && m_boardField[7].isValid == false && m_boardField[8].isValid == false
		&& m_boardField[6].occupiedBy == m_boardField[7].occupiedBy && m_boardField[6].occupiedBy == m_boardField[8].occupiedBy)
	{
		RoundEnd(8.f, 500.f);
	}

	// ------------------- //

	// left vertical
	else if (m_boardField[0].isValid == false && m_boardField[3].isValid == false && m_boardField[6].isValid == false
		&& m_boardField[0].occupiedBy == m_boardField[3].occupiedBy && m_boardField[0].occupiedBy == m_boardField[6].occupiedBy)
	{
		RoundEnd(100.f, 8.f);
		m_winningLine.rotate(90);
	}

	// middle vertical
	else if (m_boardField[1].isValid == false && m_boardField[4].isValid == false && m_boardField[7].isValid == false
		&& m_boardField[1].occupiedBy == m_boardField[4].occupiedBy && m_boardField[1].occupiedBy == m_boardField[7].occupiedBy)
	{
		RoundEnd(300.f, 8.f);
		m_winningLine.rotate(90);
	}

	// rigth vertical
	else if (m_boardField[2].isValid == false && m_boardField[5].isValid == false && m_boardField[8].isValid == false
		&& m_boardField[2].occupiedBy == m_boardField[5].occupiedBy && m_boardField[2].occupiedBy == m_boardField[8].occupiedBy)
	{	
		RoundEnd(500.f, 8.f);
		m_winningLine.rotate(90);
	}

	// ------------------- //

	// diagonal from top left to bottom right
	else if (m_boardField[0].isValid == false && m_boardField[4].isValid == false && m_boardField[8].isValid == false
		&& m_boardField[0].occupiedBy == m_boardField[4].occupiedBy && m_boardField[0].occupiedBy == m_boardField[8].occupiedBy)
	{		
		RoundEnd(15.f, 15.f);
		m_winningLine.rotate(45);
		m_winningLine.setSize(sf::Vector2f(810, 5));
	}

	// diagonal from top right to bottom left
	else if (m_boardField[2].isValid == false && m_boardField[4].isValid == false && m_boardField[6].isValid == false
		&& m_boardField[2].occupiedBy == m_boardField[4].occupiedBy && m_boardField[2].occupiedBy == m_boardField[6].occupiedBy)
	{
		RoundEnd(585.f, 15.f);
		m_winningLine.setSize(sf::Vector2f(810, 5));
		m_winningLine.rotate(135);
	}

	// if no one wins
	else if (m_boardField[0].isValid == false && m_boardField[1].isValid == false && m_boardField[2].isValid == false
		&& m_boardField[3].isValid == false && m_boardField[4].isValid == false && m_boardField[5].isValid == false
		&& m_boardField[6].isValid == false && m_boardField[7].isValid == false && m_boardField[8].isValid == false)
	{
		m_gameEnded = true;
		m_endText.setPosition(660.f, 200.f);
		m_endText.setString("It's a tie");
		ResetWinnerLine();
	}
}

void MainWindow::RoundEnd(float x_winningLine, float y_winningLine)
{
	m_gameEnded = true;
	m_endText.setPosition(615.f, 200.f);
	if (m_currentPlayer == CurrentPlayer::ENUM_O)
	{
		m_endText.setString("Player X has won!");
		m_scoreBrd.ChangeScore(Scoreboard::PlayerScore::X_SCORE_ENUM, 1);
	}
	else
	{
		m_endText.setString("Player O has won!");
		m_scoreBrd.ChangeScore(Scoreboard::PlayerScore::O_SCORE_ENUM, 1);
	}

	ResetWinnerLine();
	m_winningLine.setPosition(x_winningLine, y_winningLine);
}



void MainWindow::SetField(int fldNr)
{
	sf::Sprite s;
	s.setPosition(m_boardField[fldNr].coords[0], m_boardField[fldNr].coords[1]);
	m_boardField[fldNr].occupiedBy = m_currentPlayer;

	if (m_currentPlayer == CurrentPlayer::ENUM_O)
	{
		s.setTexture(m_oTexture);
		m_oSprites.push_back(s);
		m_currentPlayer = CurrentPlayer::ENUM_X;
		m_currentPlayerText.setString("Current Player: X");
	}
	else
	{
		s.setTexture(m_xTexture);
		m_xSprites.push_back(s);
		m_currentPlayer = CurrentPlayer::ENUM_O;
		m_currentPlayerText.setString("Current Player: O");
	}
	m_boardField[fldNr].isValid = false;
}

void MainWindow::ResetWinnerLine()
{
	// resets the green line to its default settings
	m_winningLine.setRotation(0);
	m_winningLine.setSize(sf::Vector2f(584, 5));
}