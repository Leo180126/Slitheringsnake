#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.h"

class PauseState {
public:
    PauseState();
    ~PauseState();
    void draw(sf::RenderWindow &window);
private:
    sf::Font font;
    sf::Text pausedText;
    sf::Text instruction;
    sf::Texture back;
    sf::Sprite back_;
};

#endif // PAUSE_STATE_H