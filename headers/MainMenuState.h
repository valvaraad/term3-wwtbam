#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "Game.h"

namespace TheGame
{
	class MainMenuState:public State
	{
	public:
		MainMenuState(GameDataRef data, int volume);

		void Init();

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

		void SetMainMenuText(sf::Text&, std::string, int);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _gameLogo;

		sf::Text _startText;
		sf::Text _settingText;
		sf::Text _recordTableText;
		sf::Text _exitText;
		sf::Music _mainMenuMusic;
		int volume;
	};
}
