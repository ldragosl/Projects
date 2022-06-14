//Copyright Dragos 2021

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Font;


public class MeniuPrincipal extends JFrame {
    JButton butonClient;
    JButton butonAgent;
    MeniuPrincipal(){
        super("Meniu principal");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);

        butonAgent = new JButton("Agent");
        butonClient = new JButton("Client");

        JLabel intrebare = new JLabel("In ce scop utilizati programul?", SwingConstants.CENTER);

        intrebare.setFont(new Font("Serif", Font.PLAIN, 70));
        butonAgent.setFont(new Font("Serif", Font.PLAIN, 100));
        butonClient.setFont(new Font("Serif", Font.PLAIN, 100));

        //intrebare.setForeground(Color.RED);

        //butonAgent.setPreferredSize(new Dimension(300, 80));
        //butonClient.setPreferredSize(new Dimension(300, 80));
        
        intrebare.setBounds(getWidth() / 2 - 500, 10, 1000, 100);

        //getContentPane().add(BorderLayout.WEST, butonAgent);
        //getContentPane().add(BorderLayout.EAST, butonClient);
        setLayout(null);

        butonClient.setBounds(100, 150, getWidth() / 2 - 150, getHeight() - 250);

        butonAgent.setBounds(25 + getWidth() / 2, 150, getWidth() / 2 - 150, getHeight() - 250);

        add(butonClient);
        add(butonAgent);
        add(intrebare);

        butonAgent.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                new LogareAsigurator();
                dispose();
            } 
        });
        butonClient.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                new LogareClient(); 
                dispose();
            } 
        });

        repaint();//fara aceasta catoedata nu apar butoanele
    }
}
