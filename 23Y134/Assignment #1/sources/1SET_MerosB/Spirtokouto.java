public class Spirtokouto extends Box{
     double weight;
    
    public Spirtokouto(double h, double w, double we, double l){
        super(h, w, l);
        weight=we;
    }
    
    public String toString(){
        double calc=super.calculate();
        double vol=super.volume();
        String s="Matchbox Calculation " + calc + ", Volume " + vol + ", Weight " + weight;
        System.out.println(s);
        return s;
    }        
}