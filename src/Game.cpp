#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "Game.h"
#include "MenuState.h"
#include "GameplayState.h"
#include "PauseState.h"
#include "EndGameState.h"

Game::Game(sf::RenderWindow* window)
    : window_(window)
{
    // Load textures from config.txt
    std::ifstream configFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\config.txt");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config.txt" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        size_t delimiterPos = line.find('=');
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(value)) {
            std::cerr << "Failed to load texture: " << value << std::endl;
            exit(EXIT_FAILURE);
        }

        if (key == "fieldTexture") {
            textures_[0] = std::move(texture);
        } else if (key == "snakeTexture") {
            textures_[1] = std::move(texture);
        } else if (key == "foodTexture") {
            textures_[2] = std::move(texture);
        }
    }
    configFile.close();

    currentState_ = std::make_unique<MenuState>(*this, window_->getSize().x, window_->getSize().y);
}

Game::~Game() = default;

void Game::changeState(State* newState)
{
    currentState_.reset(newState);
}

const std::array<std::unique_ptr<sf::Texture>, 3>& Game::getTextures() const {
    return textures_;
}

void Game::playBgm()
{
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\backgroundMusic.mp3")){
        std::cerr<<"Khong mo duoc nhac nen";
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

void Game::run()
{
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\backgroundMusic.mp3")){
        std::cerr<<"Khong mo duoc nhac nen";
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    
    while (window_->isOpen())
    {
        sf::Event event;
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window_->close();
            }

            currentState_->handleEvent(*window_, event);
        }

        currentState_->update(*window_);
        currentState_->draw(*window_);
    }
}
