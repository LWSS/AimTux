<p style="float: left; padding-right:30px;">
    <img src="http://i.imgur.com/mCtrbIN.png" alt="logo" width="450" height="338"></p>
<hr style="visibility:hidden;" />

Want to chat or play with other Fuzion users? Join us on Gitter!

[![Join the chat at https://gitter.im/Aimtux-Fuzion/Lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://gitter.im/Aimtux-Fuzion/Lobby#)

---

## What is Fuzion?

Fuzion is a fully featured internal cheat for *CounterStrike : Global Offensive* written in C++.

## AUR Installation

* You can install Fuzion by using the AUR helper of your choice and installing the package [fuzion-git](https://aur.archlinux.org/packages/fuzion-git/).
* Load Fuzion by using the command `fuzion-load`
* Unload using `fuzion-unload`
* As a development package, it will automatically update when you trigger your AUR helper, if a new commit has been pushed.

<hr style="height:10px; visibility:hidden;" />

---

## Compiling Fuzion

**Note:** _Do NOT download or compile as the root user._

#### First, download the required dependencies:

__Ubuntu-Based / Debian:__
```bash
sudo apt-get install cmake g++ gdb git libsdl2-dev zlib1g-dev patchelf
```
__Arch Linux:__
```bash
sudo pacman -S gcc base-devel cmake gdb git sdl2 patchelf
```
__Fedora:__
```bash
sudo dnf install cmake gcc-c++ gdb git libstdc++-static mesa-libGL-devel SDL2-devel zlib-devel libX11-devel patchelf
```

---

#### Download the Fuzion source:

```bash
git clone --recursive https://github.com/LWSS/Fuzion
```

```bash
cd Fuzion
```

#### Compile with the build script

You can easily build with the included `build` script.
```bash
./build
```

You can later update with 
```bash
./update
```

---

## Injecting

To inject Fuzion, CS:GO must be open, but it does not matter what you are currently doing in-game. Try not to inject while loading into a map however, as this can make the game unstable or crash.

Ensure you are in the directory where Fuzion was built.

Inject Fuzion by executing the `load` script.
```bash
./load
```

**Note:** _Root priviledges are required for injection, and so you may be prompted to enter your password._

If Fuzion injected successfully, you will see the following message in the CS:GO console as well as in the terminal you injected from: `Successfully injected!`

If you see `Injection failed`, then you've most likely done something wrong. Make sure Fuzion compiled successfully.

If all is successful, you should see the following in the top left of your game:

![Fuzion indicator](http://i.imgur.com/Gb0SV1u.png)

## Using Fuzion

Now that Fuzion has been injected into the game, press <kbd>Insert</kbd> on your keyboard to open the Fuzion menu (<kbd>ALT</kbd>+<kbd>I</kbd> if you are using a laptop).

---

## Unloading Fuzion

If you wish to unload the cheat from your game, execute the `uload` script:
```bash
./uload
```

---

## Configs

Configuration files for Fuzion are stored in the following directory:
```
~/.config/Fuzion
```

Each `config.json` is stored in a seperately named folder, the name of this folder being the name of the config you will see in-game. 

To add a config, create a folder inside of the `~/.config/Fuzion` folder with a name of your choice, and paste the corresponding `config.json` inside of that folder.

**__Grenade Configs__** are stored inside `~/.config/FuzionGH`.

To add a grenade config, copy `config.json` to a folder named after the map the config was created for.

---

## Screenshots

![Aimbot Menu](http://i.imgur.com/NhSEO9W.png)
![Visuals Menu](http://i.imgur.com/59TGPfw.png)
![ESP Example](http://i.imgur.com/lnF42Ng.png)

## Credits

Special thanks to the Original AimTux project: [https://github.com/AimTuxOfficial/AimTux](https://github.com/AimTuxOfficial/AimTux).

Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.).

This project was also originally based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).

[telans](https://github.com/telans) for the AUR package [fuzion-git](https://aur.archlinux.org/packages/fuzion-git/)
