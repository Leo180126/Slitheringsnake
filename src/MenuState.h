#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "Menu.h"
#include "Game.h"

class MenuState : public State {
public:
    MenuState(Game& game, float width, float height);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

private:
    Game& game_;
    Menu menu_;
    bool isMenuActive_;
    int difficultyLevel_;
};

#endif // MENU_STATE_H