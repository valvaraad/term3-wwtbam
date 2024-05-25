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
		static bool wasButtonPressed = false; // ���� ��� ������������ ����������� ��������� ������
		static bool isButtonPressed = false;  // ���� ��� ������������ �������� ��������� ������

		isButtonPressed = sf::Mouse::isButtonPressed(button);

		if (isButtonPressed && !wasButtonPressed) // ���� ������ ������ ��� ���� ������
		{
			sf::FloatRect textBounds = text.getGlobalBounds();
			sf::Vector2f textPosition = text.getPosition();

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f translatedMousePos = window.mapPixelToCoords(mousePosition);

			if (textBounds.contains(translatedMousePos))
			{
				wasButtonPressed = true; // ������������� ����, ��� ������ ���� ������
				return true;
			}
		}
		else if (!isButtonPressed) // ���� ������ ��������
		{
			wasButtonPressed = false; // ���������� ����
		}

		return false;
	}


}