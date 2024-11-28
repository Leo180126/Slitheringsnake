#include <iostream>
#include "EndGameState.h"

EndGameState::EndGameState(Game &game, sf::RenderWindow &window_) : game_(game), window(window_){}

void EndGameState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            game_.changeState(new MenuState(game_,window.getSize().x,window.getSize().y));
        }
    }
}

void EndGameState::update(sf::RenderWindow &window) {
    // No update logic for end game state
}

void EndGameState::draw(sf::RenderWindow &window) {
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\endgame.mp3")){
        std::cerr<<"No r cac chau oi";
    }
    sf::Sound s;
    s.setBuffer(buffer);
    s.play();
    
    window.clear();
    // Optionally, display an "End Game" message
    // Uncomment and set up a font to display end game text on screen
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        std::cerr<<"Cant load file";
    }
    sf::Text endGameText("Game Over! Press Escape to exit.", font, 30);
    sf::Text replayText("Press enter to replay",font,20);
    
    endGameText.setFillColor(sf::Color::Red);
    endGameText.setPosition(window.getSize().x / 2 - endGameText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - endGameText.getGlobalBounds().height / 2);
    
    replayText.setFillColor(sf::Color::White);
    replayText.setPosition(window.getSize().x / 2 - replayText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - replayText.getGlobalBounds().height / 2 + endGameText.getGlobalBounds().height );

    window.setView(window.getDefaultView());
    window.draw(endGameText);
    window.draw(replayText);
    window.display();
}