import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MyAppEv extends JFrame implements ActionListener{
    private static int h=0,g=0;
    JButton b1 = new JButton("Real");
    JButton b2 = new JButton("Barcelona");
    
    public MyAppEv (String title) {
        super(title);
        b1.addActionListener(this);
        b2.addActionListener(this);
        JPanel myPanel = new JPanel();
        myPanel.add(b1);
        myPanel.add(b2);
        setContentPane(myPanel);
    }
    
    public void actionPerformed(ActionEvent e){
        Object source = e.getSource();
        
        if (source == b1) {
            ++g;
            setTitle("Real Madrid " + g + ":" + h + " Barcelona");
        }else if (source == b2){
            ++h;
            setTitle("Real Madrid " + g + ":" + h + " Barcelona");
        }
    }
    
    public static void main(String[] args){
        try {
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
        } catch (Exception e) {
            System.err.println("Can't set look and feel: " + e);
        }
    
        MyAppEv app = new MyAppEv("Real Madrid " + g + ":" + h + " Barcelona");
        
        WindowListener L = new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        };
    
        app.addWindowListener(L);
        app.setBounds(300,200,350,250);
        app.setVisible(true);
    }
}