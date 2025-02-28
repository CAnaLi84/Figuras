class Punto{
    private:
        double x;
        double y;
      
    public:
        // Método contructor
        Punto(double _x, double _y) : x(_x), y(_y){}

        // Métodos de acceso a las coordenadas
       double getX(){
            return x;
        }  

        double getY(){
            return y;
        }

        void setX(double my_x){
            x = my_x;
        }

        void setY(double my_y){
            y = my_y;
         }
};