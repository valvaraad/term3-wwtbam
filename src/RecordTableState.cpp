#include "RecordTableState.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "MainMenuState.h"
#include "DEFINITIONS.h"

namespace TheGame
{

	void RecordTableState::SetRecordTableText(sf::Text& text, std::string name, int size, std::string font, int thickness)//div size == 10 to text, 6 to name
	{
		text.setFont(this->_data->assets.GetFont(font));
		text.setString(name);
		text.setCharacterSize(size);
		sf::Color textColor(0xFF, 0xD7, 0x00);
		text.setFillColor(textColor);
		text.setOutlineThickness(thickness);
	}

	RecordTableState::RecordTableState(GameDataRef data, int volume) : _data(data)
	{
		this->volume = volume;
	}

	void RecordTableState::Init()
	{
		this->_data->assets.LoadFont("The Font", FONT_FILEPATH);
		this->_data->assets.LoadFont("Ingame Font", INGAME_FONT_FILEPATH);
		this->_data->assets.LoadFont("Bold Font", BOLD_RECORD_FILEPATH);

		this->LoadRecords(RECORDS_FILE);

		for (int i = 0; i < _allRecords.size(); i++) {
			sf::Text _nameBuf, _scoreBuf;
			SetRecordTableText(_nameBuf, this->_allRecords[i].playerName, 65, "Bold Font", 2);
			SetRecordTableText(_scoreBuf, std::to_string(this->_allRecords[i].playerScore), 65, "Bold Font", 2);
			_nameBuf.setPosition((SCREEN_WIDTH / 2) - (_nameBuf.getGlobalBounds().width / 2) - 365, 216 + (90 * i));
			_nameBuf.setStyle(sf::Text::Bold);
			this->_names.push_back(_nameBuf);

			_scoreBuf.setPosition((SCREEN_WIDTH / 2) - (_scoreBuf.getGlobalBounds().width / 2) + 365, 216 + (90 * i));
			_scoreBuf.setStyle(sf::Text::Bold);
			this->_scores.push_back(_scoreBuf);
		}

		this->_data->assets.LoadTexture("Record Table Background", RT_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Record Table Background"));

		SetRecordTableText(_titleText, "RECORD TABLE", 120, "The Font", 3);
		SetRecordTableText(_backText, "BACK TO MAIN MENU", 70, "The Font", 3);

		_titleText.setPosition((SCREEN_WIDTH / 2) - (_titleText.getGlobalBounds().width / 2), 20);

		_backText.setPosition((SCREEN_WIDTH / 2) - (_backText.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 10 * 4) - _backText.getGlobalBounds().height / 2);
		if (!_rtMusic.openFromFile(RECORDTABLE_MUSIC_FILEPATH))
		{
			std::cout << "error\n";
		}
		_rtMusic.play();
		_rtMusic.setVolume(this->volume);
		_rtMusic.setLoop(true);
	}

	void RecordTableState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_rtMusic.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}

			if (_data->input.IsTextClicked(_backText, sf::Mouse::Left, _data->window))
			{
				_rtMusic.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}
		}
	}

	void RecordTableState::Update(float dt)
	{
	}

	void RecordTableState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.draw(this->_titleText);
		this->_data->window.draw(this->_backText);

		for (const auto& unit : this->_names) {
			this->_data->window.draw(unit);
		}
		for (const auto& unit : this->_scores) {
			this->_data->window.draw(unit);
		}

		this->_data->window.display();
	}

	void RecordTableState::LoadRecords(std::string filename)
	{
		std::fstream recordFile(filename, std::ios::in | std::ios::out);

		if (!recordFile.is_open()) {
			std::cout << "Unable to get records." << std::endl;
			return;
		}

		std::string recordEntry;
		std::streampos filePos;

		while (std::getline(recordFile, recordEntry)) {
			std::istringstream inputStream(recordEntry);
			RecordUnit _entry;

			if (std::getline(inputStream, _entry.playerName, ':') && (inputStream >> _entry.playerScore)) {
				this->_allRecords.push_back(_entry);
			}
		}

		recordFile.close();
	}
}

