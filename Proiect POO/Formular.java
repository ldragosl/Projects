//Copyright Denis 2021

import java.util.Calendar;

public class Formular {
    //private final double CURS_LEI_EURO = 4.95;
    private final double CURS_LEI_DOLARI = 4.35;
    private final double CURS_EURO_DOLARI = 1.15;

    private Moneda moneda;
    private Frecventa frecventaPlata;
    private double prima;
    private ProgramInvestitii programInvestitii;
    private Persoana persoana;
    private NivelAcoperire acoperire;
    private String numarTelefon;

    public Frecventa getFrecventaPlata() {
        return frecventaPlata;
    }

    public double getPrima() {
        return prima;
    }

    public ProgramInvestitii getProgramInvestitii() {
        return programInvestitii;
    }

    public Moneda getMoneda() {
        return moneda;
    }

    public String getNumarTelefon() {
        return numarTelefon;
    }

    public NivelAcoperire getAcoperire() {
        return acoperire;
    }
    public Persoana getPersoana() {
        return persoana;
    }
    public long calculeazaDataScadenta(){
        Calendar calendar = Calendar.getInstance();

        if(frecventaPlata == Frecventa.ANUAL){
            calendar.add(Calendar.YEAR, 1);
        }
        else if(frecventaPlata == Frecventa.SEMESTRIAL){
            calendar.add(Calendar.MONTH, 6);
        }
        else if(frecventaPlata == Frecventa.TRIMESTRIAL){
            calendar.add(Calendar.MONTH, 4);
        }
        else if(frecventaPlata == Frecventa.LUNAR){
            calendar.add(Calendar.MONTH, 1);
        }

        return calendar.getTime().getTime();
    }

    Formular(String nrTelefon, Moneda moneda, Frecventa frecventaPlata, ProgramInvestitii programInvestitii, NivelAcoperire acoperire, Persoana persoana){
        this.moneda = moneda;
        this.frecventaPlata = frecventaPlata;
        this.programInvestitii = programInvestitii;
        this.acoperire = acoperire;
        this.persoana = persoana;
        this.numarTelefon = nrTelefon;

        if(moneda == Moneda.DOLARI){
            prima = 13.0;
        }
        else if(moneda == Moneda.LEI){
            prima = 13.0 * CURS_LEI_DOLARI;
        }
        else if(moneda == Moneda.EURO){
            prima = 13.0 * CURS_EURO_DOLARI;
        }

        if(frecventaPlata == Frecventa.ANUAL)
            prima *= 12;
        else if(frecventaPlata == Frecventa.SEMESTRIAL)
            prima *= 6;
        else if(frecventaPlata == Frecventa.TRIMESTRIAL)//de 3 ori pe an
            prima *= 4;

        prima += acoperire.getProcentCrestere() / 100.0 * prima;
    }
}

