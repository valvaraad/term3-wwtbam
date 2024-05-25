#include "QuestionState.h" // 100.470 + width 800 + height 150
#include "DEFINITIONS.h"	//100.690 -> 1030.470 -> 1030.690
#include "MainMenuState.h"
#include "Question.h"
#include "GameOverState.h"
#include "VictoryState.h"

#include <sstream>
#include <locale>
#include <codecvt>
#include <iostream>

namespace TheGame
{
	QuestionState::QuestionState(GameDataRef data, int volume, int level, int score, sf::Time timer, Lifeline hints) : _data(data)
	{
		this->volume = volume;
		this->currentLevel = level;
		this->currentScore = score;
		this->_timer = timer;
		this->availableBonuses = hints;
	}

	void QuestionState::SetQuestionText(sf::Text& text, std::wstring name)//div size == 10 to text, 6 to name
	{
		text.setFont(this->_data->assets.GetFont("Ingame Font"));
		text.setString(name);
		text.setCharacterSize(33);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
	}

	void QuestionState::Init()
	{
		std::setlocale(LC_ALL, "ru_RU.UTF-8");
		currentQuestion.getQuestion(currentLevel);

		std::cout << currentQuestion.task << std::endl;
		//current.task.insert(5, "\n");
		std::cout << currentQuestion.rightAnswer << std::endl;
		std::string progress = std::to_string(currentLevel) + FULL_PROGRESS;
		std::string cScore = _SCORE_ + std::to_string(currentScore);
		std::cout << progress << std::endl;
		std::cout << "Score: " << currentScore << std::endl;

		std::setlocale(LC_ALL, "ru_RU.UTF-8");
		this->_data->assets.LoadFont("Ingame Font", INGAME_FONT_FILEPATH);
		this->_data->assets.LoadFont("Timer Font", TIMER_FONT_FILEPATH);

		this->_data->assets.LoadTexture("Task Background", QUESTION_BACKGROUND_FILEPATH);

		this->_data->assets.LoadTexture("Win A", IF_RIGHT_A);
		this->_data->assets.LoadTexture("Win B", IF_RIGHT_B);
		this->_data->assets.LoadTexture("Win C", IF_RIGHT_C);
		this->_data->assets.LoadTexture("Win D", IF_RIGHT_D);

		this->_data->assets.LoadTexture("Lose A", IF_WRONG_A);
		this->_data->assets.LoadTexture("Lose B", IF_WRONG_B);
		this->_data->assets.LoadTexture("Lose C", IF_WRONG_C);
		this->_data->assets.LoadTexture("Lose D", IF_WRONG_D);

		this->_data->assets.LoadTexture("Skip", SKIP_QUESTION_ICON_FILEPATH);
		_skip.setTexture(this->_data->assets.GetTexture("Skip"));
		_skip.setPosition(650, 933);

		this->_data->assets.LoadTexture("Change", CHANGE_QUESTION_ICON_FILEPATH);
		_change.setTexture(this->_data->assets.GetTexture("Change"));
		_change.setPosition(500, 955);

		this->_data->assets.LoadTexture("Mistake", SECOND_CHANCE_ICON_FILEPATH);
		_mistake.setTexture(this->_data->assets.GetTexture("Mistake"));
		_mistake.setPosition(380, 954);

		_timerFrame.setRadius(95);
		_timerFrame.setPointCount(45);
		_timerFrame.setPosition(865, 865);
		_timerFrame.setOutlineColor(sf::Color::White);
		_timerFrame.setOutlineThickness(2);
		_timerFrame.setFillColor(sf::Color::Black);

		SetQuestionText(_timeRemaining, std::to_wstring(static_cast<int>(_timer.asSeconds())));
		_timeRemaining.setPosition(902.5, 908.5);
		_timeRemaining.setCharacterSize(85);
		_timeRemaining.setFont(this->_data->assets.GetFont("Timer Font"));

		_background.setTexture(this->_data->assets.GetTexture("Task Background"));
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		std::wstring wTask = converter.from_bytes(currentQuestion.task);
		SetQuestionText(_task, wTask);
		_task.setPosition(170, 150);

		std::wstring wA = converter.from_bytes(currentQuestion.answerA);
		SetQuestionText(_answerA, wA);
		_answerA.setPosition(140, 520);
		_buttonA.setTextureRect(sf::IntRect(100, 470, 800, 150));
		_buttonA.setColor(sf::Color::Transparent);

		std::wstring wB = converter.from_bytes(currentQuestion.answerB);
		SetQuestionText(_answerB, wB);
		_answerB.setPosition(1070, 520);
		_buttonB.setTextureRect(sf::IntRect(1030, 470, 800, 150));
		_buttonB.setColor(sf::Color::Transparent);

		std::wstring wC = converter.from_bytes(currentQuestion.answerC);
		SetQuestionText(_answerC, wC);
		_answerC.setPosition(140, 747);
		_buttonC.setTextureRect(sf::IntRect(100, 690, 800, 150));
		_buttonC.setColor(sf::Color::Transparent);

		std::wstring wD = converter.from_bytes(currentQuestion.answerD);
		SetQuestionText(_answerD, wD);
		_answerD.setPosition(1070, 747);
		_buttonD.setTextureRect(sf::IntRect(1030, 690, 800, 150));
		_buttonD.setColor(sf::Color::Transparent);

		std::wstring wProgress = converter.from_bytes(progress);
		SetQuestionText(_progress, wProgress);
		_progress.setPosition(100, 950);
		_progress.setCharacterSize(70);

		std::wstring wScore = converter.from_bytes(cScore);
		SetQuestionText(_score, wScore);
		_score.setPosition(1350, 950);
		_score.setCharacterSize(70);


		if (!_questionMusic.openFromFile(QUESTION_MUSIC_FILEPATH))
		{
			std::cout << "error\n";
		}
		_questionMusic.setVolume(this->volume);
		_questionMusic.play();
	}

	void QuestionState::HandleInput()
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
				_questionMusic.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::FloatRect boundsA(100, 470, 800, 150);
					sf::FloatRect boundsB(1030, 470, 800, 150);
					sf::FloatRect boundsC(100, 690, 800, 150);
					sf::FloatRect boundsD(1030, 690, 800, 150);
					sf::FloatRect bounds50(400, 950, 100, 70);

					sf::Vector2f mousePos = this->_data->window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->window));
					if (boundsA.contains(mousePos)) {
						if (currentQuestion.rightAnswer == 1) {
							currentLevel++;
							currentScore += 100 * (currentLevel - 1) + (currentLevel - 1) * (static_cast<int>(_timer.asSeconds()));
							_questionMusic.stop();
							_background.setTexture(this->_data->assets.GetTexture("Win A"));
							_answerA.setFillColor(sf::Color::Black);
							if (currentLevel == 16) { //16
								_data->machine.AddState(StateRef(new VictoryState(_data, this->volume, currentScore)));
								break;
							}
							_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel, currentScore, sf::seconds(45.f), this->availableBonuses)));
						}
						else {
							_background.setTexture(this->_data->assets.GetTexture("Lose A"));
							if (!_twoChances) {
								_questionMusic.stop();
								_data->machine.AddState(StateRef(new GameOverState(_data, this->volume)), true);
							}
							_twoChances = false;
						}
					}
					if (boundsB.contains(mousePos)) {
						if (currentQuestion.rightAnswer == 2) {
							currentLevel++;
							currentScore += 100 * (currentLevel - 1) + (currentLevel - 1) * (static_cast<int>(_timer.asSeconds()));
							_questionMusic.stop();
							_background.setTexture(this->_data->assets.GetTexture("Win B"));
							_answerB.setFillColor(sf::Color::Black);
							if (currentLevel == 16) { //16
								_data->machine.AddState(StateRef(new VictoryState(_data, this->volume, currentScore)));
								break;
							}
							_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel, currentScore, sf::seconds(45.f), this->availableBonuses)));
						}
						else {
							_background.setTexture(this->_data->assets.GetTexture("Lose B"));
							if (!_twoChances) {
								_questionMusic.stop();
								_data->machine.AddState(StateRef(new GameOverState(_data, this->volume)), true);
							}
							_twoChances = false;
						}
						//Button B functionality
					}
					if (boundsC.contains(mousePos)) {
						if (currentQuestion.rightAnswer == 3) {
							currentLevel++;
							currentScore += 100 * (currentLevel - 1) + (currentLevel - 1) * (static_cast<int>(_timer.asSeconds()));
							_questionMusic.stop();
							_background.setTexture(this->_data->assets.GetTexture("Win C"));
							_answerC.setFillColor(sf::Color::Black);
							if (currentLevel == 16) { //16
								_data->machine.AddState(StateRef(new VictoryState(_data, this->volume, currentScore)));
								break;
							}
							_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel, currentScore, sf::seconds(45.f), this->availableBonuses)));
						}
						else {
							_background.setTexture(this->_data->assets.GetTexture("Lose C"));
							if (!_twoChances) {
								_questionMusic.stop();
								_data->machine.AddState(StateRef(new GameOverState(_data, this->volume)), true);
							}
							_twoChances = false;
						}
						//Button C functionality
					}
					if (boundsD.contains(mousePos)) {
						if (currentQuestion.rightAnswer == 4) {
							currentLevel++;
							currentScore += 100 * (currentLevel - 1) + (currentLevel - 1) * (static_cast<int>(_timer.asSeconds()));
							_questionMusic.stop();
							_background.setTexture(this->_data->assets.GetTexture("Win D"));
							_answerD.setFillColor(sf::Color::Black);
							if (currentLevel == 16) { //16
								_data->machine.AddState(StateRef(new VictoryState(_data, this->volume, currentScore)));
								break;
							}
							_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel, currentScore, sf::seconds(45.f), this->availableBonuses)));
						}
						else {
							_background.setTexture(this->_data->assets.GetTexture("Lose D"));
							if (!_twoChances) {
								_questionMusic.stop();
								_data->machine.AddState(StateRef(new GameOverState(_data, this->volume)), true);
							}
							_twoChances = false;
						}
						//Button D functionality
					}
				}

			}
			if (_data->input.IsSpriteClicked(_skip, sf::Mouse::Left, _data->window) && this->availableBonuses.skipQuestion)
			{
				this->availableBonuses.skipQuestion = false;
				_questionMusic.stop();
				if (currentLevel == 15)
					_data->machine.AddState(StateRef(new VictoryState(_data, this->volume, currentScore)));
				else
					_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel + 1, currentScore, sf::seconds(45.f), this->availableBonuses)));
			}
			if (_data->input.IsSpriteClicked(_change, sf::Mouse::Left, _data->window) && this->availableBonuses.changeQuestion)
			{
				this->availableBonuses.changeQuestion = false;
				_questionMusic.stop();
				_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, currentLevel, currentScore, sf::seconds(45.f), this->availableBonuses)));
			}
			if (_data->input.IsSpriteClicked(_mistake, sf::Mouse::Left, _data->window) && this->availableBonuses.twoChances)
			{
				this->availableBonuses.twoChances = false;
				_twoChances = true;
			}
		}
	}

	void QuestionState::Update(float dt)
	{
		if (_timerClock.getElapsedTime().asSeconds() >= 1) {
			_timer -= sf::seconds(1);
			if (static_cast<int>(_timer.asSeconds()) >= 10)
				_timeRemaining.setString(std::to_wstring(static_cast<int>(_timer.asSeconds())));
			else {
				_timeRemaining.setString(L"0" + std::to_wstring(static_cast<int>(_timer.asSeconds())));
			}
			_timerClock.restart();
		}

		if (static_cast<int>(_timer.asSeconds()) <= 0) {
			_questionMusic.stop();
			_data->machine.AddState(StateRef(new GameOverState(_data, this->volume)), true);
		}
		if (!this->availableBonuses.skipQuestion) {
			sf::Color x = _skip.getColor();
			x.a = 60;
			_skip.setColor(x);
		}
		if (!this->availableBonuses.twoChances) {
			sf::Color x = _mistake.getColor();
			x.a = 60;
			_mistake.setColor(x);
		}
		if (!this->availableBonuses.changeQuestion) {
			sf::Color x = _change.getColor();
			x.a = 60;
			_change.setColor(x);
		}
	}

	void QuestionState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.draw(this->_task);
		this->_data->window.draw(this->_answerA);
		this->_data->window.draw(this->_answerB);
		this->_data->window.draw(this->_answerC);
		this->_data->window.draw(this->_answerD);

		this->_data->window.draw(this->_buttonA);
		this->_data->window.draw(this->_buttonB);
		this->_data->window.draw(this->_buttonC);
		this->_data->window.draw(this->_buttonD);
		this->_data->window.draw(this->_progress);
		this->_data->window.draw(this->_score);
		if (!this->availableBonuses.skipQuestion) {
			sf::Color x = _skip.getColor();
			x.a = 60;
			_skip.setColor(x);
		}
		if (!this->availableBonuses.twoChances) {
			sf::Color x = _mistake.getColor();
			x.a = 60;
			_mistake.setColor(x);
		}
		if (!this->availableBonuses.changeQuestion) {
			sf::Color x = _change.getColor();
			x.a = 60;
			_change.setColor(x);
		}
		this->_data->window.draw(this->_skip);
		this->_data->window.draw(this->_mistake);
		this->_data->window.draw(this->_change);
		this->_data->window.draw(this->_timerFrame);
		this->_data->window.draw(this->_timeRemaining);
		this->_data->window.display();
	}
}
