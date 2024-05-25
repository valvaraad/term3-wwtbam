#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"

namespace TheGame
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int volume);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::SoundBuffer _gameOverSoundBuffer;
		sf::Sound _gameOverSound;
		sf::Text _loss;

		int volume;
	};
}
