#include "Question.h"
#include "DEFINITIONS.h"
#include <string>
#include <fstream>

namespace TheGame
{
	void Question::getQuestion(int level)
	{
		srand(time(nullptr));
		int topic = std::rand() % 10 + 1;
		std::string filename = TOPIC_FILENAME + std::to_string(topic) + TOPIC_EXTENSION;
		std::cout << filename << std::endl;
		std::ifstream inputFile(filename);

		std::string right;

		for (int i = 0; i < 2 + 8*(level - 1); i++)
			std::getline(inputFile, this->task);
		
		std::getline(inputFile, this->answerA);
		std::getline(inputFile, this->answerB);
		std::getline(inputFile, this->answerC);
		std::getline(inputFile, this->answerD);
		std::getline(inputFile, right);
		this->rightAnswer = std::stoi(right);
	}
}


