#include "scoremanager.hpp"


//Con-/Destructors
ScoreManager::ScoreManager() {

    getScores();

}

ScoreManager::~ScoreManager() = default;

//Functions
void ScoreManager::compareScores() {
    //sorts greatest to smallest
    scores.resize(6);
    std::sort(scores.begin(), scores.end()
              ,[](int a, int b) {
        return a >= b; }
              );

}

void ScoreManager::initScoreFile() {

    scoreFile.open("score.cmgt", std::ios::in);
    if(scoreFile.is_open()) {
        getScores();
    }
    else{
        scoreFile.close();
        scoreFile.open("score.cmgt", std::ios::out);
        if (scoreFile.is_open()) {
            scoreFile << "0000 \n";
            scoreFile << "0000 \n";
            scoreFile << "0000 \n";
            scoreFile << "0000 \n";
            scoreFile << "0000 \n";
        }
        std::string line;
        while(getline(scoreFile, line)){
            std::cout << line <<std::endl;
        }
        scoreFile.close();
    }

}

void ScoreManager::updateScores(int newScore) {
    scores.resize(5);
    scores.push_back(newScore);

    this->compareScores();

    scoreFile.open("score.cmgt", std::ios::out);
    if (scoreFile.is_open()) {
        scoreFile << scores.at(0) << "\n";
        scoreFile << scores.at(1) << "\n";
        scoreFile << scores.at(2) << "\n";
        scoreFile << scores.at(3) << "\n";
        scoreFile << scores.at(4) << "\n";
        scoreFile.close();
    }


}

void ScoreManager::getScores() {
    scoreFile.open("score.cmgt", std::ios::in);
    if (scoreFile.is_open()) {
        int line;
        while (scoreFile >> line ) {
            scores.push_back(line);
            std::cout  <<scores.back()<<std::endl;
        }
        scoreFile.close();
    }
    scores.resize(6);
}

std::string ScoreManager::readHighScores() {
    scoreFile.open("score.cmgt", std::ios::in);
    if (scoreFile.is_open()) {
        std::string l;
        std::stringstream lines;
        while(getline(scoreFile, l)){
             lines << l  <<std::endl;
        }
        l = "Scores:\n" + lines.str();
        scoreFile.close();
        return l;
    }
    return "Could not find Scores";

}

void ScoreManager::resetScores() {
    scoreFile.open("score.cmgt", std::ios::out);
    if (scoreFile.is_open()) {
        scoreFile << "0" << "\n";
        scoreFile << "0"  << "\n";
        scoreFile << "0"  << "\n";
        scoreFile << "0"  << "\n";
        scoreFile << "0"  << "\n";
        scoreFile.close();
    }

}








