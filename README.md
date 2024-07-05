# SFML Snake Game

## Description
This is a classic Snake game developed using the Simple and Fast Multimedia Library (SFML) in C++. The player controls a snake that moves around the screen, eating food to grow longer. The objective is to eat as much food as possible without colliding with the walls or the snake's own body.

## Features
- Classic Snake gameplay.
- Smooth animations using SFML.
- Increasing difficulty as the snake grows longer.
- Simple and intuitive controls.

# Image

![](https://github.com/Ali-Ch-001/Snake/assets/108975862/e34bc995-70b9-473d-83b8-6a5ab3e737ca)


## Requirements
- SFML
- C++
- CMake

## Installation
To build and run this project, you need to have SFML and CMake installed on your system.

### Install SFML
You can download SFML from the official website: [SFML Downloads](https://www.sfml-dev.org/download.php)

Alternatively, you can install it using a package manager:
- On Ubuntu:
  ```bash
  sudo apt-get install libsfml-dev
  ```
- On macOS:
  ```bash
  brew install sfml
  ```

### Install CMake
You can download CMake from the official website: [CMake Downloads](https://cmake.org/download/)

Alternatively, you can install it using a package manager:
- On Ubuntu:
  ```bash
  sudo apt-get install cmake
  ```
- On macOS:
  ```bash
  brew install cmake
  ```

## Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/Ali-Ch-001/SFML-Snake-Game.git
   ```
2. Navigate to the project directory:
   ```bash
   cd SFML-Snake-Game
   ```
3. Create a build directory and navigate to it:
   ```bash
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
5. Build the project using make:
   ```bash
   make
   ```

## Usage
1. After building the project, you can run the game executable:
   ```bash
   ./SFML-Snake-Game
   ```

### Controls
- Use the arrow keys to move the snake.
- Avoid colliding with the walls and the snake's own body.
- Eat the food to grow longer and score points.

## Contributing
Contributions are welcome! If you have any suggestions, bug reports, or improvements, please create an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-branch
   ```
3. Commit your changes:
   ```bash
   git commit -m "Description of your changes"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-branch
   ```
5. Create a new pull request.
