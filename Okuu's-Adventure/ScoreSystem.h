#pragma once
#include <fstream>
#include "TextObject.h"
class Score : public TextObject
{
public:
	Score();
	void loadHighScore(const char* filename);
	void saveHighScore(const char* filename);
	void updateHighScore(int counting_score, const char* filename);
	int getHighScore();
	int getCurrentScore();
private:
	int score;
	int highscore;
	std::ifstream inFile;
	std::ofstream outFile;
};