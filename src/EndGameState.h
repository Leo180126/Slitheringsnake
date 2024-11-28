#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include "State.h"
#include "Game.h"
#include "MenuState.h"
#include <SFML/Audio.hpp>


class EndGameState : public State {
public:
    EndGameState(Game &game,sf::RenderWindow &window);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;
private:
    Game& game_;
    sf::RenderWindow &window;
};

#endif // END_GAME_STATE_H