class Box{
    // Instance Variables
    double length;
    double width;
    double height;
    
    // Constructors
    Box (double side){
        width=side;
        height=side;
        length=side;
    }
    
    Box (double h, double w, double l){
        height=h;
        width=w;
        length=l;
    }
    
    // Methods
    double calculate(){
        return 2*(width*height + width*length + height*length);
    }
    
    double volume(){
        return height*width*length;
    }
        
    public String toString(){
        double calc=calculate();
        double vol=volume();
        String s="Calculation " + calc + ", Volume " + vol;
        System.out.println(s);
        return s;
    }
}