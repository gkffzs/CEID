import javax.swing.*;
import java.awt.*;

public class PLAFDemo{
    public static void main(String [] args){
        String laf = null;
        int choice = 0;
        
        if(args.length > 0)
            choice = Integer.parseInt(args[0]);
            
        switch(choice){
            case 1: laf = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
            break;
            case 2: laf = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
            break;
            case 3: laf = "com.sun.java.swing.plaf.mac.MacLookAndFeel";
            break;
            default: laf = "javax.swing.plaf.metal.MetalLookAndFeel";
        }

        try{
            System.out.println("Setting the look and feel");
            UIManager.setLookAndFeel(laf);
        }catch(Exception e){
            System.out.println("Could not set look and feel");
            e.printStackTrace();
        }
        
        JFrame f = new JFrame(laf);
        Container content = f.getContentPane();
        content.setLayout(new FlowLayout());
        content.add(new JButton("OK"));
        content.add(new JCheckBox("Pick me", true));
        JProgressBar bar = new JProgressBar(1,10);
        bar.setValue(7);
        content.add(bar);
        content.add(new JRadioButton("Click here", true));
        content.add(new JSlider(1,10,3));
        content.add(new JPasswordField("mypassword"));
        String [] opts= {"Options1","Option2", "Option3", "Option4"};
        content.add(new JComboBox(opts));
        f.setSize(400,100);
        f.setVisible(true);
    }
}