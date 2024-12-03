#include <iostream>
#include <string>
#include <thread>
#include "EndGameState.h"

EndGameState::EndGameState(Game &game, sf::RenderWindow &window_, int highScore_) : game_(game), window(window_), highScore(highScore_) {
    if(!endSound_buffer.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\endgame.mp3")){
        std::cerr<<"Khong load duoc end file";
    }
    endSound.setBuffer(endSound_buffer);
    std::thread soundThread(&EndGameState::playSound, this, endSound);
    soundThread.detach();
}

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
    
    window.clear();
    // Optionally, display an "End Game" message
    // Uncomment and set up a font to display end game text on screen
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        std::cerr<<"Cant load file";
    }
    sf::Text endGameText("Game Over! Press Escape to exit.", font, 30);
    sf::Text replayText("Press enter to replay",font,20);
    
    
    sf::Text pointText("High Score: " + std::to_string(highScore), font, 50);

    endGameText.setFillColor(sf::Color::Red);
    endGameText.setPosition(window.getSize().x / 2 - endGameText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - endGameText.getGlobalBounds().height / 2);
    
    replayText.setFillColor(sf::Color::White);
    replayText.setPosition(window.getSize().x / 2 - replayText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - replayText.getGlobalBounds().height / 2 + endGameText.getGlobalBounds().height );

    pointText.setFillColor(sf::Color::Red);
    pointText.setPosition(window.getSize().x / 2 - pointText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - pointText.getGlobalBounds().height / 2 - endGameText.getGlobalBounds().height*2);


    window.setView(window.getDefaultView());
    window.draw(endGameText);
    window.draw(replayText);
    window.draw(pointText);
    window.display();
}

void EndGameState::playSound(sf::Sound endSound)
{
    endSound.play();
    while(endSound.getStatus() == sf::Sound::Playing){
        sf::sleep(sf::milliseconds(100));
    }
}
