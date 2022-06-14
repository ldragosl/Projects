//Copyright Dragos 2021

import javax.swing.JPanel;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Dimension;

class VizualizatorRapid extends JPanel{
    private TipAlerta tipAlerta;

    protected JLabel nume;
    protected JLabel dataExpirare;

    VizualizatorRapid(TipAlerta tipAlerta, String nume, String dataExpirare, int marimeX, int marimeY){
        super();
        this.tipAlerta = tipAlerta;
        this.nume = new JLabel(nume);
        this.dataExpirare = new JLabel(dataExpirare);

        this.nume.setFont(new Font("DialogInput", Font.PLAIN, (int)(marimeY/2)));
        this.dataExpirare.setFont(new Font("DialogInput", Font.PLAIN, (int)(marimeY/2.6)));
        setPreferredSize(new Dimension(marimeX, marimeY));

        if(this.tipAlerta == TipAlerta.NEPLATA)
            setBackground(Color.RED);
        else if (this.tipAlerta == TipAlerta.EXPIRARE)
            setBackground(Color.YELLOW);
        else setBackground(Color.GREEN);

        setBorder(BorderFactory.createLineBorder(getBackground()));
        configurare();
    }

    protected void configurare(){
        setLayout(new GridLayout(0, 2));
        add(this.nume);
        add(this.dataExpirare);
    }
}