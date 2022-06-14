//Copyright Dragos 2021

import java.util.Calendar;
import java.util.HashSet;
import java.util.Date;
import java.util.LinkedList;

import java.text.SimpleDateFormat;

import javax.swing.BorderFactory;
import javax.swing.border.BevelBorder;

public class Alerte extends ListaAsigurari {
    private LinkedList<VizualizatorRapid> intrari;

    Alerte(int marimeX, int marimeY){
        super(marimeX, marimeY);
    }
    @Override
    protected void afisare(HashSet<Voucher> citite){
        intrari = new LinkedList<VizualizatorRapid>();
        Calendar c = Calendar.getInstance();
        long milisecundeCurente = c.getTime().getTime();
        c.add(Calendar.MONTH, -1);
        final long MILISECUNDE_IN_LUNA = milisecundeCurente - c.getTime().getTime();

        for(Voucher curent : citite){
            c.setTime(new Date(curent.getDataScadenta()));
            

            if(curent.getDataScadenta() < milisecundeCurente){
                intrari.add(new VizualizatorRapid(TipAlerta.NEPLATA, curent.getNume(), "Data scadenta: " + new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)), (int)getPreferredSize().getWidth() - 30, (int)getPreferredSize().getHeight() / 5));
                //asigurarea nu a fost platita
                intrari.get(intrari.size() - 1).setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
                deScrolat.add(intrari.get(intrari.size() - 1));
            }
            else if(curent.getDataScadenta() - MILISECUNDE_IN_LUNA < milisecundeCurente){
                intrari.add(new VizualizatorRapid(TipAlerta.EXPIRARE, curent.getNume(), "Data scadenta: " + new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)), (int)getPreferredSize().getWidth() - 30, (int)getPreferredSize().getHeight() / 5));
                //se apropie data scadenta. Avertizare
                intrari.get(intrari.size() - 1).setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
                deScrolat.add(intrari.get(intrari.size() - 1));
            }
        }
    }
}
