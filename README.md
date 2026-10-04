# ASCII Donut — Python

A spinning 3D donut rendered entirely in the terminal using Python.

This project is a Python implementation inspired by the famous **ASCII donut** technique, using trigonometry, 3D rotation, perspective projection, lighting, and a z-buffer to create a rotating donut using nothing but ASCII characters.

## Demo

The program continuously renders a rotating 3D donut directly in the terminal.

```text
                                                                                             
                                   $@@@@@@@@@@@@@$                              
                              $$@@@@@@@@@@@@@@@@@@@@@@@#                        
                          #$$@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#                     
                        #$$$$$$$$$$$$$#$$$$$$$@@@@@@@@@@@@@@$                   
                     =#$$$$$$$#####********####$$$@@@@@@@@@@@$#                 
                    ##$$$$$###*********===*=***##$$$$@@@@@@@@@$$*               
                  *##$$$####****===;;;;;;;;=====**#$$$@@@@@@@@@$#*              
                 *##$$$###***===;;::~~~~~~:::;===**##$$@@@@@@@@$$#*             
                *###$#####**==;;:~~-,,,.,,,--~:;;==*##$$$@@@@@@$$##=            
               =*##$$####**==;;:~-,,.       .,-~:;=**##$$$@@@@@$$$#*;           
              =*###$$####**=;;:~-,.           .-~;;=*##$$$$@@@$$$##*=           
             ;**##$$$$###**=;:~-,.             .-:;=*##$$$$$$$$$$##*=:          
             ;*##$$$$$$###*=;:~-.               ,~;=**##$$$$$$$$$#**=:          
            :=*##$$$$$$$###*=;~-.               ,:;=*##$$$$$$$$###*==:          
            :=*##$$$$$$$$$##*=:-.               ~;=*###$$$$$$$###**=;~          
            :=**#$$$@@@@@$$##*=:                ;=**###$$$$$$###***=;~          
            ~;=*##$$@@@@@@@$$#*;               ;**####$$$$#####***=;:-          
            ~:=*##$$@@@@@@@@@@$#=            =**#####$$$######***=;:~,          
            -:;=*##$$@@@@@@@@@@@$#=        **######$$#######***==;:~-           
            .~;=**##$$@@@@@@@@@@@@@$$$$$#$$$$$$$$$$########***==;::-.           
             -:;==*##$$@@@@@@@@@@@@@@@@@$$$$$$$$$######*#***===;:~-.            
              -:;;=**##$$$@@@@@@@@@@@@@@$$$$$$$#####*#****===;:~~-.             
              .-:;;==**###$$$$@@@@@@@@$$$$$$#####*******==;;::~-,.              
                -~:;==****#####$$$$$$$#$#######******===;;::~-,.                
                 .-~:;;==*******####*###*********====;;:::~-,.                  
                   .-~::;===***=***********=====;;;;::~~--,.                    
                     .,-~~::;;;===========;;;;;:::~~~--,.                       
                        .,--~~~:::::::::::::~~~~--,,..                          
                            ..,,,-----------,,,..                               
                                                                                
                                                                
```

The actual appearance changes continuously as the donut rotates.

## How It Works

The donut is represented mathematically as a **torus**.

Two angles are used:

- `theta` — angle around the cross-section of the donut
- `phi` — angle around the main ring

For every point on the surface, the program:

1. Calculates the 3D coordinates.
2. Rotates the point around the X/Y axes.
3. Projects the 3D point onto the 2D terminal.
4. Calculates the surface brightness.
5. Uses a z-buffer to determine which surface point is visible.
6. Maps brightness to an ASCII character.
7. Prints the completed frame.
8. Changes the rotation angles and renders the next frame.

## Key Concepts

### 3D Rotation

The donut uses trigonometric functions:

```python
math.sin()
math.cos()
```

to rotate the torus in 3D space.

### Perspective Projection

The 3D coordinates are converted into terminal coordinates using perspective:

```python
xp = int(SCREEN_WIDTH / 2 + K1 * ooz * x)
yp = int(SCREEN_HEIGHT / 2 - K1 * ooz * y * 0.5)
```

where:

```text
ooz = 1 / z
```

Objects farther away appear smaller.

### Z-Buffer

Multiple 3D points can map to the same terminal position.

The z-buffer keeps track of the closest point:

```python
if ooz > zbuffer[xp][yp]:
    zbuffer[xp][yp] = ooz
```

This prevents points behind the visible surface from overwriting it.

### Lighting

The variable `L` represents the approximate brightness of a surface point.

That brightness is converted into an ASCII character:

```python
".,-~:;=*#$@"
```

Darker areas use simpler characters, while brighter areas use denser characters.

## Requirements

- Python 3
- A terminal that supports ANSI escape sequences

No external Python packages are required.

## Running the Program

Clone the repository:

```bash
git clone <your-repository-url>
cd donut
```

Run:

```bash
python3 donut.py
```

Press `Ctrl+C` to stop the animation.

## Configuration

You can experiment with the constants at the top of the program:

```python
SCREEN_WIDTH = 80
SCREEN_HEIGHT = 40

theta_spacing = 0.07
phi_spacing = 0.02

R1 = 0.5
R2 = 1.0
K2 = 10.0
```

### `SCREEN_WIDTH` / `SCREEN_HEIGHT`

Controls the size of the terminal rendering.

### `theta_spacing` / `phi_spacing`

Controls the number of points used to construct the donut.

Smaller values:

- Produce a smoother donut
- Require more computation
- Can reduce animation speed

Larger values:

- Produce a faster animation
- Use fewer points
- Can make the donut look less detailed

### `R1`

Controls the radius of the donut's tube.

### `R2`

Controls the distance from the center of the donut to the center of its tube.

### `K2`

Controls the distance of the donut from the camera.

## Performance

The renderer performs thousands of calculations for every frame.

For example:

```text
theta ≈ 2π / theta_spacing
phi   ≈ 2π / phi_spacing
```

Therefore, reducing the spacing values increases the number of points that must be calculated.

For a faster animation, try:

```python
theta_spacing = 0.07
phi_spacing = 0.02
```

## Learning Goals

This project was built as a practical way to understand:

- Python loops
- Functions
- `math.sin()` and `math.cos()`
- 3D coordinate systems
- Rotation matrices
- Perspective projection
- Z-buffering
- Basic lighting
- ASCII rendering
- Terminal ANSI escape sequences
- Animation loops
- Performance considerations in Python

## Credits

Inspired by the classic ASCII donut algorithm by **Andy Sloane (a1k0n)**.

The original technique demonstrates how a surprisingly convincing 3D animation can be produced using simple mathematics and terminal characters.

## License

This project is intended for learning and experimentation.