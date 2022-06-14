//Copyright Dragos 2021

import javax.swing.JLabel;
import javax.swing.SwingUtilities;

import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VizualizatorRapidCuEditare extends VizualizatorRapid{

    private JButton butonEditare;

    private JFrame obtineFrameParinte(){
        return (JFrame)SwingUtilities.getRoot(this);
    }

    VizualizatorRapidCuEditare(TipAlerta tipAlerta, String nume, String dataExpirare, int marimeX, int marimeY, int numarAsigurare){
        super(tipAlerta, nume, dataExpirare, marimeX, marimeY);

        this.dataExpirare.setHorizontalAlignment(JLabel.CENTER);

        butonEditare.setFont(new Font("DialogInput", Font.PLAIN, (int)(marimeY/2.6)));

        butonEditare.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                obtineFrameParinte().dispose();
                new MeniuCreareAsigurare(numarAsigurare);
            } 
        });
    }

    @Override
    protected void configurare() {
        butonEditare = new JButton("Editeaza");

        setLayout(new GridLayout(0, 3));
        add(this.nume);
        add(this.dataExpirare);
        add(butonEditare);
    }
}