import java.awt.*;
import java.awt.event.*;

public class CardWindow extends Frame implements ItemListener {
    Panel cards;
    Choice c = new Choice();
    final static String BUTTONPANEL = "Panel with Buttons";
    final static String TEXTPANEL = "Panel with TextField";
    
    public CardWindow() {
        setLayout(new BorderLayout());
        setFont(new Font("Helvetica", Font.PLAIN, 14));
        //Put the Choice in a Panel to get a nicer look.
        Panel cp = new Panel();
        c.addItem(BUTTONPANEL);
        c.addItem(TEXTPANEL);
        c.addItemListener(this);
        cp.add(c);
        add("North", cp);
        cards = new Panel();
        cards.setLayout(new CardLayout());
        Panel p1 = new Panel();
        p1.add(new Button("Button 1"));
        p1.add(new Button("Button 2"));
        p1.add(new Button("Button 3"));
        Panel p2 = new Panel();
        p2.add(new TextField("TextField", 20));
        cards.add(BUTTONPANEL, p1);
        cards.add(TEXTPANEL, p2);
        add("Center", cards);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent evt) {
                System.exit(0);
            }
        });
    }
    
    public void itemStateChanged(ItemEvent evt) {
// Οι εντολές στα σχόλια θα χρειάζονταν αν και άλλα components
// άκουγαν ItemEvents
// Object component = evt.getSource();
// if (component instanceof Choice) {
        ((CardLayout)cards.getLayout()).show(cards,(String)c.getSelectedItem());
// }
    }
    
    public static void main(String args[]) {
        CardWindow window = new CardWindow();
        window.setTitle("CardWindow Application");
        window.pack();
        window.setVisible(true);
    }
}