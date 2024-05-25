#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "Game.h"

namespace TheGame
{
	struct RecordUnit {
		std::string playerName;
		int playerScore;
	};


	class RecordTableState : public State
	{
	public:
		RecordTableState(GameDataRef data, int volume);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

		void SetRecordTableText(sf::Text&, std::string, int, std::string, int);
		void LoadRecords(std::string filename);


	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Text _titleText;
		sf::Text _backText;
		sf::Music _rtMusic;
		int volume;

		std::vector<sf::Text> _names;
		std::vector<sf::Text> _scores;

		std::vector<RecordUnit> _allRecords;
	};
}

