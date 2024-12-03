#ifndef SNAKE_GAME_GAME_H
#define SNAKE_GAME_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <array>
#include "State.h"

class Game
{
public:
    Game(sf::RenderWindow *window);
    ~Game();

    void run();
    void changeState(State* newState);
    const std::array<std::unique_ptr<sf::Texture>, 3>& getTextures() const;
    void playBgm();

private:
    sf::RenderWindow* window_;
    std::unique_ptr<State> currentState_;
    std::array<std::unique_ptr<sf::Texture>, 3> textures_; // 0 - field, 1 - food, 2 - snake
};

#endif // SNAKE_GAME_GAME_H