public class MyBox extends Box{
    double side;

    public MyBox(double h, double w, double l){
            super(h, w, l);
            
            if(h!=w || w!=l || h!=l){
                System.out.println("ERROR: this is not a cube.");
            }else if(h<0 || w<0 || h<0){
                System.out.println("ERROR: sides must be greater than 0.");
            }else if((w==h)&&(h==l)){
                side=h;
            } 
    }
    
    double calculate(){
        return 6*(side*side);
    }
    
    double volume(){
        return side*side*side;
    }
        
    public String toString(){
        double calc=calculate();
        double vol=volume();
        String s="Cube Calculation " + calc + ", Volume " + vol;
        System.out.println(s);
        return s;
    }
}