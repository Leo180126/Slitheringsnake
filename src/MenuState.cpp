#include "MenuState.h"
#include "GameplayState.h"

MenuState::MenuState(Game& game, float width, float height)
    : game_(game), menu_(width, height), isMenuActive_(true), difficultyLevel_(0) {}

void MenuState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num3) {
            int selectedItem = event.key.code - sf::Keyboard::Num1;
            if (menu_.getState() == Menu::MainMenu) {
                menu_.selectItem(selectedItem);
                if (selectedItem == 0) {
                    menu_.setState(Menu::DifficultyMenu); // Go to Difficulty Menu
                } else if (selectedItem == 1) {
                    // Show High Scores (implement as needed)
                } else if (selectedItem == 2) {
                    window.close(); // Exit
                }
            } else if (menu_.getState() == Menu::DifficultyMenu) {
                menu_.selectItem(selectedItem);
                difficultyLevel_ = selectedItem; // Set difficulty level
                isMenuActive_ = false; // Start Game
            }
        }
    }
}

void MenuState::update(sf::RenderWindow &window) {
    if (!isMenuActive_) {
        // Transition to GameplayState
        game_.changeState(new GameplayState(game_, &window, difficultyLevel_));
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    window.clear();
    menu_.draw(window);
    window.display();
}