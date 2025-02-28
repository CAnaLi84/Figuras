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
    double x = static_cast<double>((1-t)*p1.getX() + t*p2.getX()); //Interpolación en X
    double y = static_cast<double>((1-t)*p1.getY() + t*p2.getY()); //Interpolaciñon en Y
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
        Punto p3(p1.getX(), p1.getY()+dist); //Calcula las coordenadas de los otros puntos
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
void triangulo(Punto p1, Punto p2, Punto p3, uint32_t color)
{
    linea(p1, p2, color);
    linea(p2, p3, color);
    linea(p3, p1, color);
}

//Función para pintar hexágono
void hexagono(Punto centro, double radio, uint32_t color)
{
    std::vector<Punto> puntos(6);

    //Calculo de los 6 vértices
    for (int i = 0; i < 6; i++) {
        double alfa = (2 * PI * i) / 6;
        double x = centro.getX() + radio * cos(alfa);
        double y = centro.getY() + radio * sin(alfa);
        puntos[i] = Punto(x, y);
    }

    //Pintamos las 6 líneas
    for (int i = 0; i < 6; i++) {
        linea(puntos[i], puntos[(i + 1) % 6], color);
    }
}

//Función para pintar puntos
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

//Función con el  menú
void mostrarMenu()
{
    std::cout << "\n=== Menú de figuras ===\n";
    std::cout << "0. Línea\n";
    std::cout << "1. Cuadrado\n";
    std::cout << "2. Triángulo\n";
    std::cout << "3. Hexágono\n";
    std::cout << "4. Salir\n";
    std::cout << "Selecciona una opción: ";
}

//funciones de figuras

int main() {
    initPixels(0x000000FF);  

    // Crear una textura y un sprite para mostrar la imagen
    sf::Texture texture;
    texture.create(width, height);
    
    Punto p1(100, 200);
    Punto p2(400, 200);
    Punto p3(400, 400);
    Punto p4(250, 450);

    int opcion;
    
    //Mostrar menú
    mostrarMenu();
    std::cin >> opcion;

    //Limpiar la pantalla
    initPixels(0x000000FF);

    switch(opcion) {
        case 0:
            linea(p1,p2, rojo);
            break;
        case 1:
            cuadrado(p1, p2, amarillo);  
            break;
        case 2:
            triangulo(p1, p2, p4, cyan);  
            break;
        case 3:
            hexagono(p3, 100, magenta); 
            break;
        case 4:
            std::cout << "¡Adiós!\n";
            return 0;
        default:
            std::cout << "Opción no válida.\n";
            return 1;
    }

    // Cargar los píxeles en la textura
    texture.update(pixels.data());

    // Crear un sprite para mostrar la textura
    sf::Sprite sprite(texture);

    // Crear una ventana
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