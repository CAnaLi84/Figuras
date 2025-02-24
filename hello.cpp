#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>
#include "colores.cpp"
#include "punto.cpp"

#define PI 3.141592



    // Dimensiones de la imagen
    const int width = 800;
    const int height = 600;
    
    std::vector<uint8_t> pixels;

//Función lerp
double lerp(int p1,int p2, double t)
{
    return (1-t)*p1 + t*p2;
}

//Función para pintar una línea
void linea(int p1, int p2, uint32_t color)
{
    for(double t = 0; t < 1; t += 0.0001){
        int x = static_cast<int>(lerp(p1, p2, t));
        int y = x*2;

        if(x >= 0 && x < width && y >= 0 && y < height){
         double index = (y * width + x) * 4;
    
         pixels[index + 0] = (color >> 24) & 0xFF;
         pixels[index + 1] = (color >> 16) & 0xFF;
         pixels[index + 2] = (color >> 8) & 0xFF;
         pixels[index + 3] = color & 0xFF;
        }
    }
}

//Función para pintar un círculo
//void circulo(int cx, int cy, int radio, uint32_t color)
//{
//    for(int alfa = 0; alfa < 360; alfa++){
//        int x = radio * cos(alfa);
//        int y = radio * sin(alfa);
//        int index = ((y+cy) * width + (x+cy)) * 4;
//
//        pixels[index + 0] = (color >> 24) & 0xFF;
//        pixels[index + 1] = (color >> 16) & 0xFF;
//        pixels[index + 2] = (color >> 8) & 0xFF;
//        pixels[index + 3] = color & 0xFF;
//    }
//}

//Función para pintar un cuadrado

//Función para pintar un triángulo

//Función para pintar hexágono

//Función para pintar un fractal

void pinta(int x, int y, uint32_t color)
{
    int index = (y * width + x) * 4;
    pixels[index + 0] = (color >> 24) & 0xFF;
    pixels[index + 1] = (color >> 16) & 0xFF;
    pixels[index + 2] = (color >> 8) & 0xFF;
    pixels[index + 3] = color & 0xFF;
}

void initPixels(uint32_t color)
{

pixels.reserve(width * height * 4);
std::cout << "Inicializando" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
           // uint32_t pixel = image[y][x];
            uint32_t pixel = color;
            int index = (y * width + x) * 4;
            pixels[index + 0] = (pixel >> 24) & 0xFF; // R
            pixels[index + 1] = (pixel >> 16) & 0xFF; // G
            pixels[index + 2] = (pixel >> 8) & 0xFF;  // B
            pixels[index + 3] = pixel & 0xFF;         // A
        }
    }

}

//funciones de figuras

int main() {

    initPixels(0x000000FF);
    // Crear una textura y un sprite para mostrar la imagen
    sf::Texture texture;
    texture.create(width, height);

    std::cout << "Pintando pixeles" << std::endl;
    pinta(300,300,0xFF0000FF);
    pinta(500,300,0x00FF00FF);
    pinta(300,500,0x00FFFF);
    pinta(700,300,0xFF00FFFF);
    //circulo(400,300,50,blanco);
    linea(100,400, rojo);



    std::cout << "Cargar los píxeles en la textura" << std::endl;
    texture.update(pixels.data());

    std::cout << "Crear un sprite para mostrar la textura" << std::endl;
    sf::Sprite sprite(texture);

    std::cout << "Crear una ventana" << std::endl;
    sf::RenderWindow window(sf::VideoMode(width, height), "Display Image from Array");

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
