public class HourlyEmployee extends Employee{
   private int hoursWorked=0;
   private int hourlyPayment=0;
   
   public void setHoursWorked(int hw){
       this.hoursWorked=hw;
   }
   
   public int getHoursWorked(){
       return this.hoursWorked;
   }
   
   public void setHourlyPayment(int hp){
       this.hourlyPayment=hp;
   }
   
   public int getHourlyPayment(){
       return this.hourlyPayment;
   }
   
   public int payment(){
       return this.hoursWorked*this.hourlyPayment;
   }
}
