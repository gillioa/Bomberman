# Bomberman

A Bomberman clone written in C++ with OpenGL rendering, AI opponents, save/load and scores.

## Features
- 3D rendering through the GDL library (OpenGL 3.3)
- AI players driven by scripts (`IAScript/easy.ia`, `medium.ia`, `hard.ia`, `perso.ia`)
- Map files (`maps/*.bomber`) and a map generator
- Bonuses, bombs, save/load and score tracking
- Multithreaded engine (own `Thread`, `Mutex`, `ScopedLock` wrappers)

## Requirements
- Linux, `g++` with C++0x support
- OpenGL 3.3
- GDL and JsonCPP (bundled under `sources/GDL` and `sources/JsonCPP`)

## Build and run
```bash
make
export LD_LIBRARY_PATH="./sources/GDL/libs/:./sources/JsonCPP/"
./bomberman
```

## Layout
- `sources/`: engine, map, players, bombs, bonuses, IA, menu, load/save, serialization
- `maps/`, `IAScript/`, `assets/`, `sauvegarde/`, `scores/`

## Status
Archived, no further development planned.

## License
MIT