#include "HighScore.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <string>

HighScoreState::HighScoreState(Game &game): game_(game)
{
    std::ifstream file("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\highscore.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
            std::istringstream iss(line);
            int score;
            if (iss >> score) {
                scores.push_back(score);
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open high score file: " << std::endl;
    }
    highScore = scores[0];
    for(int i=1; i<scores.size(); i++){
        if(highScore < scores[i]) highScore = scores[i];
    }

    if (lines.size() > 5) {
        lines.erase(lines.begin(), lines.end() - 5);
    }

}
void HighScoreState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    if(event.type == sf::Event::Closed)
        window.close();
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
        game_.changeState(new MenuState(game_, window.getSize().x, window.getSize().y));

}

void HighScoreState::update(sf::RenderWindow &window)
{
}

void HighScoreState::draw(sf::RenderWindow &window)
{
    window.clear();

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
        std::cerr << "Can't load font file" << std::endl;
    }

    sf::Text title("Scores", font, 50);
    title.setFillColor(sf::Color::Red);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 50);
    window.draw(title);

    float yOffset = 150;

    for (const auto& line_ : lines) {
        sf::Text lineText(line_, font, 30);
        lineText.setFillColor(sf::Color::White);
        lineText.setPosition(window.getSize().x / 2 - lineText.getGlobalBounds().width / 2, yOffset);
        window.draw(lineText);
        yOffset += 50;
        }
    sf::Text highestScoreText("Highest Score: " + std::to_string(highScore), font, 50);
    highestScoreText.setFillColor(sf::Color::Green);
    highestScoreText.setPosition(window.getSize().x / 2 - highestScoreText.getGlobalBounds().width / 2, yOffset + 30);
    window.draw(highestScoreText);

    window.display();
}


void HighScoreState::saveHighScore(const std::string &filename, int score)
{
    std::ofstream file(filename,std::ios::app);
    if(file.is_open()){
        std::time_t now = time(0);
        file << score << ' ' <<asctime(localtime(&now));
        file.close();
    }
}
