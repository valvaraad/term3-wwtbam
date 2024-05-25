#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h" 

#include <sstream>

#include <iostream>

namespace TheGame
{
	GameOverState::GameOverState(GameDataRef data, int volume) : _data(data)
	{
		this->volume = volume;
	}

	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		this->_data->assets.LoadFont("Font", BOLD_RECORD_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));

		if (!_gameOverSoundBuffer.loadFromFile(WRONG_ANSWER_SFX))
		{
			std::cout << "error\n";
		}

		_loss.setString("Your answer was wrong.");
		_loss.setFont(this->_data->assets.GetFont("Font"));
		_loss.setCharacterSize(40);
		_loss.setFillColor(sf::Color::Red);
		_loss.setPosition((SCREEN_WIDTH / 2) - (_loss.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - _loss.getGlobalBounds().height / 2);
		_gameOverSound.setBuffer(_gameOverSoundBuffer);
		_gameOverSound.setVolume(this->volume);
		_gameOverSound.play();
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || _data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window))
			{
				//_tutorialSound.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{
	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(_loss);

		this->_data->window.display();
	}
}
