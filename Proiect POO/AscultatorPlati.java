//Copyright Dragos 2022
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JOptionPane;

public class AscultatorPlati implements ActionListener{
    int numarAsigurare;
    VizualizareVoucher meniuVechi;
    AscultatorPlati(int numarAsigurare, VizualizareVoucher meniuVechi){
        this.numarAsigurare = numarAsigurare;
        this.meniuVechi = meniuVechi;
    }

    public void actionPerformed(ActionEvent e){
        Calendar calendar = Calendar.getInstance();
        long milisecundeCurente = calendar.getTime().getTime();
        for(Voucher curent : CitireFisier.citesteVouchere()){
            calendar.setTime(new Date(curent.getDataScadenta()));
            if(curent.getNrPolita() == numarAsigurare && curent.getDataScadenta() > milisecundeCurente){
                JOptionPane.showMessageDialog(null, "Plata a fost inregistrata cu succes.");

                Asigurare asig = CitireFisier.citesteAsigurare(numarAsigurare);

                asig.getFormular().getAcoperire().incrementareSumaAsigurata(asig.getFormular().getPrima());
                double sumaRealizataDeCompanie = (Math.random() - 0.3) * asig.getFormular().getPrima();//compania realizeaza profit intre -30% si 70%, indiferent de valuta
                Frecventa frecventaPlata = asig.getFormular().getFrecventaPlata();

                if(frecventaPlata == Frecventa.ANUAL){
                    calendar.add(Calendar.YEAR, 1);
                }
                else if(frecventaPlata == Frecventa.SEMESTRIAL){
                    calendar.add(Calendar.MONTH, 6);
                    sumaRealizataDeCompanie/=2;
                }
                else if(frecventaPlata == Frecventa.TRIMESTRIAL){
                    calendar.add(Calendar.MONTH, 4);
                    sumaRealizataDeCompanie/=3;
                }
                else if(frecventaPlata == Frecventa.LUNAR){
                    calendar.add(Calendar.MONTH, 1);
                    sumaRealizataDeCompanie/=12;
                }

                asig.getFormular().getAcoperire().incrementareSumaAsigurata(sumaRealizataDeCompanie * 0.25);

                Voucher voucherNou = new Voucher(curent.getNrPolita(), curent.getNume(), curent.getCnp(), curent.getSuma(), calendar.getTime().getTime());

                SalvareFisier.salveazaVoucher(voucherNou, voucherNou.getNrPolita());
                SalvareFisier.salveazaAsigurare(asig, asig.getNumarPolitaAsociat());

                new VizualizareVoucher(meniuVechi.getPoliteCitite());
                meniuVechi.dispose();
                
                return;
            }
        }
        JOptionPane.showMessageDialog(null, "Plata nu a putut fii procesata: voucher invalid/expirat.", "Eroare plata", JOptionPane.ERROR_MESSAGE);
    }
}
