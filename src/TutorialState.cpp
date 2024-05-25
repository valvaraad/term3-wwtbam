#include "TutorialState.h"
#include "QuestionState.h"
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

#include <sstream>

#include <iostream>

namespace TheGame
{
	TutorialState::TutorialState(GameDataRef data, int volume) : _data(data)
	{
		this->volume = volume;
	}

	void TutorialState::Init()
	{
		std::setlocale(LC_ALL, "ru_RU.UTF-8");
		this->_data->assets.LoadFont("Ingame Font", INGAME_FONT_FILEPATH);
		this->_data->assets.LoadTexture("Game Background", MAIN_MENU_BACKGROUND_FILEPATH);

		_info.setFillColor(sf::Color(0x00, 0x00, 0x33));
		_info.setPosition(192, 108);
		_info.setSize(sf::Vector2f(1536, 864));
		_info.setOutlineColor(sf::Color::White);
		_info.setOutlineThickness(5);

		_infotext.setString(L"Вам предстоит ответить на 15 вопросов на разные темы:\nгеография, искусство, точные науки и так далее. \n\n"
			"В распоряжении у вас три подсказки : \n\n"
			"Право на ошибку - позволяет ответить на вопрос два раза;\n\n"
			"Смена вопроса - замените вопрос на другой такой же сложности;\n\n"
			"Пропуск вопроса - переходите к следующему вопросу,\nно учтите - вы теряете возможные очки за правильный ответ!\n\n"
			"Удачной игры!\n"
			"И помните: чем меньше времени вы потратите на ответ,\nтем больше очков вы получите при победе!\n"
			"\n\n\n\nНажмите чтобы продолжить.");
		_infotext.setFont(this->_data->assets.GetFont("Ingame Font"));
		_infotext.setCharacterSize(33);
		_infotext.setFillColor(sf::Color::White);
		_infotext.setPosition(200, 150);
		_infotext.setStyle(sf::Text::Bold);


		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		if (!_tutorialMusic.openFromFile(TUTORIAL_MUSIC_FILEPATH))
		{
			std::cout << "error\n";
		}
		_tutorialMusic.setVolume(this->volume);
		_tutorialMusic.play();
		_tutorialMusic.setLoop(true);
	}

	void TutorialState::HandleInput()
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
				_tutorialMusic.stop();
				_data->machine.AddState(StateRef(new MainMenuState(_data, this->volume)), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || _data->input.IsTextClicked(_infotext, sf::Mouse::Left, _data->window))
			{
				_tutorialMusic.stop();
				Lifeline hints;
				_data->machine.AddState(StateRef(new QuestionState(_data, this->volume, 1, 0, sf::seconds(45.f), hints)), true);
			}
		}
	}

	void TutorialState::Update(float dt)
	{
	}

	void TutorialState::Draw(float dt)
	{
			this->_data->window.clear(sf::Color::Red);

			this->_data->window.draw(this->_background);

			this->_data->window.draw(_info);

			this->_data->window.draw(_infotext);

			this->_data->window.display();
	}
}
