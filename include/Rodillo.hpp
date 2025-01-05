// Rodillo.hpp
#ifndef RODILLO_HPP
#define RODILLO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Rodillo {
public:
    Rodillo(int x, int y) : x(x), y(y) {}

    void dibujar(SDL_Renderer* renderer, const std::vector<SDL_Texture*>& simbolos, const std::vector<std::vector<int>>& posicionesRodillos, int fila, int col) {
        const int ANCHO_RODILLO = 100;
        const int ALTO_RODILLO = 150;
        SDL_Rect dstRect = {x, y, ANCHO_RODILLO, ALTO_RODILLO};
        SDL_RenderCopy(renderer, simbolos[posicionesRodillos[fila][col]], NULL, &dstRect);
    }

private:
    int x, y;
};

#endif // RODILLO_HPP

