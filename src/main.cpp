#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
    sf::VideoMode videoMode(1280,960); // Khai báo cửa sổ 
    std::string windowTitle = "Slithering Snake";
    auto windowStyles = sf::Style::Titlebar | sf::Style::Close;

    
    sf::RenderWindow window(videoMode, windowTitle, windowStyles);
    window.setPosition(sf::Vector2i(200, 0));
    Game game(&window);
    game.run();

    return 0;
}