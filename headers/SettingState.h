#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "Game.h"

namespace TheGame
{
	class SettingState : public State
	{
	public:
		SettingState(GameDataRef data, int volume);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

		void SetSettingsText(sf::Text&, std::string, int);

	private:
		GameDataRef _data;
		sf::Sprite _background;
		sf::Text _settingsText;
		sf::Text _musicText;
		sf::Text _backText;
		sf::Text _plus;
		sf::Text _minus;
		sf::Text _volume;
		sf::Music _settingsMusic;
		int volume;
	};
}
