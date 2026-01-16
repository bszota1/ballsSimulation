## Bouncing Balls Simulator
A 2D physics simulation built with C++ and SFML 3. The project simulates multiple balls moving within a bounded window, featuring elastic collisions between balls and realistic bouncing off the walls.

## Features
1. Physics-based Collisions: Implements elastic collision logic between balls, taking into account their mass (weight) and velocity.

1. Dynamic Generation: Automatically calculates ball sizes based on the window area and the desired number of balls to prevent overcrowding.

1. Customizable Quantity: Users can specify the number of balls via command-line arguments.

1. SFML 3 Integration: Utilizes modern SFML 3 features, including the new event handling system and angle types.

1. Randomized Properties: Every ball is generated with a random color, initial velocity, and weight.

## Project Structure
1. src/main.cpp: The entry point of the application. Handles the window lifecycle and the main simulation loop.

1. include/ball.h: Defines the Ball data structure containing physical properties like position, velocity, and weight.

1. include/ballsEngine.h: The core logic engine. Handles movement, wall collisions, and inter-ball collision physics.

1. CMakeLists.txt: Configuration file for building the project with CMake.

## Prerequisites
Before building the project, ensure you have the following installed:

1. C++17 Compiler (or newer).

1. CMake 3.25 or higher (Note: Your CMakeLists.txt specifies version 4.1, but version 3.25+ is standard for SFML 3).

1. SFML 3: Ensure SFML 3 is installed on your system.

On macOS (Homebrew): brew install sfml.

On Linux: Use your package manager or build from source.

## Building the Project
Clone or download the project to your local machine.

Open a terminal in the project root directory and run:

```Bash
mkdir build
cd build
cmake ..
make
```
Usage
You can run the simulator by executing the binary. You can optionally provide the number of balls as an argument:

# Run with default (15 balls)
``` Bash
./bouncingBalls
```
# Run with 50 balls
```Bash
./bouncingBalls 50
```
## Controls

1. Close Window: Click the 'X' or close the window to exit the simulation.

1. Physics: Balls will automatically bounce off the edges of the 1200x1000 window and react to each other upon impact.

## Implementation Details
1. The simulation uses a Normal Impulse method for collisions:

1. Wall Collisions: When a ball hits a boundary, its velocity on that axis is inverted.

1. Ball Collisions: The engine calculates the collision normal and relative velocity to apply an impulse based on the weights of the two colliding balls, ensuring momentum is preserved.

1. Overlap Correction: To prevent balls from getting stuck inside each other, a static separation is applied immediately after a collision is detected.