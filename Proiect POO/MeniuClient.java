//Copyright Denis 2022

import javax.swing.JFrame;
import javax.swing.ImageIcon;
import java.util.HashSet;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.Box;
import javax.swing.BoxLayout;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MeniuClient extends JFrame {
    private JButton butonVizualizarePolita;
    private JButton butonVizualizareVoucher;

    MeniuClient(HashSet<Integer> politeAsociate){
        super("Meniu Client");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);

        butonVizualizarePolita = new JButton("Vizualizare polite");
        butonVizualizareVoucher = new JButton("Vizualizare vouchere");

        butonVizualizarePolita.setFont(new Font("Serif", Font.PLAIN, 50));
        butonVizualizareVoucher.setFont(new Font("Serif", Font.PLAIN, 50));

        butonVizualizarePolita.setPreferredSize(new Dimension(500, 120));
        butonVizualizareVoucher.setPreferredSize(new Dimension(500, 120));

        JPanel panouButoane = new JPanel();

        JPanel panouNord  = new JPanel();
        panouNord.setLayout(new BoxLayout(panouNord, BoxLayout.PAGE_AXIS));

        add(new JLabel(new ImageIcon("C:/Users/Utente/Desktop/Proiect/FisiereText/image.jpg")));

        butonVizualizareVoucher.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                dispose();
                new VizualizareVoucher(politeAsociate);
            } 
        });

        butonVizualizarePolita.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                dispose();
                new VizualizarePolita(politeAsociate);
            }
        });

        panouButoane.add(butonVizualizarePolita);
        panouButoane.add(Box.createHorizontalStrut(100));
        panouButoane.add(butonVizualizareVoucher);
        getContentPane().add(BorderLayout.NORTH, panouNord);
        getContentPane().add(BorderLayout.SOUTH, panouButoane);

    }
}
