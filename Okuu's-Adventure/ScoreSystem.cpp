#include "ScoreSystem.h"
Score::Score()
{
	score = 0;
	highscore = 0;
}
void Score::loadHighScore(const char* filename)
{
    inFile.open(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    inFile >> highscore;
    inFile.close();
}
void Score::saveHighScore(const char* filename) {
    outFile.open(filename);
    if (!outFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    outFile << highscore;
    outFile.close();
}
void Score::updateHighScore(int counting_score, const char* filename) {
    score = counting_score;
    if (score > highscore) {
        highscore = score;
        saveHighScore(filename);
    }
}
int Score::getHighScore()
{
    return highscore;
}
int Score::getCurrentScore()
{
    return score;
}