#include "SettingState.h"

#include <sstream>
#include "MainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace TheGame
{

	void SettingState::SetSettingsText(sf::Text& text, std::string name, int divSize)//div size == 10 to text, 6 to name
	{
		text.setFont(this->_data->assets.GetFont("The Font"));
		text.setString(name);
		text.setCharacterSize(SCREEN_HEIGHT / divSize);
		sf::Color textColor(0xFF, 0xD7, 0x00);
		text.setFillColor(textColor);
	}

	SettingState::SettingState(GameDataRef data, int volume) : _data(data)
	{
		this->volume = volume;
	}

	void SettingState::Init()
	{
		this->_data->assets.LoadFont("The Font", FONT_FILEPATH);
		this->_data->assets.LoadFont("Volume Font", TIMER_FONT_FILEPATH);

		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		SetSettingsText(_settingsText, "SETTINGS", 9);
		_settingsText.setOutlineThickness(3);
		SetSettingsText(_musicText, "MUSIC", 15);
		_musicText.setOutlineThickness(3);
		SetSettingsText(_backText, "BACK TO MAIN MENU", 14);
		_backText.setOutlineThickness(3);

		SetSettingsText(_minus, "-", 15);
		_minus.setFont(this->_data->assets.GetFont("Volume Font"));
		_minus.setPosition(((SCREEN_WIDTH / 3) - (_minus.getGlobalBounds().width / 2) + 400),
			(SCREEN_HEIGHT / 3) - _musicText.getGlobalBounds().height / 2);

		SetSettingsText(_plus, "+", 15);
		_plus.setFont(this->_data->assets.GetFont("Volume Font"));
		_plus.setPosition(((SCREEN_WIDTH / 3) - (_plus.getGlobalBounds().width / 2) + 700),
			(SCREEN_HEIGHT / 3) - _musicText.getGlobalBounds().height / 2);

		SetSettingsText(_volume, std::to_string(this->volume), 15);
		_volume.setFont(this->_data->assets.GetFont("Volume Font"));
		_volume.setPosition(((SCREEN_WIDTH / 3) - (_volume.getGlobalBounds().width / 2) + 550),
			(SCREEN_HEIGHT / 3) - _musicText.getGlobalBounds().height / 2);


		_settingsText.setPosition((SCREEN_WIDTH / 2) - (_settingsText.getGlobalBounds().width / 2), 20);

		_musicText.setPosition((SCREEN_WIDTH / 3) - (_musicText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 3) - _musicText.getGlobalBounds().height / 2);

		_backText.setPosition((SCREEN_WIDTH / 2) - (_backText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 10 * 4) - _backText.getGlobalBounds().height / 2);
		if (!_settingsMusic.openFromFile(MAIN_MENU_MUSIC_FILEPATH))
		{
			std::cout << "error\n";
		}
		_settingsMusic.setVolume(this->volume);
		_settingsMusic.play();
	}

	void SettingState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (_data->input.IsTextClicked(_backText, sf::Mouse::Left, _data->window))
			{
				_settingsMusic.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}

			if (_data->input.IsTextClicked(_plus, sf::Mouse::Left, _data->window) && this->volume < 100)
			{
				this->volume += 10;
				_settingsMusic.setVolume(this->volume + 10);
			}

			if (_data->input.IsTextClicked(_minus, sf::Mouse::Left, _data->window) && this->volume > 0)
			{
				this->volume -= 10;
				_settingsMusic.setVolume(this->volume - 10);
			}
		}
	}

	void SettingState::Update(float dt)
	{
		_volume.setPosition(((SCREEN_WIDTH / 3) - (_volume.getGlobalBounds().width / 2) + 550),
			(SCREEN_HEIGHT / 3) - _musicText.getGlobalBounds().height / 2);
		_volume.setString(std::to_string(this->volume));
	}

	void SettingState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.draw(this->_settingsText);
		this->_data->window.draw(this->_musicText);
		this->_data->window.draw(this->_minus);
		this->_data->window.draw(this->_plus);
		this->_data->window.draw(this->_volume);
		this->_data->window.draw(this->_backText);


		this->_data->window.display();
	}
}
