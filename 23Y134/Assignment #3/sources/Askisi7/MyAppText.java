import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MyAppText extends Frame {
    public MyAppText (String title) {
        super(title);
        setFont(new Font("Verdana", Font.BOLD, 14));
        setLayout(new BorderLayout(5,5));
        Label appName = new Label("Application name: ", Label.RIGHT);
        TextField app = new TextField(20);
        JLabel userName = new JLabel("Username: ", SwingConstants.RIGHT);
        JTextField user = new JTextField(20);
        Label passWord1 = new Label("Password awt: ");
        TextField pwd1 = new TextField(20);
        pwd1.setEchoChar('#');
        JLabel passWord2 = new JLabel("Password swing: ");
        JPasswordField pwd2 = new JPasswordField(20);
        Label comments1 = new Label("Comments awt: ", Label.RIGHT);
        TextArea area1 = new TextArea("Default awt...",5, 20,
        TextArea.SCROLLBARS_BOTH);
        JLabel comments2 = new JLabel("Comments swing: ",
        SwingConstants.RIGHT);
        JTextArea area2 = new JTextArea("Default swing...",5, 20);
        JScrollPane pane = new
        JScrollPane(area2,ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
        ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        Panel MyUpPanel = new Panel();
        MyUpPanel.setLayout(new GridLayout(0,2,5,5));
        Panel MyDownPanel = new Panel();
        MyDownPanel.setLayout(new GridLayout(0,2,5,5));
        MyUpPanel.add(appName);
        MyUpPanel.add(app);
        MyUpPanel.add(userName);
        MyUpPanel.add(user);
        MyUpPanel.add(passWord1);
        MyUpPanel.add(pwd1);
        MyUpPanel.add(passWord2);
        MyUpPanel.add(pwd2);
        MyDownPanel.add(comments1);
        MyDownPanel.add(area1);
        MyDownPanel.add(comments2);
        MyDownPanel.add(pane);
        add("North", MyUpPanel);
        add("South", MyDownPanel);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                System.exit(0);
            }
        });
    }
    
    public static void main(String[] args){
        MyAppText app2 = new MyAppText("Application Window");
        app2.pack();
        app2.setVisible(true);
    }
}