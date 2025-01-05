// Dinero.hpp
#ifndef DINERO_HPP
#define DINERO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <iostream>

class Dinero {
public:
    Dinero(int cantidad) : cantidad(cantidad) {}

    void mostrar(SDL_Renderer* renderer, TTF_Font* fuente) {
        SDL_Color colorTexto = {255, 255, 255, 255};
        std::stringstream ss;
        ss << "Dinero: $" << cantidad;
        SDL_Surface* superficieTexto = TTF_RenderText_Solid(fuente, ss.str().c_str(), colorTexto);
        SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderer, superficieTexto);
        SDL_FreeSurface(superficieTexto);

        int anchoTexto = 0, altoTexto = 0;
        SDL_QueryTexture(texturaTexto, NULL, NULL, &anchoTexto, &altoTexto);

        SDL_Rect renderQuad = {10, 10, anchoTexto, altoTexto};
        SDL_RenderCopy(renderer, texturaTexto, NULL, &renderQuad);
        SDL_DestroyTexture(texturaTexto);
    }

    void actualizar(int cambio) {
        cantidad += cambio;
    }

    int getCantidad() {
        return cantidad;
    }

private:
    int cantidad;
};

#endif // DINERO_HPP

