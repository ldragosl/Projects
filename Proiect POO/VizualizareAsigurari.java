//Copyright Dragos 2021-2022

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.Box;
import javax.swing.BoxLayout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;

public class VizualizareAsigurari extends JFrame {
    private JButton butonInchideMeniu;
    private ListaAsigurari alerte;

    VizualizareAsigurari(){
        super("Meniu asigurator");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        butonInchideMeniu = new JButton("Inchide meniu");

        butonInchideMeniu.setFont(new Font("Serif", Font.PLAIN, 50));

        butonInchideMeniu.setPreferredSize(new Dimension(500, 120));

        JPanel wrapperAlerte = new JPanel();//vrem ca dimensiunea preferata sa fie respectata
        alerte = new ListaAsigurari((int)(getWidth()/1.5), getHeight() / 2);
        wrapperAlerte.add(alerte);

        JPanel panouButoane = new JPanel();

        JPanel panouNord  = new JPanel();
        panouNord.setLayout(new BoxLayout(panouNord, BoxLayout.PAGE_AXIS));

        JLabel textAlerta = new JLabel("Asigurari realizate:");
        textAlerta.setFont(new Font("Serif", Font.PLAIN, 80));
        panouNord.add(Box.createVerticalStrut(100));
        panouNord.add(textAlerta);
        panouNord.add(Box.createVerticalStrut(30));
        panouNord.add(Box.createHorizontalStrut(getWidth() / 10));
        
        panouButoane.add(butonInchideMeniu);
        getContentPane().add(BorderLayout.NORTH, panouNord);
        getContentPane().add(BorderLayout.SOUTH, panouButoane);
        getContentPane().add(BorderLayout.CENTER, wrapperAlerte);

        butonInchideMeniu.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                dispose();
                new MeniuAsigurator();
            } 
        });

    }
}
