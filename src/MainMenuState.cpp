
#include <sstream>
#include "MainMenuState.h"
#include "TutorialState.h"
#include "SettingState.h"
#include "RecordTableState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace TheGame
{

	void MainMenuState::SetMainMenuText(sf::Text& text, std::string name, int divSize)//div size == 10 to text, 6 to name
	{
		text.setFont(this->_data->assets.GetFont("The Font"));
		text.setString(name);
		text.setCharacterSize(SCREEN_HEIGHT / divSize);
		sf::Color textColor(0xFF, 0xD7, 0x00);
		text.setFillColor(textColor);
	}

	MainMenuState::MainMenuState(GameDataRef data, int volume) : _data(data)
	{
		this->volume = volume;
	}

	void MainMenuState::Init() 
	{
		this->_data->assets.LoadFont("The Font", FONT_FILEPATH);
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);


		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_gameLogo.setTexture(this->_data->assets.GetTexture("Game Title"));

		_background.setPosition(0, 0);
		_gameLogo.setPosition(735, 30);
		
		SetMainMenuText(_startText, "START", 12);
		_startText.setOutlineThickness(3);
		SetMainMenuText(_settingText, "SETTINGS", 12);
		_settingText.setOutlineThickness(3);
		SetMainMenuText(_recordTableText, "RECORD TABLE", 12);
		_recordTableText.setOutlineThickness(3);
		SetMainMenuText(_exitText, "EXIT", 12);
		_exitText.setOutlineThickness(3);

		_startText.setPosition((SCREEN_WIDTH / 2) - (_startText.getGlobalBounds().width / 2),
		(SCREEN_HEIGHT / 2) - _startText.getGlobalBounds().height / 2);

		_settingText.setPosition((SCREEN_WIDTH / 2) - (_settingText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 10) - _settingText.getGlobalBounds().height / 2);

		_recordTableText.setPosition((SCREEN_WIDTH / 2) - (_recordTableText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 10 * 2) - _recordTableText.getGlobalBounds().height / 2);

		_exitText.setPosition((SCREEN_WIDTH / 2) - (_exitText.getGlobalBounds().width / 2),
		(SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 10 * 3) - _exitText.getGlobalBounds().height / 2);

		if (!_mainMenuMusic.openFromFile(MAIN_MENU_MUSIC_FILEPATH))
		{
			std::cout << "error\n";
		}
		_mainMenuMusic.play();
		_mainMenuMusic.setVolume(this->volume);
		_mainMenuMusic.setLoop(true);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (_data->input.IsTextClicked(_startText, sf::Mouse::Left, _data->window))
			{
				_mainMenuMusic.stop();
				_data->machine.AddState(StateRef(new TutorialState(_data, this->volume)), true);
			}

			if (_data->input.IsTextClicked(_settingText, sf::Mouse::Left, _data->window))
			{
				_mainMenuMusic.stop();
				_data->machine.AddState(StateRef(new SettingState(_data, this->volume)), true);
			}

			if (_data->input.IsTextClicked(_recordTableText, sf::Mouse::Left, _data->window))
			{
				_mainMenuMusic.stop();
				_data->machine.AddState(StateRef(new RecordTableState(_data, this->volume)), true);
			}

			if (_data->input.IsTextClicked(_exitText, sf::Mouse::Left, _data->window))
			{
				this->_data->window.close();
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.draw(this->_gameLogo);

		this->_data->window.draw(this->_startText);
		this->_data->window.draw(this->_settingText);
		this->_data->window.draw(this->_recordTableText);
		this->_data->window.draw(this->_exitText);


		this->_data->window.display();
	}
}
