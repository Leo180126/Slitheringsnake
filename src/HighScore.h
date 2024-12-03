#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include <ctime>
class HighScoreState : public State{
    public:
        HighScoreState(Game& game);
        static void saveHighScore(const std::string& filename,int score);
        void loadScore();
        void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
        void update(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;
    private:
    Game& game_;
    int highScore;
    std::vector<int> scores;
    std::vector<std::string> lines;
};
#endif