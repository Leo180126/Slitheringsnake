#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include "State.h"
#include "HighScore.h"
#include "Game.h"
#include "MenuState.h"
#include <cstring>
#include <SFML/Audio.hpp>


class EndGameState : public State {
public:
    EndGameState(Game &game,sf::RenderWindow &window, int highScore);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;
    void playSound(sf::Sound endSound);
private:
    Game& game_;
    sf::RenderWindow &window;
    int highScore;
    sf::SoundBuffer endSound_buffer;
    sf::Sound endSound;
};

#endif // END_GAME_STATE_H