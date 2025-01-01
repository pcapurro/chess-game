# Welcome to chess-game!

### Here is my first game project: a feature-complete chess engine and chess game written from scratch, along with a user interface.

<br/>

The project has been created for Linux only and requires the following packages:

```
libsdl2-dev stockfish
```

Use `make` to compile the classic version of the game. Type `./chess-game` to launch.

Use `make shell` to compile a shell version of the game. Type `./shell-chess` to launch. You can specify `blind-mode` to play without the terminal board.

<br/>

**In both versions**: 

You can specify `--sandbox` to play against yourself. Otherwise, you will play by default against Stockfish (elo randomly set between 1 400 and 2 000).

At the end of a game, a summary is written in algebraic notation in the terminal.

<br/>

**In classical version**:

Use `LMB` on the right bottom corner to switch the colors of the board, or on the left side of the board to enable/disable the score bar.

You can use `RMB` to enable visual coordinates indicator on the board.

Use `LMB` on the right top corner of the window to restart the game. When a game is over, you can also use `Enter`.

You can use `Escape` key to quit the game or simply click the cross in the window.

A secret key sequence can unlock an easter egg if typed during a game.

<br/>

**In shell version**:

Type the move you want to play using algebraic notation (e.g.: 'e4', 'e4-e5', 'Bc4', 'Nf3xg5', 'Qh5xf7#').

Write `end` to end the game and shut down the program.

<br/>

> [!NOTE]
> The chess pieces textures have been downloaded from Wikimedia Commons and are under the Creative Commons license, originally made by the user Cburnett.
>
> All the others assets have been made by myself from scratch using GIMP software.
