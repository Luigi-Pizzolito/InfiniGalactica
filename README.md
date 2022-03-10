# Space_Invaders
Space Invaders style game for a C/C++ programming class at Beijing Institute of Technology, using SFML.

![Gameplay Screenshot](https://www.luigipizzolito.com/InfiniGalactica/readme/Screenshot%202022-03-10%20at%2014.03.43.png)

Note: The code has gone through a set of changes, hence some of the entries in our log might be outdated. The graphical evidence attached with the project belongs to the updated version of the project, however it surely relates the old entries of the log.

---
- [Space_Invaders](#space_invaders)
  - [Application Components](#application-components)
  - [Directory Structure](#directory-structure)
  - [Dependencies](#dependencies)
  - [Compiling](#compiling)
    - [On Windows](#on-windows)
    - [On MacOS](#on-macos)
    - [On Linux](#on-linux)
  - [Running the executables](#running-the-executables)

---
## Application Components
![Class Diagram](https://www.luigipizzolito.com/InfiniGalactica/readme/Class%20Diagram%20-%20InfiniGalactica.drawio_white.png)

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
3. Reconfigure Makefile.
4. 3. run `make`.

## Running the executables
Pre-compiled binary executables can be found in the releases or in the `bin` folder for each respective platform, just execute.