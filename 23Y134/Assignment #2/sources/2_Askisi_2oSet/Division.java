import java.io.*;

public class Division{
    public static void main(String args[]){
        System.out.print("Please insert the first number: ");
        int first=readInt();
        System.out.print("Please insert the second number: ");
        int second=readInt();
        
        try{
            if((first<0) || (second<0)){
                System.out.println("The division couldn't be done.");
            }else{
                System.out.println("The result after the division is "+divide_x_y(first,second)+".");
            }
        }catch(ArithmeticException ae){
            System.out.println("ArithmeticException: cannot divide with zero.");
        }
    }
    
    public static int readInt(){
        byte number[]=new byte[16];
        String temp_str;
        
        try{
            System.in.read(number);
            temp_str=(new String(number)).trim();
            return Integer.parseInt(temp_str);
        }catch(IOException ioe){
            System.out.println("IOException: "+ioe.toString()+".");
            return 0;
        }catch(NumberFormatException nfe){
            System.out.println("NumberFormatException: "+nfe.toString()+".");
            return -1;
        }
    }
    
    public static double divide_x_y(int x,int y) throws ArithmeticException{
        double result= (double)x/(double)y;
        
        if(result==Double.POSITIVE_INFINITY  || result==Double.NEGATIVE_INFINITY) {
            throw new ArithmeticException("ArithmeticException: cannot divide with zero.");
        }
       
        return result;
    }
}
