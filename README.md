*This project has been created as part of the 42 curriculum by beergin, kikiz.*

# cub3D

## Description

cub3D is a small 3D game engine inspired by the classic game Wolfenstein 3D.  
The goal of this project is to explore the concept of ray-casting and create a realistic first-person view inside a maze using the MiniLibX graphics library.

The program parses a scene description file (`.cub`) which defines:
- Wall textures (North, South, East, West)
- Floor and ceiling colors
- A map composed of walls and empty spaces
- The player's starting position and orientation

The engine renders the scene in real time and allows the player to navigate through the maze using keyboard controls.

This project focuses on:
- Graphics programming
- Ray-casting algorithms
- File parsing
- Memory management
- Event handling
- Mathematical computations for 3D projection

---

## Features

- Real-time 3D rendering using ray-casting
- Different wall textures for each direction (N, S, E, W)
- Customizable floor and ceiling colors
- Map validation (closed map required)
- Keyboard controls for movement and rotation
- Clean exit handling (ESC key and window close button)

---

## Instructions

### Requirements

- GCC or Clang compiler
- MiniLibX
- Unix-based OS (Linux or macOS)

---

### Compilation

Clone the repository and compile the project using:

```bash
make
```

To clean object files:

```bash
make clean
```

To remove all compiled files:

```bash
make fclean
```

To recompile everything:

```bash
make re
```

---

### Execution

Run the program with a `.cub` map file as argument:

```bash
./cub3D maps/map.cub
```

Example:

```bash
./cub3D example.cub
```

---

## Controls

- `W` : Move forward  
- `S` : Move backward  
- `A` : Move left  
- `D` : Move right  
- `←` / `→` : Rotate camera left / right  
- `ESC` : Exit the program  
- Window close button (X) : Exit the program  

---

## Map Format (.cub)

The scene file must contain:

### Texture paths
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
```

### Colors
```
F 220,100,0
C 225,30,0
```

### Map (last part of the file)
```
111111
100001
1000N1
111111
```

Legend:
- `1` : Wall  
- `0` : Empty space  
- `N`, `S`, `E`, `W` : Player starting position and orientation  

The map must be fully surrounded by walls, otherwise the program will exit with an error.

---

## Error Handling

If any configuration error is found in the `.cub` file (invalid map, missing textures, wrong colors, etc.), the program exits with:

```
Error
<custom error message>
```

---

## Resources

- Wolfenstein 3D (1992) – Inspiration for ray-casting
- MiniLibX documentation
- Ray-casting tutorials:
  - https://lodev.org/cgtutor/raycasting.html
  - https://permadi.com/1996/05/ray-casting-tutorial/

### AI Usage

AI tools were used only for:
- Understanding ray-casting concepts
- Clarifying parsing logic
- Debugging explanations

All generated content was reviewed, understood, and adapted manually before integration into the project.

---

## Author

- beergin
- kikiz
