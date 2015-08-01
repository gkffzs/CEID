import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MenuDemo extends JFrame{
    private JButton red, blue, white;
    private JProgressBar progress;
    
    public MenuDemo(String title){
        super(title);
        Container contentPane = this.getContentPane();
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        red = new JButton("Red");
        blue = new JButton("Blue");
        white = new JButton("White");
        //add the buttons to the frame
        JPanel south = new JPanel();
        south.add(red);
        south.add(blue);
        south.add(white);
        contentPane.add(south, BorderLayout.SOUTH);
        //add the progress bar
        progress = new JProgressBar(0,3);
        contentPane.add(progress, BorderLayout.NORTH);
        //register the event listener
        MenuColorChanger changer = new MenuColorChanger(contentPane, progress);
        red.addActionListener(changer);
        blue.addActionListener(changer);
        white.addActionListener(changer);
        createMenu(changer);
    }
    
    public void createMenu(MenuColorChanger changer){
        //create a menu bar and attach it to this JFrame
        JMenuBar menuBar = new JMenuBar();
        this.setJMenuBar(menuBar);
        //create three menus and add them to the menu bar
        JMenu fileMenu = new JMenu("File");
        JMenu colorMenu = new JMenu("Color");
        JMenu helpMenu = new JMenu("Help");
        menuBar.add(fileMenu);
        menuBar.add(colorMenu);
        menuBar.add(helpMenu);
        //add three menu items to the "Color" menu
        JMenuItem redMenuItem = new JMenuItem("Red");
        JMenuItem blueMenuItem = new JMenuItem("Blue");
        JMenuItem whiteMenuItem = new JMenuItem("White");
        colorMenu.add(redMenuItem);
        colorMenu.add(blueMenuItem);
        colorMenu.add(whiteMenuItem);
        redMenuItem.addActionListener(changer);
        blueMenuItem.addActionListener(changer);
        whiteMenuItem.addActionListener(changer);
        //add one menu item to the "File" menu
        JMenuItem exit = new JMenuItem("Exit");
        fileMenu.add(exit);
        exit.addActionListener(changer);
        //add one menu item and one menu to the "Help" menu
        JMenuItem about = new JMenuItem("About MenuDemo...");
        helpMenu.add(about);
        JMenu cascade = new JMenu("Tip of the day");
        helpMenu.add(cascade);
        JCheckBoxMenuItem show = new JCheckBoxMenuItem("Show");
        cascade.add(show);
    }
    
    public static void main(String [] args){
        MenuDemo f = new MenuDemo("MenuDemo");
        f.setSize(300,300);
        f.setVisible(true);
    }
}