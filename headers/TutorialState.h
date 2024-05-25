#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "Game.h"

namespace TheGame
{
	class TutorialState : public State
	{
	public:
		TutorialState(GameDataRef data, int volume);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::RectangleShape _info;

		sf::Text _infotext;

		sf::Music _tutorialMusic;

		int volume;
	};
}

