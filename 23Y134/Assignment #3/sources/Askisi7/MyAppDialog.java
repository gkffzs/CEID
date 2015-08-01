import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MyAppDialog extends JFrame implements ActionListener{
    Button b = new Button("Delete");
    
    public MyAppDialog (String title) {
        super(title);
        JPanel myPanel = new JPanel();
        b.addActionListener(this);
        myPanel.add(b);
        setContentPane(myPanel);
    }
    
    public void actionPerformed(ActionEvent e){
        int answer = JOptionPane.showConfirmDialog(null, "Delete file?",
        "Deleting File", JOptionPane.YES_NO_OPTION, JOptionPane.ERROR_MESSAGE);
        if (answer == JOptionPane.OK_OPTION)
            JOptionPane.showMessageDialog(null,"File deleted!","File Deletion Information",JOptionPane.INFORMATION_MESSAGE);
        else
            JOptionPane.showMessageDialog(null,"File not deleted!","File Deletion Information",JOptionPane.INFORMATION_MESSAGE); 
    }
            
    public static void main(String[] args){
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            System.err.println("Can't set look and feel: " + e);
        }
        
        MyAppDialog app = new MyAppDialog("Application Window");
        
        WindowListener I = new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        };
        
        app.addWindowListener(I);
        app.setSize(200,200);
        app.setVisible(true);
    }
}