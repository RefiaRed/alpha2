#pragma once

#include "headers.hpp"
class ScoreManager {
private:
    std::vector<int> scores;
    std::fstream scoreFile;


    void compareScores();


public:
    ScoreManager();
    ~ScoreManager();


    void initScoreFile();
    void updateScores(int newScore);
    void getScores();
    std::string readHighScores();
    void resetScores();

};

