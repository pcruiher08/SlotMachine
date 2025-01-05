// Simbolo.hpp
#ifndef SIMBOLO_HPP
#define SIMBOLO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Simbolo {
public:
    Simbolo(const std::string& ruta, SDL_Renderer* renderer) {
        textura = cargarTextura(ruta, renderer);
    }

    SDL_Texture* getTextura() const {
        return textura;
    }

private:
    SDL_Texture* textura;

    SDL_Texture* cargarTextura(const std::string& ruta, SDL_Renderer* renderer) {
        SDL_Surface* superficie = IMG_Load(ruta.c_str());
        if (!superficie) {
            std::cerr << "Error IMG_Load: " << IMG_GetError() << std::endl;
            return nullptr;
        }
        SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
        SDL_FreeSurface(superficie);
        return textura;
    }
};

#endif // SIMBOLO_HPP

