#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
    sf::VideoMode videoMode(1600,900); // Window size
    std::string windowTitle = "Slithering Snake";
    auto windowStyles = sf::Style::Titlebar | sf::Style::Close;

    
    sf::RenderWindow window(videoMode, windowTitle, windowStyles);
    Game game(&window);
    game.run();

    return 0;
}