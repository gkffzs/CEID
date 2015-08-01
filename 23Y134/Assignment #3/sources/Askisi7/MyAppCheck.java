import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MyAppCheck extends Frame {
    public MyAppCheck (String title) {
        super(title);
        setFont(new Font("Verdana", Font.BOLD, 12));
        setLayout(new GridLayout(1,3));
        Panel cboxes = new Panel();
        cboxes.setLayout(new GridLayout(0,1));
        Color c = new Color(80,120,230);
        cboxes.setBackground(c);
        Checkbox c1 = new Checkbox("Windows");
        Checkbox c2 = new Checkbox("Linux");
        Checkbox c3 = new Checkbox("IRIX");
        Checkbox c4 = new Checkbox("MacOS");
        cboxes.add(c1);
        cboxes.add(c2);
        cboxes.add(c3);
        cboxes.add(c4);
        c2.setState(true);
        c4.setState(true);
        JPanel cboxgrp = new JPanel();
        cboxgrp.setLayout(new GridLayout(0,1));
        cboxgrp.setBackground(Color.YELLOW);
        cboxgrp.setBorder(BorderFactory.createTitledBorder("Languages"));
        CheckboxGroup progLang = new CheckboxGroup();
        Checkbox cg1 = new Checkbox("Pascal", false, progLang);
        Checkbox cg2 = new Checkbox("Java", false, progLang);
        Checkbox cg3 = new Checkbox("Basic", false, progLang);
        Checkbox cg4 = new Checkbox("C", false, progLang);
        Checkbox cg5 = new Checkbox("C++", false, progLang);
        cboxgrp.add(cg1);
        cboxgrp.add(cg2);
        cboxgrp.add(cg3);
        cboxgrp.add(cg4);
        cboxgrp.add(cg5);
        cg3.setState(true);
        add(cboxes);
        add(cboxgrp);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                System.exit(0);
            }
        });
    }
    
    public static void main(String[] args){
        MyAppCheck app2 = new MyAppCheck("Application Window");
        app2.setSize(200, 200);
        app2.setVisible(true);
    }
}