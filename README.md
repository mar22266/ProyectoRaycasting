# Raycaster Game

## Table of Contents
- [Demo](#demo)
- [Description](#description)
- [New Features](#new-features)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [How to Build and Run](#how-to-build-and-run)
- [Controls](#controls)

## Demo
![Raycaster Gameplay Demo](VideoDemo/Raycasting.gif)

## Description
This Raycaster game is developed using C++ and the SFML library. It features a versatile 2D/3D rendering mode, dynamic object handling, and an integrated level editor for creative gameplay experiences.

## New Features
- **Enhanced Textures**: Added different wall textures, along with detailed textures for the sky and floor.
- **Map Creation and Editing**: Players can create their own maps, save them, upload them, and edit them using the integrated level editor.
- **Enhanced Sprites**: Introduced three different sprites in the `test.map`, which is the main map created for initial gameplay.
- **Toggleable Game Modes**: Implemented a game mode and an editor mode. Initially, upon loading a map, the game starts in editor mode. Pressing `Shift` + `~` toggles the game mode on, enabling sprite movement with collision detection. Pressing the same keys again returns the game to editing mode.

## Requirements
- **SFML**: Used for rendering, window management, etc.
- **ImGui-SFML**: Used for GUI features within the game.

## Project Structure
- **`main.cpp`**: The entry point of the game.
- **`include/`**: Contains all the header files.
- **`src/`**: Contains all source files.
- **`assets/`**: Contains game textures and sprites.

## How to Build and Run
1. **Install Dependencies**: Ensure you have SFML and ImGui-SFML installed on your system.
2. **Clone the Repository**: `https://github.com/mar22266/ProyectoRaycasting.git` then `cd ProyectoRaycasting`
3. **Build the Project**: `make`
4. **Clean the Build Files**: `make clean`


## Controls
Control the game using the following keys:
- **`ESC`**: Toggle between game and editor modes.
- **`Tab`**: Switch between 2D and 3D views.
- **Movement Keys**:
- **`W`**: Move forward
- **`A`**: Move left
- **`S`**: Move backward
- **`D`**: Move right
- **Rotation Keys**:
- **`Left Arrow`**: Rotate left
- **`Right Arrow`**: Rotate right
- **Toggle Game Mode**:
- **`Shift` + `~`**: Toggle between playing and editing modes.


