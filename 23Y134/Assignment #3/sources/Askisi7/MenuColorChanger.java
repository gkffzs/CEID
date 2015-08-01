import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MenuColorChanger implements ActionListener{
    private Container container;
    private JProgressBar progress;
    
    public MenuColorChanger(Container c, JProgressBar p){
        container = c;
        progress = p;
    }
    
    public void actionPerformed(ActionEvent a){
        String label = a.getActionCommand();
        
        if(label.equals("Red")){
            container.setBackground(Color.RED);
            progress.setValue(1);
        }else if(label.equals("Blue")){
            container.setBackground(Color.BLUE);
            progress.setValue(2);
        }else if(label.equals("White")){
            container.setBackground(Color.WHITE);
            progress.setValue(3);
        }else if(label.equals("Exit")){
            System.exit(0);
        }
    }
}