#include "GameplayState.h"
#include "PauseState.h"
#include "EndGameState.h"
#include "HighScore.h"
#include <thread>
GameplayState::GameplayState(Game& game, sf::RenderWindow* window, int difficultyLevel)
    : game_(game), window_(window), directionChosen_(Direction::None), highScore_(0), gameRunning_(true), tileEdgeLength_(20.f), cap(0), isPause(false) {
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
    }

    // Initialize game components
    field_ = std::make_unique<GameField>(window_->getSize().x / tileEdgeLength_,
                                         window_->getSize().y / tileEdgeLength_,
                                         tileEdgeLength_,
                                         game_.getTextures()[0].get());

    // Set snake speed based on difficulty level
    float snakeSpeed;
    if (difficultyLevel == 0) {
        snakeSpeed = 0.2f; // Easy
    } else if (difficultyLevel == 1) {
        snakeSpeed = 0.1f; // Medium
    } else if (difficultyLevel == 2) {
        snakeSpeed = 0.05f; // Hard
    }

    // Initialize snake with the selected speed
    snake_ = std::make_unique<Snake>(field_.get(), game_.getTextures()[1].get(), snakeSpeed);
    food_ = std::make_unique<FoodSpawner>(field_.get(), game_.getTextures()[2].get());

    // Load background texture
    if (!backgroundTexture_.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\background.jpg")) {
        std::cerr << "Error: Could not load background texture" << std::endl;
    }
    backgroundSprite_.setTexture(backgroundTexture_);

    // Init sound
    if(!eating.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\eatingsound.mp3")){
        std::cerr<<"Khong load duoc file tieng an";
    }

    if(!death.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\die.mp3")){
        std::cerr<<"Khong load duoc die efect";
    }
    eatingSound.setBuffer(eating);
    deathSound.setBuffer(death);
}

void GameplayState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            isPause=!isPause;
        }
        if (event.key.code == sf::Keyboard::Escape) {
            std::cout << "Escape key pressed" << std::endl;
        }
    }
}

void GameplayState::update(sf::RenderWindow &window) {
    if (!isPause) {
        if(gameRunning_){
            // Capture frame from the webcam
            cv::Mat frame;
            cap >> frame;
            if (frame.empty()) return;

            // Detect fingertip
            cv::Point fingertip = fingerDetector_.detectFingertip(frame);

            if (fingertip.x != -1 && fingertip.y != -1) {
                // Update direction based on fingertip position
                directionChosen_ = Direction::fromFingertipPosition(fingertip);
            }

            // Convert the frame to SFML texture
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
            webcamTexture_.create(frame.cols, frame.rows);
            webcamTexture_.update(frame.ptr());

            // Update the sprite
            webcamSprite_.setTexture(webcamTexture_);
            // Update snake and check game state
            snake_->update(directionChosen_, food_->currentPos());

            if (snake_->isFoodEaten()) {
                std::thread soundThread(&GameplayState::playSound, this, eatingSound);
                soundThread.detach();
                food_->respawn();
                highScore_++;
                window_->setTitle("SnakeGame | Score: " + std::to_string(highScore_));
            }

            if (snake_->isDead()) {
                std::thread soundThread(&GameplayState::playSound, this, deathSound);
                soundThread.join();
                std::cout << "The end! You are dead..." << std::endl;
                gameRunning_ = false;
                HighScoreState::saveHighScore("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\highscore.txt",highScore_);
                game_.changeState(new EndGameState(game_, *window_, highScore_));
            }
        }
    }
}

void GameplayState::draw(sf::RenderWindow &window) {
    if(!isPause){
        window.clear();
        // Set up views for game scene, background and webcam feed

        sf::View gameView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        sf::View webcamView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        sf::View backgroud(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        
        // Set the viewport for each view
        gameView.setViewport(sf::FloatRect(0.f, 0.4f, 0.8f, 0.6f));
        webcamView.setViewport(sf::FloatRect(0.6f, 0.f, 0.8f, 0.6f));
        //Draw the background
        
        // Draw the game scene
        window.setView(backgroud);
        window.draw(backgroundSprite_);
        window.setView(gameView);
        window.draw(*field_->getRectToDraw());
        for (auto drawable : snake_->getRectsToDraw())
            window.draw(*drawable);
        window.draw(*food_->getRectToDraw());

        // Draw the webcam feed
        window.setView(webcamView);
   

        sf::CircleShape controlLine;
        controlLine.setPosition(webcamView.getSize().x/4-60, webcamView.getSize().y/4-20);
        // controlLine.setPosition(0, 0);
        controlLine.setRadius(60);
        controlLine.setFillColor(sf::Color::Transparent);
        controlLine.setOutlineColor(sf::Color::Green);
        controlLine.setOutlineThickness(5);
        //Huong dan
        // Load font
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\Eater-Regular.ttf")) {
            std::cerr << "Can't load font file" << std::endl;
        }

        // Create directional text
        sf::Text huongDcText[4];
        std::string directions[4] = {"Up", "Down", "Left", "Right"};
        for (int i = 0; i < 4; i++) {
            huongDcText[i].setFont(font);
            huongDcText[i].setString(directions[i]);
            huongDcText[i].setCharacterSize(20);
            huongDcText[i].setFillColor(sf::Color::White);
        }

        // Position directional text around the control line
        huongDcText[0].setPosition(controlLine.getPosition().x + controlLine.getRadius() - huongDcText[0].getGlobalBounds().width / 2, controlLine.getPosition().y - huongDcText[0].getGlobalBounds().height - 10); // Up
        huongDcText[1].setPosition(controlLine.getPosition().x + controlLine.getRadius() - huongDcText[1].getGlobalBounds().width / 2, controlLine.getPosition().y + controlLine.getRadius() * 2 + 10); // Down
        huongDcText[2].setPosition(controlLine.getPosition().x - huongDcText[2].getGlobalBounds().width - 10, controlLine.getPosition().y + controlLine.getRadius() - huongDcText[2].getGlobalBounds().height / 2); // Left
        huongDcText[3].setPosition(controlLine.getPosition().x + controlLine.getRadius() * 2 + 10, controlLine.getPosition().y + controlLine.getRadius() - huongDcText[3].getGlobalBounds().height / 2); // Right

        

        window.draw(webcamSprite_);
        window.draw(controlLine);

        // Draw directional text
        for (int i = 0; i < 4; i++) {
            window.draw(huongDcText[i]);
        }
        
        window.display();
    }
    else{
        window.setView(window.getDefaultView());
        pausestate_.draw(window);
    }
}

void GameplayState::playSound(sf::Sound sound)
{   
    std::cout<<"Create thread ";
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(100)); // Avoid busy-waiting
    }
}
