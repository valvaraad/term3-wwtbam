#pragma once
#include <iostream>

namespace TheGame
{
	class Question
	{
	public:
		std::string task;
		std::string answerA;
		std::string answerB;
		std::string answerC;
		std::string answerD;

		int rightAnswer;
		int difficulty = 0;
	public:
		void getQuestion(int level);
	};

	enum answerOption {
		A = 1,
		B,
		C,
		D
	};
}


