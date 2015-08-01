import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MyAppButton extends Frame {
    public MyAppButton (String title) {
        super(title);
        Font f1 = new Font("Tahoma", Font.PLAIN, 14);
        setFont(f1);
        FlowLayout lay1 = new FlowLayout(FlowLayout.LEFT);
        setLayout(lay1);
        add(new Button("Previous"));
        add(new Button("Stop"));
        add(new Button("Play"));
        add(new Button("Pause"));
        add(new Button("Next"));
        ImageIcon ic1 = createImageIcon("icon_01.jpg");
        add(new JButton(ic1));
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                System.exit(0);
            }
        });
    }
    
/** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = MyAppButton.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }

    public static void main(String[] args){
        MyAppButton app2 = new MyAppButton("Application Window");
        GridLayout lay2 = new GridLayout(3,2); app2.setLayout(lay2);
        app2.setSize(400, 200);
        app2.setVisible(true);
    }
}