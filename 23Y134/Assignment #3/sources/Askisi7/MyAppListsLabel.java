import java.awt.*;
import java.awt.event.*;

public class MyAppListsLabel extends Frame {
    public MyAppListsLabel (String title) {
        super(title);
        setFont(new Font("Tahoma", Font.ITALIC, 10));
        setLayout(new GridLayout(2,2,10,10));
        Label lb = new Label("Choose Language");
        add(lb);
        Choice progLang = new Choice();
        progLang.add("Pascal");
        progLang.add("Java");
        progLang.add("Basic");
        progLang.add("C");
        progLang.add("C++");
        add(progLang);
        add(new Label("Choose Operating System"));
        List l = new List(4, true);
        l.add("Windows");
        l.add("Linux");
        l.add("IRIX");
        l.add("MacOS");
        add(l);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                System.exit(0);
            }
        });
    }
    
    public static void main(String[] args){
        MyAppListsLabel app2 = new MyAppListsLabel("Application Window");
        app2.setSize(200, 200);
        app2.setVisible(true);
    }
}