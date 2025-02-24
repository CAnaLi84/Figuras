class Punto{
    private:
        int x;
        int y;
    
    // Método contructor
    Punto(int _x, int _y) : x(_x), y(_y){}

    // Métodos de acceso a las coordenadas
    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void setX(int my_x){
        x = my_x;
    }

    void setY(int my_y){
        y = my_y;
    }
};