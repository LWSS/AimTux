# This is a public fork of Fuzion, if security is an issue for you, then you shouldn't use this fork. 
[![Join the chat at https://gitter.im/Aimtux-Fuzion/Lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://gitter.im/Aimtux-Fuzion/Lobby#)

Want to chat or play with other Fuzion users? Join us on Gitter!


## What is Fuzion?

A fully featured internal hack for * CounterStrike: Global Offensive* written in C++.

## What is Zedeion?

A fork of Fuzion, which heavily focuses on HvH. The legit bot will shortly be removed.
The hack is completely compatible with Fuzion. So, your configs can be still used here.


## Compiling

**Note:** _Do NOT download or compile as the root user._

#### Download the dependencies required to build Fuzion:

If you are having problems compiling make sure you've got the latest version of `g++`.

[How to update g++](https://github.com/AimTuxOfficial/AimTux/wiki/Updating-your-compiler)

==================

__Ubuntu-Based / Debian:__
```bash
sudo apt-get install cmake g++ gdb git libsdl2-dev zlib1g-dev patchelf
```
__Arch:__
```bash
sudo pacman -S base-devel cmake gdb git sdl2 patchelf
```
__Fedora:__
```bash
sudo dnf install cmake gcc-c++ gdb git libstdc++-static mesa-libGL-devel SDL2-devel zlib-devel libX11-devel patchelf
```

===================

#### Download Zedeion:

```bash
git clone --recursive https://github.com/Zedespook/Zedeion
```

```bash
cd Zedeion
```

===================

#### Compile with the build script

You can build easily with the included build script.
```bash
./build
```

You can later update with 
```bash
./update
```


## Injecting using the load script

First of all, make sure CS: GO is open, it does not matter whether you are in-game or not. However, it is not recommended to inject while CS: GO is loading into a map. 

Navigate to the directory where Zedeion was built if you have not ready.
```bash
cd Zedeion
```

Now, you can inject the hack with the `load` script
```bash
./load
```

You might be prompted to enter in your password, this is because the injection script requires root access.

The text printed out during injection is not important. 

If the injection was successful you will see a message at the bottom saying `Successfully injected!`, however, if the message says `Injection failed`, then you've most likely done something wrong.

Now, go back into CS: GO, if you are in the main menu of the game you should see a banner in the top left like so:

![this](http://i.imgur.com/Gb0SV1u.png)

*Note:* if you are getting crashes ( that are unrelated to game updates ) Try disabling shader precaching in your Steam Client -> Steam -> Settings -> Shader Pre-Caching. 

## Using the hack

Now that Fuzion has been injected into the game, press <kbd>Insert</kbd> on your keyboard to open the hack menu (<kbd>ALT</kbd>+<kbd>I</kbd> if you are using a laptop).

If you want to change skins, create and load configs or open the player list, you can find those buttons at the top of the screen.


## Unloading the hack

If you wish to unload the hack from the game, you can do so by entering the command:
```bash
./uload
```

## Configs

Configs are stored in a hidden directory in your home folder. Specifically 
```
~/.config/Fuzion
```

Each `config.json` is stored in a separately named folder (The name you see in-game, in the config window). 

To add a config, create a folder inside of the `~/.config/Fuzion` folder with a name of your choice, and paste the `config.json` inside of that folder.

To see hidden folders inside your home folder, press <kbd>CTRL</kbd>+<kbd>H</kbd> when using a file manager.

On your command line, you can also add the -a flag on `ls` e.g.
```bash
ls -la ~/
```


## Grenade Configs

```
~/.config/FuzionGH
```

Each `config.json` is stored in the folder named after the map name.

To add a config, copy the folder containing it to `~/.config/FuzionGH`


## Screenshots

![aimbot](http://i.imgur.com/NhSEO9W.png)
![menu](http://i.imgur.com/59TGPfw.png)
![esp](http://i.imgur.com/lnF42Ng.png)


## Credits

Special thanks to the Original AimTux project: [https://github.com/AimTuxOfficial/AimTux](https://github.com/AimTuxOfficial/AimTux).

Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin-changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) GitHub page.).

Also, thank you [@LWSS](http://www.github.com/LWSS/) for providing us with source-code to create something for our own satisfaction. This project of mine, couldn't be done without you and your community!

This project was also originally based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
