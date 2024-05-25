#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "Game.h"
#include "Question.h"

namespace TheGame
{
	struct Lifeline {
		bool skipQuestion = true;
		bool changeQuestion = true;
		bool twoChances = true;
	};

	class QuestionState : public State
	{
	public:
		QuestionState(GameDataRef data, int volume, int level, int score, sf::Time timer, Lifeline hints);

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

		void SetQuestionText(sf::Text&, std::wstring);

	private:
		GameDataRef _data; //

		sf::Sprite _background; //

		sf::Sprite _buttonA; //
		sf::Sprite _buttonB;//
		sf::Sprite _buttonC;//
		sf::Sprite _buttonD;//
		
		sf::Sprite _skip;//
		sf::Sprite _mistake;//
		sf::Sprite _change;//

		sf::Time _timer;//
		sf::CircleShape _timerFrame;//
		sf::Clock _timerClock;//
		sf::Text _timeRemaining;//

		Lifeline availableBonuses;//

		bool _twoChances = false;//

		sf::Music _questionMusic; //

		int volume; //

		sf::Text _task;
		sf::Text _answerA;
		sf::Text _answerB;
		sf::Text _answerC;
		sf::Text _answerD;
		sf::Text _progress;
		sf::Text _score;
		
		Question currentQuestion;
		int currentLevel;
		int currentScore = 0;
	};
}

