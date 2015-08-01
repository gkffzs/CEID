public class Person {
    private String lastname;
    private String firstname;
    private int age;
    private boolean married;
    private float salary;
    public static final int MALE = 0;
    public static final int FEMALE = 1;
    private int sex;
    
    public Person (String lastname, String firstname, int age, boolean married, float salary, int sex) {
        this.lastname = new String(lastname);
        this.firstname = new String(firstname);
        this.age = age;
        this.married = married;
        this.salary = salary;
        this.sex = sex;
    }
    
    public String getLastName() { return lastname; }
    public String getFirstName() { return firstname; }
    public int getAge() { return age; }
    public boolean isMarried() { return married; }
    public float getSalary() { return salary; }
    public int getSex() { return sex; }
    
    public void setLastName(String ln) { this.lastname=ln; }
    public void setFirstName(String fn) { this.firstname=fn; }
    public void setAge(int a) { this.age=a; }
    public void setMarried(boolean m) { this.married=m; }
    public void setSalary(float s) { this.salary=s; }
    public void setSex(int s) { this.sex=s; }
 
    public void printInfo() { 
        System.out.print(this.getFirstName()+" "+this.getLastName()+" is "
        +this.getAge()+" years old, ");
        if(sex==0) System.out.print("male, ");
        else if (sex==1) System.out.print("female, ");
        System.out.print("gets a "+this.getSalary()+" Euros salary and is");
        if (this.isMarried() == false)
            System.out.print(" not");
        System.out.println(" married.");
    }
}