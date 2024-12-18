#include "Menu.h"

Menu::Menu(float width, float height) : state_(MainMenu) {
    if (!font_.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        // Handle error
    }

    std::vector<std::string> mainItems = {"Start Game", "High Scores", "Exit"};
    for (size_t i = 0; i < mainItems.size(); ++i) {
        sf::Text text;
        text.setFont(font_);
        text.setString(mainItems[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, height / (mainItems.size() + 1) * (i + 1)));
        mainMenuItems_.push_back(text);
    }

    std::vector<std::string> difficultyItems = {"Easy", "Medium", "Hard"};
    for (size_t i = 0; i < difficultyItems.size(); ++i) {
        sf::Text text;
        text.setFont(font_);
        text.setString(difficultyItems[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, height / (difficultyItems.size() + 1) * (i + 1)));
        difficultyMenuItems_.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow &window) {
    const auto& items = (state_ == MainMenu) ? mainMenuItems_ : difficultyMenuItems_;
    for (const auto &item : items) {
        window.draw(item);
    }
}



void Menu::setState(State state) {
    state_ = state;
}

Menu::State Menu::getState() const {
    return state_;
}