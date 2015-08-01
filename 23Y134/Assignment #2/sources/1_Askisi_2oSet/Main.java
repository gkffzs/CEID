public class Main{
    public static void main(String args[]){
        Employee emp_list[]=new Employee[2];
        
        emp_list[0]=new SalariedEmployee();
        emp_list[1]=new HourlyEmployee();
        
        emp_list[0].setName("Gewrgiou");
        emp_list[0].setAfm("777777");
        ((SalariedEmployee)emp_list[0]).setSalary(300000);
        
        emp_list[1].setName("Karamitros");
        emp_list[1].setAfm("888888");
        ((HourlyEmployee)emp_list[1]).setHoursWorked(3000);
        ((HourlyEmployee)emp_list[1]).setHourlyPayment(40);
        
        for(int i=0; i<2; i++){
            System.out.println("Employee ID: "+emp_list[i].getEmpID());
            System.out.println("Employee Name: "+emp_list[i].getName());
            System.out.println("Employee AFM: "+emp_list[i].getAfm());
            System.out.println("Employee Payment: "+emp_list[i].payment()+"\n");
        }
            
    }
}
