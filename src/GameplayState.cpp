#include "GameplayState.h"
#include "PauseState.h"
#include "EndGameState.h"
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
    if (!backgroundTexture_.loadFromFile("C:\\Users\\84333\\projects\\Opencv_SFML_example\\src\\background.png")) {
        std::cerr << "Error: Could not load background texture" << std::endl;
    }
    backgroundSprite_.setTexture(backgroundTexture_);

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
                food_->respawn();
                highScore_++;
                window_->setTitle("SnakeGame | Score: " + std::to_string(highScore_));
                // if (highScore_ + 3 == field_->tileSum()) {
                //     std::cout<<highScore_<<' '<<field_->tileSum();
                //     std::cout << "The end! You won..." << std::endl;
                //     gameRunning_ = false;
                //     game_.changeState(new EndGameState());
                
            }

            if (snake_->isDead()) {
                std::cout << "The end! You are dead..." << std::endl;
                gameRunning_ = false;
                game_.changeState(new EndGameState());
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
        gameView.setViewport(sf::FloatRect(0.f, 0.3f, 0.7f, 0.7f));
        webcamView.setViewport(sf::FloatRect(0.7f, 0.f, 0.5f, 0.5f));
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
        window.draw(webcamSprite_);

        window.display();
    }
    else{
        window.setView(window.getDefaultView());
        pausestate_.draw(window);
    }
}