#include "EndGameState.h"
#include <iostream>
EndGameState::EndGameState() {}

void EndGameState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
}

void EndGameState::update(sf::RenderWindow &window) {
    // No update logic for end game state
}

void EndGameState::draw(sf::RenderWindow &window) {
    window.clear();
    // Optionally, display an "End Game" message
    // Uncomment and set up a font to display end game text on screen
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        std::cerr<<"Cant load file";
    }
    sf::Text endGameText("Game Over! Press Escape to exit.", font, 30);
    endGameText.setFillColor(sf::Color::Red);
    endGameText.setPosition(window.getSize().x / 2 - endGameText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - endGameText.getGlobalBounds().height / 2);
    window.setView(window.getDefaultView());
    window.draw(endGameText);
    window.display();
}