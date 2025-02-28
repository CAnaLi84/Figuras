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
Punto lerp(Punto p1,Punto p2, double t)
{
    double x = static_cast<double>((1-t)*p1.getX() + t*p2.getX());
    double y = static_cast<double>((1-t)*p1.getY() + t*p2.getY());
    return Punto(x,y);
}

//Función para saber si un punto está dentro de las dimensiones de la imágen
bool dentro(Punto p)
{
    bool estaDentro = false;
    if(p.getX() >= 0 && p.getX() < width && p.getY() >= 0 && p.getY() < height){
        estaDentro = true;
    }
    return estaDentro;
}

//Función que calcula la distancia entre dos puntos
double distancia(Punto p1, Punto p2)
{
    double dist = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
    return dist;
}

//Función para pintar una línea
void linea(Punto p1, Punto p2, uint32_t color)
{
    for(double t = 0; t < 1; t += 0.01){
        Punto p = lerp(p1, p2, t);

        if(dentro(p)){
         double index = (p.getY() * width + p.getX()) * 4;
    
         pixels[index + 0] = (color >> 24) & 0xFF;
         pixels[index + 1] = (color >> 16) & 0xFF;
         pixels[index + 2] = (color >> 8) & 0xFF;
         pixels[index + 3] = color & 0xFF;
        }
    }
}

//Función para pintar un círculo
void circulo(int cx, int cy, int radio, uint32_t color)
{
    for(int alfa = 0; alfa < 360; alfa++){
        int x = radio * cos(alfa);
        int y = radio * sin(alfa);
        int index = ((y+cy) * width + (x+cy)) * 4;

        pixels[index + 0] = (color >> 24) & 0xFF;
        pixels[index + 1] = (color >> 16) & 0xFF;
        pixels[index + 2] = (color >> 8) & 0xFF;
        pixels[index + 3] = color & 0xFF;
    }
}

//Función para pintar un cuadrado dados dos puntos horizontales
void cuadrado(Punto p1, Punto p2, uint32_t color)
{
    double dist = distancia(p1, p2);
    if(p1.getY() == p2.getY()){
        Punto p3(p1.getX(), p1.getY()+dist);
        Punto p4(p2.getX(), p2.getY()+dist);

        linea(p1, p2, color);
        linea(p2, p4, color);
        linea(p3, p4, color);
        linea(p3, p1, color);
    }else{
        std::cout << "Igrese dos puntos horizontales" << std::endl;
    }
}

//Función para pintar un triángulo
void triangulo()
{}

//Función para pintar hexágono
void hexagono()
{}

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
    Punto p1(100,200);
    Punto p2(400,200);
    Punto p3(400,400);

    std::cout << "Pintando pixeles" << std::endl;
    //pinta(300,300,0xFF0000FF);
    //pinta(500,300,0x00FF00FF);
    //pinta(300,500,0x00FFFF);
    //pinta(700,300,0xFF00FFFF);
    //circulo(400,300,50,blanco);
    //linea(p1,p3, rojo);
    cuadrado(p1,p2,amarillo);



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
