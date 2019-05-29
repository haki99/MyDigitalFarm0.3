#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//!Globalis a window, mert csak egy ablakkal dolgozunk
extern SDL_Window *window;

//!Globalis a felulet
extern SDL_Surface *surface;

//!Globalis a megjelenito motor is
extern SDL_Renderer *renderer;

//!A 2D matrixot kezelo struct
typedef struct Field
{
    int szeles, magas;
    int **adat;
} Field;

//!A 2D matrix az idonek
typedef struct Ido
{
    int szeles, magas;
    int **adat;
} Ido;

#endif // HEADER_H_INCLUDED
