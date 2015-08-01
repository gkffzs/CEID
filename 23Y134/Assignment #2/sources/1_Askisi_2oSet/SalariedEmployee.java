public class SalariedEmployee extends Employee{
    private int salary=0;
    
    void setSalary(int s){
        this.salary=s;
    }
    
    public int payment(){
        return this.salary;
    }
}
