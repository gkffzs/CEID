public class MarriedPerson extends Person {
    private int children;
    
    public MarriedPerson(String lastname, String firstname, int age, float salary, int sex, int children) {
        super(lastname, firstname, age, true, salary, sex);
        this.children = children;
    }
    
    public int getNoOfChildren() { return children; }
    
    public void setNoOfChildren(int c) { this.children=c; }
    public void setMarried(boolean m) { }
    
    public void setSalary(MarriedPerson spouse) {
        float temp_sal;
        if (spouse.getSex()!=this.getSex()){
            temp_sal=this.getSalary()+spouse.getSalary();
            this.setSalary(temp_sal);
        }
    }
    
    public void printInfo() {
        super.printInfo();
        System.out.print(this.getFirstName()+ " has ");
        if (this.getNoOfChildren() > 0)
            System.out.print(this.getNoOfChildren());
        else System.out.print("no");
        System.out.println(" children.");
    }
}