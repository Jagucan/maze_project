# Capstone Project ( Maze Game ).

<p align="center">
	<a href="https://imgur.com/9RR4sDk">
		<img src="https://i.imgur.com/9RR4sDk.png" title="source: imgur.com" width = "600px" height = "350px"/>
	</a>
</p>

## Context.

This project is part of the final project of the _Holberton Academy_, and it is a game that uses a 3D perspective through the use of the **SDL2 library** and the **raycasting technique**. The main objective of this game is to create an immersive experience for the player, where he will be able to explore a three-dimensional environment.

### Raycasting and SDL2.

**Raycasting** is a technique used in retro games like _Wolfenstein 3D_ to simulate 3D graphics in a 2D environment. It works by tracing rays from the player's position and calculating the distance to objects in the environment to generate a visual representation.

By using **SDL2**, a cross-platform input and graphics library, we are able to create a compelling graphical interface and allow players to interact with the game via keyboard or other supported input devices.

The main goal of this project is to explore the capabilities of _SDL2_ and _raycasting_ to create a functional 3D game. This involves implementing collision detection algorithms, rendering maps and objects, and designing levels.

## Requirements.

- Ubuntu 20.04+.
- C++ Compiler.
- SDL 2.0 (not SDL 1.2).
- Library SDL_Image.

## How to Install.

### For linux:

- If it is the first time you compile **The Maze Game**, use `make all` to install the libraries and/or dependencies necessary for the correct compilation of the game, this command will also execute it immediately.
- If you have already used `make all`, you can use `make run` to run the game immediately.
- If you have made any changes to the game code, you can use `make compile` to compile and then `make run` to run the game or you can also use `make execute` to do these two actions.

### Makefile command:

- `make all`: Install the dependencies and/or libraries, compile and run the executable.
- `make execute`: Compile and run the executable.
- `make compile`: Compile the executable.
- `make run`: Run the executable.
- `make install`: Install the dependencies and/or libraries.

## How to Play.

### controls.

- To walk forward hold down the **W key**.
- To walk left hold down the **A key**.
- To walk right hold down the **D key**.
- To walk backwards hold down the **S key**.
- To rotate the camera to the right hold the **RIGHT key** or move the mouse to the right.
- To rotate the camera to the left hold down the **LEFT key** or move the mouse to the left.

## Map View

<p align="center">
  <a href="https://imgur.com/5aCfp1C">
    <img src="https://i.imgur.com/5aCfp1C.png" title="source: imgur.com" width = "600px" height = "350px"/>
  </a>
</p>

### Map Screenshot

<p align="center">
  <a href="https://imgur.com/AHZcRsl"><img src="https://i.imgur.com/AHZcRsl.png" title="source: imgur.com" width = "300px" height = "150px"/></a>
  <a href="https://imgur.com/AVr6Ic3"><img src="https://i.imgur.com/AVr6Ic3.png" title="source: imgur.com" width = "300px" height = "150px"/></a>
</p>

<p align="center">
  <a href="https://imgur.com/ECPWGRv"><img src="https://i.imgur.com/ECPWGRv.png" title="source: imgur.com" width = "300px" height = "150px"/></a>
  <a href="https://imgur.com/ZAlPvwe"><img src="https://i.imgur.com/ZAlPvwe.png" title="source: imgur.com" width = "300px" height = "150px"/></a>
</p>

## References.

### Information sources.

[Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)  
[Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)  
[Raycasting engine rendering](https://stackoverflow.com/questions/24173966/raycasting-engine-rendering-creating-slight-distortion-increasing-towards-edges)

### Examples and Resources.

[The power ups - Learning](https://www.youtube.com/watch?v=_45s_gNicwo&list=PLAGy_slICtV1AD8nV3nEe7P8j82XdxH-7&pp=iAQB)  
[SDL2 C/C++ Tutorial](https://www.youtube.com/watch?v=ZQGA4ke_SQA)  
[Introduction to SDL2](https://www.youtube.com/watch?v=QM4WW8hcsPU)  
[DieHard Wolfers](https://dhw.wolfenstein3d.com/viewforum.php?f=24)  
[Sky Texture](https://opengameart.org/content/cloudy-sky)  
[Textures](https://opengameart.org/content/big-pack-of-hand-painted-tiling-textures)  
[More Textures](https://lodev.org/cgtutor/raycasting2.html)
