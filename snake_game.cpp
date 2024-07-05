#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct SnakeSegment {
    int x;
    int y;
};

class Snake {
public:
    Snake() {
        direction = RIGHT;
        segments.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});
        score = 0;
    }

    void move() {
        SnakeSegment newSegment = segments.front();
        switch (direction) {
            case UP:
                newSegment.y -= 1;
                break;
            case DOWN:
                newSegment.y += 1;
                break;
            case LEFT:
                newSegment.x -= 1;
                break;
            case RIGHT:
                newSegment.x += 1;
                break;
        }
        segments.push_front(newSegment);
        if (!ateFood) {
            segments.pop_back();
        } else {
            ateFood = false;
        }
    }

    void changeDirection(Direction newDirection) {
        if (segments.size() > 1) {
            SnakeSegment& head = segments.front();
            SnakeSegment& neck = *(++segments.begin());
            if ((newDirection == UP && head.y + 1 != neck.y) ||
                (newDirection == DOWN && head.y - 1 != neck.y) ||
                (newDirection == LEFT && head.x + 1 != neck.x) ||
                (newDirection == RIGHT && head.x - 1 != neck.x)) {
                direction = newDirection;
            }
        } else {
            direction = newDirection;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& segment : segments) {
            sf::RectangleShape rect({CELL_SIZE, CELL_SIZE});
            rect.setPosition(segment.x * CELL_SIZE, segment.y * CELL_SIZE);
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);
        }
    }

    bool checkCollision() {
        SnakeSegment& head = segments.front();
        for (auto it = ++segments.begin(); it != segments.end(); ++it) {
            if (head.x == it->x && head.y == it->y) {
                return true;
            }
        }
        return head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT;
    }

    void eatFood() {
        ateFood = true;
        score++;
    }

    int getScore() const {
        return score;
    }

    const SnakeSegment& getHeadPosition() const {
        return segments.front();
    }

private:
    Direction direction;
    std::deque<SnakeSegment> segments;
    bool ateFood = false;
    int score;
};

class Food {
public:
    Food() {
        respawn();
    }

    void respawn() {
        position.x = rand() % GRID_WIDTH;
        position.y = rand() % GRID_HEIGHT;
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape rect({CELL_SIZE, CELL_SIZE});
        rect.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);
    }

    const SnakeSegment& getPosition() const {
        return position;
    }

private:
    SnakeSegment position;
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window({SCREEN_WIDTH, SCREEN_HEIGHT}, "Snake Game");
    window.setFramerateLimit(10);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return EXIT_FAILURE;
    }

    Snake snake;
    Food food;
    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        snake.changeDirection(UP);
                        break;
                    case sf::Keyboard::Down:
                        snake.changeDirection(DOWN);
                        break;
                    case sf::Keyboard::Left:
                        snake.changeDirection(LEFT);
                        break;
                    case sf::Keyboard::Right:
                        snake.changeDirection(RIGHT);
                        break;
                    default:
                        break;
                }
            }
        }

        if (!gameOver) {
            snake.move();
            if (snake.checkCollision()) {
                gameOver = true;
            }
            if (snake.getHeadPosition().x == food.getPosition().x && snake.getHeadPosition().y == food.getPosition().y) {
                snake.eatFood();
                food.respawn();
            }
        }

        window.clear();
        snake.draw(window);
        food.draw(window);

        // Display score
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(snake.getScore()));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);

        // Display game over message
        if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over! Press R to restart.");
            gameOverText.setCharacterSize(36);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(SCREEN_WIDTH / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, SCREEN_HEIGHT / 2.0f - gameOverText.getGlobalBounds().height / 2.0f);
            window.draw(gameOverText);
        }

        window.display();

        // Restart the game if 'R' is pressed
        if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            snake = Snake();
            food.respawn();
            gameOver = false;
        }
    }

    return 0;
}
