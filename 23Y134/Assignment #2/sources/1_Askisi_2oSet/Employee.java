public abstract class Employee{
    private String name;
    private String afm;
    private long EmpID;
    private static int tempID=0;
    
    public Employee(){
        tempID=tempID+1;
        this.EmpID=tempID;
    }
    
    public void setName(String n){
        this.name=n;
    }
    
    public String getName(){
        return this.name;
    }
    
    public void setAfm(String a){
        this.afm=a;
    }
    
    public String getAfm(){
        return this.afm;
    }
    
    public long getEmpID(){
        return this.EmpID;
    }
    
    abstract int payment();
}