import java.io.*;

public class File_Exe{
    public static void main(String args[]){
        int temp;
        int counter=0;
        long src_length=0;
        long dest_length=0;
        
        try{
            File temp_file_1=new File("src.txt");
            boolean file_exists=temp_file_1.exists();
            FileInputStream file_input=new FileInputStream("src.txt");
        }catch(FileNotFoundException fnfe){
            System.out.println("The file \"src.txt\" wasn't found in this directory.");
            System.exit(0);
        }            
        
        try{
            File temp_file_1=new File("src.txt");
            File temp_file_2=new File("temp.txt");
            
            src_length=temp_file_1.length();
            dest_length=temp_file_2.length();
            
            FileReader file_reader=new FileReader(temp_file_1);
            FileWriter file_writer=new FileWriter(temp_file_2);
            
            System.out.println("Before copying \"src.txt\" to \"dest.txt\":");
            System.out.println("\t-\"src.txt\" Length: "+src_length);
            System.out.println("\t-\"dest.txt\" Length: "+dest_length+"\n");
            
            do{
                temp=file_reader.read();
                
                if(temp!=-1){
                    if((char)temp==' '){
                        temp=(int)'@';
                        counter++;
                    }
                    
                    file_writer.write(temp);
                }  
            }while(temp!=-1);
            
            file_reader.close();
            file_writer.close();
            
        }catch(FileNotFoundException fnfe){
            System.out.println("FileNotFoundException: "+fnfe.toString()+".");
            System.exit(0);
        }catch(IOException ioe){
            System.out.println("IOException: "+ioe.toString()+".");
            System.exit(0);
        }
        
        try{
            File temp_file_1=new File("temp.txt");
            File temp_file_2=new File("dest.txt");
            String EOL=System.getProperty("line.separator");
            String line=null;
            
            FileReader file_reader=new FileReader(temp_file_1);
            FileWriter file_writer=new FileWriter(temp_file_2);
            BufferedReader file_buffer_read=new BufferedReader(file_reader);
            BufferedWriter file_buffer_write=new BufferedWriter(file_writer);
            
            while((line=file_buffer_read.readLine())!=null){
                    file_buffer_write.write(line+EOL+EOL);
            }
            
            file_buffer_write.close();
            file_buffer_read.close();
            file_reader.close();
            file_writer.close();
            
            System.out.println("After copying \"src.txt\" to \"dest.txt\":");
            System.out.println("\t-\"src.txt\" Length: "+src_length);
            System.out.println("\t-\"dest.txt\" Length: "+temp_file_2.length()+"\n");
            System.out.println(counter+" spaces were replaced with the character \"@\".");
            
        }catch(FileNotFoundException fnfe){
            System.out.println("FileNotFoundException: "+fnfe.toString()+".");
            System.exit(0);
        }catch(IOException ioe){
            System.out.println("IOException: "+ioe.toString()+".");
            System.exit(0);
        }
    }  
}
