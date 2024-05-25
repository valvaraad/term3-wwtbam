#include "InputManager.h"

namespace TheGame
{
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}

	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (playButtonRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}

	bool InputManager::IsTextClicked(const sf::Text& text, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		static bool wasButtonPressed = false; // Флаг для отслеживания предыдущего состояния кнопки
		static bool isButtonPressed = false;  // Флаг для отслеживания текущего состояния кнопки

		isButtonPressed = sf::Mouse::isButtonPressed(button);

		if (isButtonPressed && !wasButtonPressed) // Если кнопка только что была нажата
		{
			sf::FloatRect textBounds = text.getGlobalBounds();
			sf::Vector2f textPosition = text.getPosition();

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f translatedMousePos = window.mapPixelToCoords(mousePosition);

			if (textBounds.contains(translatedMousePos))
			{
				wasButtonPressed = true; // Устанавливаем флаг, что кнопка была нажата
				return true;
			}
		}
		else if (!isButtonPressed) // Если кнопка отпущена
		{
			wasButtonPressed = false; // Сбрасываем флаг
		}

		return false;
	}


}