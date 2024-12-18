#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    enum State {
        MainMenu,
        DifficultyMenu
    };

    Menu(float width, float height);
    void draw(sf::RenderWindow &window);
    void setState(State state);
    State getState() const;

private:
    sf::Font font_;
    std::vector<sf::Text> mainMenuItems_;
    std::vector<sf::Text> difficultyMenuItems_;
    State state_;
};

#endif // MENU_H