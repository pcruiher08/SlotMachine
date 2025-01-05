// Boton.hpp
#ifndef BOTON_HPP
#define BOTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Boton {
public:
    Boton(int x, int y, int w, int h, const std::string& etiqueta)
        : x(x), y(y), w(w), h(h), etiqueta(etiqueta) {}

    void dibujar(SDL_Renderer* renderer, TTF_Font* fuente) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect rectBoton = {x, y, w, h};
        SDL_RenderFillRect(renderer, &rectBoton);

        SDL_Color colorTexto = {255, 255, 255, 255};
        SDL_Surface* superficieTexto = TTF_RenderText_Solid(fuente, etiqueta.c_str(), colorTexto);
        SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderer, superficieTexto);
        SDL_FreeSurface(superficieTexto);

        int anchoTexto = 0, altoTexto = 0;
        SDL_QueryTexture(texturaTexto, NULL, NULL, &anchoTexto, &altoTexto);

        SDL_Rect rectTexto = {x + (w - anchoTexto) / 2, y + (h - altoTexto) / 2, anchoTexto, altoTexto};
        SDL_RenderCopy(renderer, texturaTexto, NULL, &rectTexto);
        SDL_DestroyTexture(texturaTexto);
    }

    bool contiene(int mouseX, int mouseY) {
        return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
    }

private:
    int x, y, w, h;
    std::string etiqueta;
};


#endif

