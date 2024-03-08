![Logo](https://img.itch.zone/aW1nLzE1MTY4MDE4LnBuZw==/original/CDpOiF.png)

Thank you for visiting the GitHub repository! Here you can find the full code for the game (some parts are ugly as hell because this game was made for a Game Jam and I wanted to make sure I made it on time).

Please, feel free to visit the [Issues section](https://github.com/MascaChapas27/AlchemyTogether/issues) if you have any problem that needs to be solved. If you want to download the latest version, go to the [itch.io page](https://mascachapas27.itch.io/alchemy-together), or go to [Releases](https://github.com/MascaChapas27/AlchemyTogether/releases) and choose the latest one (the one at the top).

# Compiling on Linux

In order to compile the program on any Linux machine, follow these instructions:

## 1. Install everything you need

In order to compile Alchemy Together you need the following programs:

1. git
2. g++
3. make

The installation method depends on the distribution. Try running those commands on `bash`. You might have them installed, or maybe you won't and a line will be displayed, telling you how to install them.

If this line doesn't appear, you usually just need to type:

```bash
sudo apt install git
```
(On Fedora machines, instead of `apt` write `yum`).

## 2. Clone the project

Use the following command to copy the contents of the repository to your machine:

```bash
git clone https://github.com/MascaChapas27/AlchemyTogether
```

Once the cloning is done, type the following command to navigate to the directory:

```bash
cd AlchemyTogether
```

## 3. Check constants

In `Utilities.hpp` there are three constants that change the way the game is displayed:

```cpp
// Activar para ver las hitboxes
const bool DEBUG = false;

// Activar para poner el idioma a español
const bool SPANISH = true;

// Activar para poner los controles de la recreativa y
// otros assets (el idioma será español aunque SPANISH sea false)
const bool RECREATIVA = true;
```

The most important here is `SPANISH`. Set it to `true` if you want the game to be in Spanish or `false` if you want it in English. Also, make sure `RECREATIVA` is set to `false` if you want to play on PC.

## 4. Compile the project

Type `make` to compile the project. If something bad happens, error messages will appear. Please, go to the [Issues section](https://github.com/MascaChapas27/AlchemyTogether/issues), click on the "New Issue" button and paste the message. I would also appreciate it if you told me what distribution you are using and which version.

## 5. Run the project

Type `make run` to execute the program. It should work if there were no compilation errors during step 3, but anything could happen. Again, if it doesn't work, you can create an Issue and paste the error message you got.

## Typical errors

Sometimes the project will compile properly but won't run because a resource cannot be found. Please make sure that the structure of the project is exactly the same as in the repository: if you change names or move files you may screw everything!!
