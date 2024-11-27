#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include "State.h"

class EndGameState : public State {
public:
    EndGameState();
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;
};

#endif // END_GAME_STATE_H