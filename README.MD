# Mandelbrot viewer
This project was made using the programming language c with the graphics library [SDL](https://www.libsdl.org/). In order to improve performance the library [OpenMp](https://www.openmp.org/) was also used.
## Running the program
In order to run this program, compile it using `make`. Once compiled, the program expects 4 command line arguments when called in the terminal:
```Powershell
./main.exe <re(z)> <im(z)> <scale> <colortheme>
```