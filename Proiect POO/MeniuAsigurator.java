//Copyright Dragos 2021

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.Box;
import javax.swing.BoxLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MeniuAsigurator extends JFrame {
    
    private JButton butonCreeazaAsigurare;
    private JButton butonVizualizareAsigurari;
    private Alerte alerte;

    MeniuAsigurator(){
        super("Meniu asigurator");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);

        butonCreeazaAsigurare = new JButton("Creeaza asigurare noua");
        butonVizualizareAsigurari = new JButton("Vizualizare asigurari");

        butonCreeazaAsigurare.setFont(new Font("Serif", Font.PLAIN, 50));
        butonVizualizareAsigurari.setFont(new Font("Serif", Font.PLAIN, 50));

        butonVizualizareAsigurari.setPreferredSize(new Dimension(500, 120));
        butonCreeazaAsigurare.setPreferredSize(new Dimension(500, 120));

        JPanel wrapperAlerte = new JPanel();//vrem ca dimensiunea preferata sa fie respectata
        alerte = new Alerte((int)(getWidth()/1.5), getHeight() / 2);
        wrapperAlerte.add(alerte);

        JPanel panouButoane = new JPanel();

        JPanel panouNord  = new JPanel();
        panouNord.setLayout(new BoxLayout(panouNord, BoxLayout.PAGE_AXIS));

        JLabel textAlerta = new JLabel("Alerte expirare:");
        textAlerta.setFont(new Font("Serif", Font.PLAIN, 80));
        panouNord.add(Box.createVerticalStrut(100));
        panouNord.add(textAlerta);
        panouNord.add(Box.createVerticalStrut(30));
        panouNord.add(Box.createHorizontalStrut(getWidth() / 10));
        

        panouButoane.add(butonCreeazaAsigurare);
        panouButoane.add(Box.createHorizontalStrut(100));
        panouButoane.add(butonVizualizareAsigurari);
        getContentPane().add(BorderLayout.NORTH, panouNord);
        getContentPane().add(BorderLayout.SOUTH, panouButoane);
        getContentPane().add(BorderLayout.CENTER, wrapperAlerte);

        butonCreeazaAsigurare.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                dispose();
                new MeniuCreareAsigurare(-1);
            } 
        });
        butonVizualizareAsigurari.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                dispose();
                new VizualizareAsigurari();
            } 
        });

    }

}
