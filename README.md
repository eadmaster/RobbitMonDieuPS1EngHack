# Robbit Mon Dieu English Translation

My attempt at an English hack for the PS1 game Robbit Mon Dieu.


## Current status  🏗️

 - Translated most of the menus
 - Translated only the briefing of the 1st mission
 - Gfx text/buttons are NOT translated


## Preview  👀

<img width="40%" height="40%" alt="demo1" src="https://raw.githubusercontent.com/eadmaster/RobbitMonDieuPS1EngHack/refs/heads/main/shots/demo1.png">  <img width="40%" height="40%" alt="demo2" src="https://raw.githubusercontent.com/eadmaster/RobbitMonDieuPS1EngHack/refs/heads/main/shots/demo2.png">  <img width="40%" height="40%" alt="demo3" src="https://raw.githubusercontent.com/eadmaster/RobbitMonDieuPS1EngHack/refs/heads/main/shots/demo3.png">


## Patch instructions  🩹

1. Obtain a game image matching [these hashes](http://redump.org/disc/7227/), and extract it
2. Grab the latest xdelta patch from the [Releases section](https://github.com/eadmaster/RobbitMonDieuPS1EngHack/releases).
3. Visit [Rom Patcher JS](https://www.marcrobledo.com/RomPatcher.js/)
4. Select `Robbit mon Dieu (Japan).bin` as ROM file
5. Select `.xdelta` as Patch file
6. Click "Apply patch" and save in the same folder without changing the filename: `"Robbit mon Dieu (Japan) (patched).bin`
7. Download and use this cue sheet to play the game:

```
FILE "Robbit mon Dieu (Japan) (patched).bin" BINARY
  TRACK 01 MODE2/2352
    INDEX 01 00:00:00
```

# Credits/Contributors/Special thanks  🤝

 - [C0mposer](https://github.com/C0mposer) for the [C/C++ Game Modding Utility](https://github.com/C0mposer/C-Game-Modding-Utility)