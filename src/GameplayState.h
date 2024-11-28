#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

#include "State.h"
#include "GameField.h"
#include "PauseState.h"
#include "Snake.h"
#include "FoodSpawner.h"
#include "FingerDetector.h"
#include "Game.h"
#include <opencv2/opencv.hpp>
#include <SFML/Audio.hpp>

class GameplayState : public State {
public:
    GameplayState(Game& game, sf::RenderWindow* window, int difficultyLevel);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

private:
    Game& game_;
    sf::RenderWindow* window_;
    std::unique_ptr<GameField> field_;
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<FoodSpawner> food_;
    FingerDetector fingerDetector_;
    Direction::Type directionChosen_;
    int highScore_;
    bool gameRunning_;
    float tileEdgeLength_;
    cv::VideoCapture cap;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    sf::Texture webcamTexture_;
    sf::Sprite webcamSprite_;
    PauseState pausestate_;
    bool isPause;
    sf::SoundBuffer eating, death;
    sf::Sound eatingSound, deathSound; 
};

#endif // GAMEPLAY_STATE_H