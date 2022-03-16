# Space_Invaders
Space Invaders style game for a C/C++ programming class at Beijing Institute of Technology, using SFML.

![Gameplay Screenshot](https://www.luigipizzolito.com/InfiniGalactica/readme/Screenshot%202022-03-10%20at%2014.03.43.png)

## Running the executables
Pre-compiled binary executables can be found in the releases or in the `bin` folder for each respective platform, just execute.

---
- [Space_Invaders](#space_invaders)
  - [Running the executables](#running-the-executables)
  - [Application Components](#application-components)
  - [Directory Structure](#directory-structure)
  - [Dependencies](#dependencies)
  - [Compiling](#compiling)
    - [On Windows](#on-windows)
    - [On MacOS](#on-macos)
    - [On Linux](#on-linux)
- [General Framework](#general-framework)
  - [How to do it?](#how-to-do-it)
  - [Technical aspects of the project](#technical-aspects-of-the-project)
  - [How easy is to access and use our source code?](#how-easy-is-to-access-and-use-our-source-code)
  - [For Windows](#for-windows)
  - [For UNIX-based systems (MacOS and Linux)](#for-unix-based-systems-macos-and-linux)
- [External Dependencies](#external-dependencies)
  - [SFML(Simple and Fast Multimedia Library)](#sfmlsimple-and-fast-multimedia-library)
  - [SFML and OpenGL](#sfml-and-opengl)
  - [Nlohmann/json](#nlohmannjson)
  - [Resources](#resources)
- [Key Algorithms and Data Structures](#key-algorithms-and-data-structures)
  - [The Source Code](#the-source-code)
  - [Application layer](#application-layer)
  - [Game Layer: Extends Application](#game-layer-extends-application)
  - [Scene Manager](#scene-manager)
  - [Text Manager](#text-manager)
  - [Text Panel](#text-panel)
  - [Entities](#entities)
  - [Physics Entity](#physics-entity)
  - [Player: Extends Physics Entity](#player-extends-physics-entity)
  - [Enemy](#enemy)
  - [Simple Algorithm to spawn enemies](#simple-algorithm-to-spawn-enemies)
  - [Projectiles](#projectiles)
  - [Spawning projectiles](#spawning-projectiles)
  - [Algorithms:](#algorithms)
  - [Camera Follow](#camera-follow)
  - [Starfield Background](#starfield-background)
  - [Starfield Background – Batch Rendering](#starfield-background--batch-rendering)
  - [Utilities](#utilities)
  - [Math Utilities](#math-utilities)
      - [Example](#example)
  - [Collisions](#collisions)
  - [Entity and projectile deletion](#entity-and-projectile-deletion)
- [Current Prototypes](#current-prototypes)

---
## Application Components
![Class Diagram](https://www.luigipizzolito.com/InfiniGalactica/readme/Class%20Diagram%20-%20InfiniGalactica.drawio_dark.png)

## Directory Structure
```
Space_Invaders
├── Dependencies
│   ├── include
│   │   ├── SFML
│   │   └── json.hpp
│   ├── lib
│   │   └── Windows Libs.lib
│   └── lib-darwin
│       └── Mac Libs.dylib
├── Makefile
├── Project\ Generator.bat
├── README.md
├── Space_Invaders
│   ├── res
│   │   ├── Novel
│   │   │   ├── LanaPixel.ttf
│   │   │   ├── Scenes
│   │   │   │   └── scene1.json
│   │   │   └── controllerbuttons.html
│   │   └── Sprites
│   │       ├── brokenscreen.png
│   │       ├── bullet.png
│   │       ├── enemy.png
│   │       ├── player.png
│   │       ├── player2.png
│   │       └── stars.png
│   └── src
│       ├── Algorithms
│       │   ├── CameraFollowScroll.cpp
│       │   ├── CameraFollowScroll.h
│       │   ├── MathUtils.cpp
│       │   ├── MathUtils.h
│       │   ├── StarField.cpp
│       │   ├── StarField.h
│       │   ├── Utilities.cpp
│       │   └── Utilities.h
│       ├── Application
│       │   ├── Application.cpp
│       │   ├── Application.h
│       │   ├── BasicNovel.cpp
│       │   ├── BasicNovel.h
│       │   ├── BasicShooter.cpp
│       │   └── BasicShooter.h
│       ├── Entity
│       │   ├── Enemy.cpp
│       │   ├── Enemy.h
│       │   ├── Entity.cpp
│       │   ├── Entity.h
│       │   ├── PhysicsEntity.cpp
│       │   ├── PhysicsEntity.h
│       │   ├── Player.cpp
│       │   └── Player.h
│       ├── Projectiles
│       │   ├── Projectile.cpp
│       │   └── Projectile.h
│       ├── SceneManager
│       │   ├── TextManager.cpp
│       │   ├── TextManager.h
│       │   ├── TextPanel.cpp
│       │   └── TextPanel.h
│       └── Scenes
│           └── BasicTest.cpp
├── bin
│   └── Platform Releases
├── premake5.lua
└── vendor
    └── bin
        └── premake
            ├── License.txt
            └── premake5.exe
```
## Dependencies
- SFML
- nlohmann/json

## Compiling
### On Windows
1. Install Visual Studio 2019
2. Run `Project Generator.bat`
3. Open the VS2019 project generated.
4. Compile and run.

### On MacOS
1. Make sure you have Clang/G++ and make installed.
2. `git clone` and `cd` into this directory.
3. run `make`.
### On Linux
1. Make sure you have G++ and make installed.
2. Download binary SFML release for Linux.
3. Reconfigure Makefile to include SFML.
4. run `make`.


# General Framework

## How to do it?
Base our project on the standards of not only the game industry but the programming market in general for:
- A realistic planning for the components of the game(including, but not limited to the code)
- The use of solid code and good practices

## Technical aspects of the project

As stated before, we want our game to be multiplatform, as you might have guessed that requires writing code in a more “general way”, which means taking in consideration how different OSs react to certain practices, or the probable absence of certain third-party libs.

We have dealt with these sort of issues and  since the two main programmers use different OSs we came up with two different building systems.

## How easy is to access and use our source code?
Using a text editor is fine, some are better than others, such as visual studio code(a text editor on steroids ), still so many of us prefer using IDEs, usually for productiveness or comfort. 

But there are many different IDEs, some of them are multiplatform, while others are platform dependent.

My preferred IDE is Visual Studio, but since I know many developers might use a different IDE, my main task was making sure that any programmer using windows will be able to just download the source code and with one click get the set up done.

## For Windows
- The solution is pretty simple, although Lua is more than just a “scripting” , it is surely a good choice for it.

- With the creation of a script, we can specify all of the details our computer needs in order not to only generate a project file for some IDE, but to set configuration intended for the project based on your OS, build, programming language , etc.

## For UNIX-based systems (MacOS and Linux)
- Uses the ”make” build system which is an industry standard.
- Most UNIX-based systems come with g++ (GNU C++ Compiler) pre-installed, as well as make.
- User can compile and launch the source code by simply typing “make” into the terminal.
- Makefile specifies configurations.

![Picture1](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture1.png)

![Picture2](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture2.png)

# External Dependencies 

## SFML(Simple and Fast Multimedia Library)
The reasons for our choice  :
1. SFML is multi-media
2. SFML is multi-platform
3. SFML is multi-language

![logo](https://www.luigipizzolito.com/InfiniGalactica/readme/logo.png)

## SFML and OpenGL
SFML is an OpenGL based library, however it has some characteristics differences that any programmer intending to use it must know

The reference frames a different

SFML is only officially supports 2D, however as programmers if we know the basis of the library, we can implement any feature/concept that we need, whether it is the use of Entities in the world, batch rendering, or even 3D, anything is possible .

Of course, if you use OpenGL, you might be used to creating your own data structures, writing shaders, and communicating with your GPU, in a more “lower-level” way.

## Nlohmann/json
- Modern JSON library for C/C++

- Allows near-native integration between C/C++ datatypes and JSON.

- Used to read and parse dialog/script files.

 ![Picture3](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture3.png)

 ## Resources

 - 2D textures
- Default SFML internal shader
- 8-bit Font
- JSON files with dialogs

# Key Algorithms and Data Structures

## The Source Code
Scenes:

Using a scene structured system, and a base application class, we were able to decouple/separate the client(user) from the application side(to keep it simple SFML and our data structures), this way it is easy to refactorize and maintain our code.
![Picture4](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture4.png)

## Application layer
Application is the base of the game, it deals with the set up for the window and the callbacks, also defines the basic methods that are indispensable for any game.

## Game Layer: Extends Application
The Game for the time being, the Game class manages the whole game components and its logic, however this is subject to change in the following days after the implementation of the scene manager.

Ideally the Game layer should only help the application layer to set up the base components, call the fundamental functions that let the game run, and communicate with the scene manager to create an instance of the scene/level of interest.

## Scene Manager
- Loads game level scene data.
- Creates corresponding elements; Enemies, Dialogs, Game state settings, etc
- Manage switching between levels / restarting levels on death etc.
- Manages level/scene specific game logic.
- Still to be implemented

## Text Manager
- Handles entire text/dialog scenes.
- Load script from JSON file.
- Create array of TextPanel elements, one per dialog item in the script.

![Picture5](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture5.png)

## Text Panel
- Algorithim to calculate the line width and line wrapping for text;
  -   Where to start a new line.
  -   Where to split text across multiple panels.
- Renders text boxes and text.
- Does the text display animation and handles user input for skipping/next.

    ![Picture6](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture6.png)

## Entities
The basic idea of an entity is any object that occupies some portion of the game world space.

Since our game is a 2D shooter, we weren’t so strict with the members contained in the entity(if it was a game engine, we would probably add members such as the HP and speed on the next layer)

![Picture7](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture7.png)

## Physics Entity
- Extends the entities class, adding physics to the entity movement
- Simulates forces, acceleration, and velocity.
Provides new way to move entity: applyForce(vec2)
- Used for the player entity

![Picture8](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture8.png) 

## Player: Extends Physics Entity
- The player defines members that will influence its physics, also redefined some prototype functions declared in the Entity class
- Contains Setters and Getters that are fundamental
- Receives the player Input and reacts accordingly 

![Picture9 ](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture9.png)

## Enemy

The enemy is an entity that behaves based on its own rules, its main objective is to kill the player.
Since we are using a simple orthographic projection for 2D graphics, algorithm for generating enemies is quite simple, we just make use of the viewport's movement  and the dimensions of the window.

 ![Picture10](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture10.png) 

 ## Simple Algorithm to spawn enemies
 ![Picture11](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture11.png)
 ![Picture12](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture12.png)

 ## Projectiles
They collide with the enemies and the player.
The projectiles define similar members to the ones of any entity except from HP, they can also inflict damage upon collision.
![Picture13](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture13.png)

## Spawning projectiles
Both the enemies and the player can shoot projectiles.

So, how do we spawn them?Are they children of the entity that called them? 
If we were using a node base game engine, we would probably use the parent node transforms(scale,rotation and translation) in order to the the transform of the projectile, then reparent it, however this is not needed.
![Picture14](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture14.png)

## Algorithms:
1. Camera Follow
2. Starfield Background
3. Utilities 
4. Math Utilities
5. Collisions
6. Entity and Projectile Deletion

## Camera Follow
- Moves camera along the world at a constant speed.
- Keeps player moving in bounds with the camera.
- Moves faster if player wants to rush ahead; the player can push the camera forwards.
- Ensures the game progresses.

![Picture15](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture15.png)

## Starfield Background
- Creates a dynamic illusion of 3D for the background; random stars.
- Uses the parallax effect alogrithim.
  - 8 different layers of stars
  - Each layer has a different speed / relative shift.
- Implements batch-rendering algorithim; to draw all stars as a single efficient VertexArray per layer.

![Picture16](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture1.png)
![Picture17](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture17.gif)

## Starfield Background – Batch Rendering
![Picture18](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture18.png)

![Picture19](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture19.tif)

![Picture20](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture20.png)

## Utilities
Timers and Spawners are important, they can be used for debugging purposes, or for the gameplay

![Picture21](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture21.png)
![Picture22](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture22.png)

 ## Math Utilities
 We all know how to calculate these quantities, however, if we type the formulas too often, it means we are doing something wrong, in order to make our code more reader friendly, and easier for us, we should automatize the most important formulas. 

![Picture23](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture23.png)

#### Example

![Picture24](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture24.png)

## Collisions
Collisions are simple, whether they are in 2D or 3D and there are different methods to check for collisions

If two AABB intersect, then for the projection of each dimension for the AABB1 there will be an overlapping section of the AABB2

If we let v1, be the vector whose components are the distances of from the origin of one AABB to the other one, if the sum of the half sizes in each dimension is bigger than its respective component of D, then the two AABB intersect.

![Picture25](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture25.png)

![Picture26](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture26.png)

## Entity and projectile deletion
The collisions of the game are only between the player and the enemy bullets, and the enemies with the player bullets, just for simplicity and to avoid double checking some cases.

Upon collision we check the state of the entity/projectile, if the given entity has a HP<=0 then it is dead, hence it is deleted, simultaneously the projectiles that collided with it will also be deleted.
 
 ![Picture27](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture27.png)

 # Current Prototypes

 ![Picture28](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture28.png)

 ![Picture29](https://www.luigipizzolito.com/InfiniGalactica/readme/Picture29.png)




















