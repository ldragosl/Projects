//Copyright Dragos 2021-2022

import java.util.Calendar;
import java.util.HashSet;
import java.util.Date;
import java.util.ArrayList;

import java.text.SimpleDateFormat;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JScrollPane;
import java.awt.Dimension;
import javax.swing.JPanel;
import javax.swing.border.BevelBorder;

public class ListaAsigurari extends JScrollPane{
    protected ArrayList<VizualizatorRapid> intrari;
    protected JPanel deScrolat;

    ListaAsigurari(int marimeX, int marimeY){
        super();

        setHorizontalScrollBarPolicy(HORIZONTAL_SCROLLBAR_NEVER);

        //intrari = new LinkedList<VizualizatorRapid>();//daca o lasam aici aplicatia trimite o exceptie nullpointer

        deScrolat = new JPanel();
        deScrolat.setLayout(new BoxLayout(deScrolat, BoxLayout.PAGE_AXIS));

        setViewportView(deScrolat);

        setPreferredSize(new Dimension(marimeX, marimeY));

        setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));

        afisare(CitireFisier.citesteVouchere());
    }

    protected void afisare(HashSet<Voucher> citite){
        intrari = new ArrayList<VizualizatorRapid>();
        Calendar c = Calendar.getInstance();
        long milisecundeCurente = c.getTime().getTime();
        c.add(Calendar.MONTH, -1);
        final long MILISECUNDE_IN_LUNA = milisecundeCurente - c.getTime().getTime();
        for(Voucher curent : citite){
            c.setTime(new Date(curent.getDataScadenta()));

            if(curent.getDataScadenta() < milisecundeCurente){
                intrari.add(new VizualizatorRapidCuEditare(TipAlerta.NEPLATA, curent.getNume(), new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)), (int)getPreferredSize().getWidth() - 30, (int)getPreferredSize().getHeight() / 5, curent.getNrPolita()));
                //asigurarea nu a fost platita
            }
            else if(curent.getDataScadenta() - MILISECUNDE_IN_LUNA < milisecundeCurente){
                intrari.add(new VizualizatorRapidCuEditare(TipAlerta.EXPIRARE, curent.getNume(), new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)), (int)getPreferredSize().getWidth() - 30, (int)getPreferredSize().getHeight() / 5, curent.getNrPolita()));
                //se apropie data scadenta. Avertizare
            }
            else{
                intrari.add(new VizualizatorRapidCuEditare(TipAlerta.NICIUNA, curent.getNume(), new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)), (int)getPreferredSize().getWidth() - 30, (int)getPreferredSize().getHeight() / 5, curent.getNrPolita()));
                //se afiseaza fara alte actiuni
            }
            intrari.get(intrari.size() - 1).setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
            deScrolat.add(intrari.get(intrari.size() - 1));
        }
    }
}
