import java.awt.*;
import java.awt.event.*;

public class MyAppBord extends Frame {
    public MyAppBord (String title) {
            super(title);
            Font f1 = new Font("Helvetica", Font.PLAIN, 10);
            setFont(f1);
            BorderLayout lay1 = new BorderLayout(3,2);
            setLayout(lay1);
            add("North", new Button("North"));
            add("South", new Button("South"));
            add("East", new Button("East"));
            add("West", new Button("West"));
            add("Center", new Button("Center"));
            addWindowListener(new WindowAdapter() {
                public void windowClosing(WindowEvent evt) {
                    System.exit(0);
                }
            });
    }

    public static void main(String[] args){
        MyAppBord app2 = new MyAppBord("Application Window");
        app2.pack();
        app2.setBounds(50, 50, 300, 300);
        app2.setVisible(true);
    }
}