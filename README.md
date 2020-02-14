# Android Multiplayer Physics Engine (Demo)
 AMP stands for Android, Multiplayer and Physics.
 This engine is currently under development, so not all features are already existing yet.
 The finished engine will allow the creation of mobile games with similar game mechanics to Angry Birds.
 Physic based games with a strong multiplayer component are targeted with the feature complete engine.
## Current Major Features
- Android Rendering
- Post Processing
- Physics
## Upcoming Features
- Animation System
- Networking
- Documentation
## Required Software 
- Visual Studio 2019 (recommended)
- Microsoft Visual C++ Cross-Platform Mobile Development Extension (Visual Studio)
## Packaging
After opening the `AMP_Game_Engine.sln` file in Visual Studio, set the `Android/GamePackaging` project as start up project.
Now you can select your targeted solution platform (`ARM, ARM64, x86, x64`). You can also use USB-Debugging by connecting
your device and installing your device USB-Drivers. You can find the generated `.apk` in the following file path:
`.../Code/AMP/Android/GamePackaging/(Solution Platform)/(Solution Configuration)/AMP.apk`
(e.g : `Code/AMP/Android/GamePackaging/ARM/Release/AMP.apk`)
