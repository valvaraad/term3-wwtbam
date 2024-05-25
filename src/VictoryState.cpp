#include "VictoryState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h" 

#include <sstream>
#include <fstream>
#include <vector>

#include <iostream>

namespace TheGame
{
	VictoryState::VictoryState(GameDataRef data, int volume, int score) : _data(data)
	{
		this->volume = volume;
		this->_score = score;
	}

	void VictoryState::Init()
	{
		this->_data->assets.LoadFont("Bold Font", BOLD_RECORD_FILEPATH);
		std::cout << "Victory!" << std::endl;

		if (!_victorySoundBuffer.loadFromFile(VICTORY_SFX))
		{
			std::cout << "error\n";
		}

		_victorySound.setBuffer(_victorySoundBuffer);
		_victorySound.setVolume(this->volume);
		_victorySound.play();

		_inputText.setFont(this->_data->assets.GetFont("Bold Font"));
		_inputText.setCharacterSize(40);
		_inputText.setFillColor(sf::Color(0xFF, 0xD7, 0x00));
		_inputText.setPosition(615, 330);

		_scoreText.setFont(this->_data->assets.GetFont("Bold Font"));
		_scoreText.setCharacterSize(40);
		_scoreText.setFillColor(sf::Color(0xFF, 0xD7, 0x00));
		_scoreText.setPosition(615, 550);
		_scoreText.setString("Score: " + std::to_string(this->_score));

		this->_data->assets.LoadTexture("Victory Background", VICTORY_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Victory Background"));

		this->getRecords(RECORDS_FILE);
	}

	void VictoryState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					if (this->playerName != "")
						this->updateRecords(this->playerName, this->_score, RECORDS_FILE);
					_victorySound.stop();
					_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
				}
				else if (event.text.unicode < 128 && event.text.unicode != 8 && this->playerName.length() < NAME_LENGTH_LIMIT) {
					this->playerName += static_cast<char>(event.text.unicode);
					_inputText.setString(this->playerName);
				}
				else if (event.text.unicode == 8 && !this->playerName.empty()) {
					this->playerName.pop_back();
					_inputText.setString(this->playerName);
				}
				
			}
		}
	}

	void VictoryState::Update(float dt)
	{
		
	}

	void VictoryState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_inputText);
		this->_data->window.draw(this->_scoreText);

		this->_data->window.display();
	}

	void VictoryState::getRecords(std::string filename)
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

	void VictoryState::updateRecords(std::string playerName, int playerScore, std::string filename)
	{
		RecordUnit entry;
		entry.playerName = playerName;
		entry.playerScore = playerScore;
		this->_allRecords.push_back(entry);

		std::sort(this->_allRecords.begin(), this->_allRecords.end(), [](const RecordUnit& a, const RecordUnit& b) {return a.playerScore > b.playerScore; });
		if (this->_allRecords.size() > RECORD_ENTRIES_LIMIT)
			this->_allRecords.pop_back();

		std::ofstream recordFile(filename);

		if (recordFile.is_open()) {
			for (const auto& unit : this->_allRecords) {
				recordFile << unit.playerName << ": " << unit.playerScore << std::endl;
			}
			recordFile.close();
		}
		else {
			std::cout << "Unable to update records." << std::endl;
			return;
		}


	}
}