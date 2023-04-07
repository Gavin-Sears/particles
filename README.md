# particles

Implements particle demos

<img width="401" alt="demo_screenshot" src="https://user-images.githubusercontent.com/112534115/230680571-2cdc9335-1bd7-4ee8-ad44-721d988f88cd.png">

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ start particles.sln
```

Your solution file should contain four projects.
To run from the git bash command shell, 

```
particles/build $ ../bin/Debug/billboard-axis.exe
particles/build $ ../bin/Debug/explosion.exe
particles/build $ ../bin/Debug/sparkle-trail.exe
particles/build $ ../bin/Debug/sparkles.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ make
```

To run each program from build, you would type

```
particles/build $ ../bin/billboard-axis
particles/build $ ../bin/sparkles
particles/build $ ../bin/sparkle-trail
particles/build $ ../bin/explosion
```

## Demo of basic features

# Animated Sprites

https://user-images.githubusercontent.com/112534115/230680800-42b2d3dc-4833-444f-adf6-8019d62e8479.mp4

# Billboards

https://user-images.githubusercontent.com/112534115/230680838-600d1f0b-1872-41ac-a1fe-1626876ff011.mp4

# Trailing Particles

https://user-images.githubusercontent.com/112534115/230680879-cf84be56-e921-4593-ba59-7768c55bf4ae.mp4

## Unique features 

# Spinning Duck ring

https://user-images.githubusercontent.com/112534115/230680922-338f6904-742c-4bb8-a650-f04c477cadbe.mp4
