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

	class VictoryState : public State
	{
	public:
		VictoryState(GameDataRef data, int volume, int score);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

		void getRecords(std::string filename);
		void updateRecords(std::string playerName, int playerScore, std::string filename);


	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Text _inputText;
		sf::Text _scoreText;

		std::string playerName;

		sf::SoundBuffer _victorySoundBuffer;
		sf::Sound _victorySound;

		int volume;
		int _score;

		std::vector<RecordUnit> _allRecords;
	};
}
