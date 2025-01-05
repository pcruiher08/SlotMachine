// Ventana.hpp
#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Ventana {
public:
    Ventana(const std::string& titulo, int ancho, int alto) {
        ventana = SDL_CreateWindow(titulo.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

    void limpiar() {
        SDL_RenderClear(renderer);
    }

    void presentar() {
        SDL_RenderPresent(renderer);
    }

    ~Ventana() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
    }

private:
    SDL_Window* ventana;
    SDL_Renderer* renderer;
};


#endif // VENTANA_HPP