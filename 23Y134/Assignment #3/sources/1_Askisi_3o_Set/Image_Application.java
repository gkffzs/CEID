import javax.swing.*;
import javax.imageio.*;
import java.awt.image.BufferedImage;
import java.awt.event.*;
import java.awt.*;
import java.io.*;

public class Image_Application extends JFrame implements ActionListener{
    JMenuBar menu_bar;
    JMenu options_menu;
    JMenuItem reset_option;
    JPanel main_panel, image_panel;
    JPanel align_buttons, resize_buttons;
    JButton left_button, center_button, right_button;
    JLabel picture_label;
    int start_width, start_height;
    JLabel width_label, height_label;
    JTextField text_width, text_height;
    JButton resize_button;
    BufferedImage image;
    int type;
    
    String picture_path=new String("wolves.jpg");

	public static void main (String args[]){
        Image_Application image_application=new Image_Application();
    }
	
    public Image_Application(){
        super("Image Application");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        menu_bar=new JMenuBar();
        options_menu=new JMenu("Options");
        reset_option=new JMenuItem("Reset");
        reset_option.setActionCommand("reset");
        reset_option.addActionListener(this);
        options_menu.add(reset_option);
        menu_bar.add(options_menu);
        setJMenuBar(menu_bar);
        
        main_panel=new JPanel();
        main_panel.setLayout(new BorderLayout());
        align_buttons=new JPanel(new GridLayout(1,3));
        image_panel=new JPanel();
        image_panel.setLayout(new FlowLayout(FlowLayout.CENTER));
        resize_buttons=new JPanel(new GridLayout(3,2));
        
        width_label=new JLabel("Width:");
        text_width=new JTextField();
        height_label=new JLabel("Height:");
        text_height=new JTextField();
        resize_button=new JButton("Resize");
        resize_button.setActionCommand("resize");
        resize_button.addActionListener(this);
        
        resize_buttons.add(width_label);
        resize_buttons.add(text_width);
        resize_buttons.add(height_label);
        resize_buttons.add(text_height);
        resize_buttons.add(resize_button);
        
        left_button=new JButton("Align Left");
        left_button.setActionCommand("align_left");
        left_button.addActionListener(this);
        center_button=new JButton("Align Center");
        center_button.setActionCommand("align_center");
        center_button.addActionListener(this);
        right_button=new JButton("Align Right");
        right_button.setActionCommand("align_right");
        right_button.addActionListener(this);
        
        align_buttons.add(left_button);
        align_buttons.add(center_button);
        align_buttons.add(right_button);
        
        try{
            image=ImageIO.read(new File(picture_path));
	        type=image.getType()==0? BufferedImage.TYPE_INT_ARGB : image.getType();
	        start_height=image.getHeight();
            start_width=image.getWidth();
        }catch(IOException ioe){
            ioe.printStackTrace();
        }
        
        picture_label=new JLabel(new ImageIcon(image));
        image_panel.add(picture_label);
        
        main_panel.add(align_buttons, BorderLayout.NORTH);
        main_panel.add(image_panel, BorderLayout.CENTER);
        main_panel.add(resize_buttons, BorderLayout.SOUTH);
        
        add(main_panel);
        
        setSize(550,675);
        setVisible(true);
    }
    
    public BufferedImage Resize_Image(BufferedImage original_image, int type, int new_width, int new_height){
        BufferedImage resized_image=new BufferedImage(new_width, new_height, type);
        Graphics2D graph_image=resized_image.createGraphics();
        graph_image.drawImage(original_image, 0, 0, new_width, new_height, null);
        graph_image.dispose();
 
        return resized_image;
    }
    
    public void actionPerformed(ActionEvent e){
        if("align_left".equals(e.getActionCommand())){
            image_panel.setLayout(new FlowLayout(FlowLayout.LEFT));
            image_panel.revalidate();
            validate();
            repaint();
        }else if("align_center".equals(e.getActionCommand())){
            image_panel.setLayout(new FlowLayout(FlowLayout.CENTER));
            image_panel.revalidate();
            validate();
            repaint();
        }else if("align_right".equals(e.getActionCommand())){
            image_panel.setLayout(new FlowLayout(FlowLayout.RIGHT));
            image_panel.revalidate();
            validate();
            repaint();
        }else if("resize".equals(e.getActionCommand())){
            picture_label.removeAll();
            image_panel.removeAll();
            BufferedImage resized_image=Resize_Image(image, type, Integer.parseInt(text_width.getText()), Integer.parseInt(text_height.getText()));
            picture_label=new JLabel(new ImageIcon(resized_image));
            picture_label.setPreferredSize(new Dimension(Integer.parseInt(text_width.getText()), Integer.parseInt(text_height.getText())));
            picture_label.revalidate();
            image_panel.add(picture_label);
            image_panel.revalidate();
            validate();
            repaint();
        }else if("reset".equals(e.getActionCommand())){
            picture_label.removeAll();
            image_panel.removeAll();
            picture_label=new JLabel(new ImageIcon(image));
            picture_label.setPreferredSize(new Dimension(start_width, start_height));
            picture_label.revalidate();
            image_panel.setLayout(new FlowLayout(FlowLayout.CENTER));
            image_panel.add(picture_label);
            image_panel.revalidate();
            validate();
            repaint();
        }
    }
}