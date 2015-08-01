import java.awt.*; 
import java.awt.event.*;
import javax.swing.*; 

public class Puzzle_Game extends java.applet.Applet{ 
    JButton[] button_table=new JButton[9]; 
    String[] button_label={"1", "2", "3", "4", "5", "6", "7", "8"}; 
    boolean[] verification={false, false, false, false, false, false, false, false}; 
    int moves; 
    JPanel game_panel=new JPanel(); 
    JPanel main_panel=new JPanel(new GridLayout(3,3, 10, 10)); 
    JPanel move_panel=new JPanel(new FlowLayout()); 
    JLabel move_text; 
    JLabel game_moves; 
    JButton new_game_button;

    public void init(){
        setSize(390, 450);
        setVisible(true); 
        setLayout(new BorderLayout()); 
        new_game_button=new JButton("New Game");
        
        new_game_button.addActionListener(new ActionListener(){ 
            public void actionPerformed(ActionEvent ae){ 
                moves=0; 
                game_moves.setText(Integer.toString(moves));
                
                for(int i=0; i<8; i++){
                    verification[i]=false;
                }
                
                for(int i=0;i<8;i++){
                    Button_Loop: for(;;){ 
                        int x=(int)(Math.random()*8); 
                
                        if(verification[x]) { 
                            continue Button_Loop; 
                        }else{ 
                            button_table[i].setText(button_label[x]);
                            button_table[i].setBackground(new Color(238, 238, 224));
                            verification[x]=true; 
                            break;
                        }
                    }
                } 
                
                boolean end_loop=false;
                
                for(int i=0;i<9;i++){
                    for(int j=0;j<9;j++){                        
                        if(i!=j && button_table[i].getText()==button_table[j].getText()){
                            button_table[i].setText("");
                            button_table[i].setBackground(Color.black);
                            end_loop=true;
                            break;
                        }
                            
                        if (end_loop==true){
                            return;
                        }
                    }
                }
            } 
        });

        game_panel.add(new_game_button);
        main_panel.setBackground(Color.black);
        
        move_text=new JLabel("Moves:"); 
        game_moves=new JLabel("0");
        move_panel.add(move_text); 
        move_panel.add(game_moves);
        
        add(game_panel, BorderLayout.NORTH); 
        add(main_panel, BorderLayout.CENTER); 
        add(move_panel, BorderLayout.SOUTH);
        
        moves=0; 
        game_moves.setText(Integer.toString(moves));
    
        for(int i=0;i<9;i++){ 
            button_table[i]=new JButton("");
            button_table[i].setFont(new Font("Tahoma", Font.BOLD, 35));
            button_table[i].setForeground(new Color(131, 139, 131));
            button_table[i].setBackground(Color.black);
            main_panel.add(button_table[i]);
        }

        for(int i=0;i<8;i++){
            Button_Loop: for(;;){ 
                int x=(int)(Math.random()*8); 
                
                if(verification[x]){ 
                    continue Button_Loop; 
                }else{ 
                    button_table[i].setText(button_label[x]);
                    button_table[i].setBackground(new Color(238, 238, 224));
                    verification[x]=true; 
                    break;
                }
            }
        } 

        for(int i=0;i<9;i++){ 
            button_table[i].addActionListener(new ActionListener(){ 
                public void actionPerformed(ActionEvent ae){ 
                    if((ae.getSource()).equals(button_table[0])){ 
                        button_swap(0,1);
                        button_swap(0,3); 
                    }

                    if((ae.getSource()).equals(button_table[1])){ 
                        button_swap(1,0); 
                        button_swap(1,4); 
                        button_swap(1,2); 
                    } 
    
                    if((ae.getSource()).equals(button_table[2])){ 
                        button_swap(2,1); 
                        button_swap(2,5); 
                    } 
    
                    if((ae.getSource()).equals(button_table[3])){
                        button_swap(3,0); 
                        button_swap(3,4); 
                        button_swap(3,6); 
                    } 
    
                    if((ae.getSource()).equals(button_table[4])){
                        button_swap(4,1);
                        button_swap(4,3);
                        button_swap(4,5); 
                        button_swap(4,7); 
                    } 

                    if((ae.getSource()).equals(button_table[5])){ 
                        button_swap(5,2); 
                        button_swap(5,4); 
                        button_swap(5,8); 
                    }

                    if((ae.getSource()).equals(button_table[6])){ 
                        button_swap(6,3); 
                        button_swap(6,7); 
                    } 
    
                    if((ae.getSource()).equals(button_table[7])){ 
                        button_swap(7,4); 
                        button_swap(7,6); 
                        button_swap(7,8); 
                    } 
    
                    if((ae.getSource()).equals(button_table[8])){ 
                        button_swap(8,7);
                        button_swap(8,5);
                    } 
                } 
            });
        }
    }

    public void button_swap(int x, int y){ 
        if((button_table[y].getText()).equals("")){ 
            button_table[y].setText(button_table[x].getText());
            button_table[y].setBackground(new Color(238, 238, 224));
            button_table[x].setText("");
            button_table[x].setBackground(Color.black);
            moves++; 
            game_moves.setText(Integer.toString(moves)); 
            check(); 
        } 
    } 

    public void check(){ 
        int button_number;
        boolean end_game=true;
        
        for(int i=0;i<8;i++){ 
            if(button_table[i].getText().equals("")){
                return;
            }
            
            button_number=Integer.parseInt(button_table[i].getText());
            
            if(button_number!=i+1){
                end_game=false;
            }
        }
        
        if(end_game==true){
            JOptionPane.showMessageDialog(null, "Well Done!");
        }
    }
}