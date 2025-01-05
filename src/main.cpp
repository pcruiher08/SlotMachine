#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../include/Boton.hpp"
#include "../include/Simbolo.hpp"
#include "../include/Rodillo.hpp"
#include "../include/Dinero.hpp"
#include "../include/Ventana.hpp"

const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;

std::vector<std::string> rutasSimbolos = {
    "../assets/lemon.png", "../assets/cherry.png", "../assets/diamond.png"};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Error IMG_Init: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Error TTF_Init: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* fuente = TTF_OpenFont("../assets/font.ttf", 28);
    if (!fuente) {
        std::cerr << "Error TTF_OpenFont: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    Ventana ventana("Tragamonedas", ANCHO_VENTANA, ALTO_VENTANA);
    SDL_Renderer* renderer = ventana.getRenderer();

    std::vector<SDL_Texture*> simbolos;
    for (const auto& ruta : rutasSimbolos) {
        Simbolo simbolo(ruta, renderer);
        simbolos.push_back(simbolo.getTextura());
    }

    std::vector<std::vector<int>> posicionesRodillos(3, std::vector<int>(3));
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            posicionesRodillos[fila][col] = std::rand() % simbolos.size();
        }
    }

    Dinero dinero(100);

    Boton botonGirar((ANCHO_VENTANA - 200) / 2 - 300, ALTO_VENTANA - 150 - 300, 200, 50, "Girar");
    Boton botonRetirar((ANCHO_VENTANA - 200) / 2 - 300, ALTO_VENTANA - 150 - 300 + 70, 200, 50, "Retirar");

    bool salir = false;
    SDL_Event evento;
    bool girando = false;
    int contadorGiros = 0;
    const int DURACION_GIRO = 50;
    const int RETRASO_ENTRE_ACTUALIZACIONES = 50;

    while (!salir) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                salir = true;
            } else if (evento.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (botonGirar.contiene(mouseX, mouseY)) {
                    if (dinero.getCantidad() >= 2) {
                        dinero.actualizar(-2);
                        girando = true;
                        contadorGiros = 0;
                    } else {
                        std::cerr << "¡No tienes suficiente dinero para girar!" << std::endl;
                    }
                } else if (botonRetirar.contiene(mouseX, mouseY)) {
                    std::cout << "Saldo final: $" << dinero.getCantidad() << std::endl;
                    salir = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); 

        if (girando) {
            for (int fila = 0; fila < 3; fila++) {
                for (int col = 0; col < 3; col++) {
                    posicionesRodillos[fila][col] = std::rand() % simbolos.size();
                }
            }
            contadorGiros++;
            if (contadorGiros > DURACION_GIRO) {
                girando = false;
                contadorGiros = 0;

                // Verificar si hay una victoria en alguna fila
                for (int fila = 0; fila < 3; fila++) {
                    // Verificar si los tres símbolos en la fila son iguales
                    if (posicionesRodillos[fila][0] == posicionesRodillos[fila][1] && posicionesRodillos[fila][1] == posicionesRodillos[fila][2]) {
                        std::cout << "¡Victoria en fila!" << std::endl;
                        dinero.actualizar(10);  // Añadir 10 monedas por ganar
                    }
                }

                // Verificar si hay una victoria en las diagonales
                // Diagonal principal (de arriba a la izquierda a abajo a la derecha)
                if (posicionesRodillos[0][0] == posicionesRodillos[1][1] && posicionesRodillos[1][1] == posicionesRodillos[2][2]) {
                    std::cout << "¡Victoria en la diagonal principal!" << std::endl;
                    dinero.actualizar(15);  // Añadir 15 monedas por ganar en la diagonal principal
                }

                // Diagonal secundaria (de arriba a la derecha a abajo a la izquierda)
                if (posicionesRodillos[0][2] == posicionesRodillos[1][1] && posicionesRodillos[1][1] == posicionesRodillos[2][0]) {
                    std::cout << "¡Victoria en la diagonal secundaria!" << std::endl;
                    dinero.actualizar(15);  // Añadir 15 monedas por ganar en la diagonal secundaria
                }
            }

        }

        for (int col = 0; col < 3; col++) {
            for (int fila = 0; fila < 3; fila++) {
                Rodillo rodillo((ANCHO_VENTANA - 100 * 3 - 20 * 2) / 2 + col * (100 + 20), 100 + fila * (150 + 20));
                rodillo.dibujar(renderer, simbolos, posicionesRodillos, fila, col);
            }
        }

        dinero.mostrar(renderer, fuente);

        botonGirar.dibujar(renderer, fuente);
        botonRetirar.dibujar(renderer, fuente);

        ventana.presentar();
        SDL_Delay(RETRASO_ENTRE_ACTUALIZACIONES);
    }

    // Liberar las texturas
    for (auto& textura : simbolos) {
        SDL_DestroyTexture(textura);
    }

    TTF_CloseFont(fuente);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}