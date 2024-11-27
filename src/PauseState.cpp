#include "PauseState.h"
#include <iostream>

PauseState::PauseState() {
    if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        std::cerr << "Error: Could not load font" << std::endl;
    }

    if(!back.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\background.png")){
        std::cerr<<"Khong load duoc file";
    }
    back_.setTexture(back);


    pausedText.setFont(font);
    pausedText.setString("Paused");
    pausedText.setCharacterSize(50);
    pausedText.setFillColor(sf::Color::Red);
    pausedText.setStyle(sf::Text::Bold);

    instruction.setFont(font);
    instruction.setString("Bam space de tiep tuc");
    instruction.setCharacterSize(30);
    instruction.setFillColor(sf::Color::White);
    instruction.setStyle(sf::Text::Bold);
}

PauseState::~PauseState() = default;

void PauseState::draw(sf::RenderWindow &window) {
    // Background
    

    // Center the paused text
    pausedText.setPosition(window.getSize().x / 2 - pausedText.getGlobalBounds().width / 2,
                           window.getSize().y / 2 - pausedText.getGlobalBounds().height / 2);
    instruction.setPosition(window.getSize().x / 2 - instruction.getGlobalBounds().width / 2 ,
                           window.getSize().y / 2 - instruction.getGlobalBounds().height / 2 + pausedText.getGlobalBounds().height );
    //Draw scene
    window.draw(back_);
    window.draw(pausedText);
    window.draw(instruction);
    window.display();
}