//Copyright Denis 2021

public class NivelAcoperire {
    private Acoperire acoperire;
    private double procentCrestere;
    private double sumaAsigurata;
    public Acoperire getAcoperire() {
        return acoperire;
    }

    public double getProcentCrestere() {
        return procentCrestere;
    }

    public double getSumaAsigurata() {
        return sumaAsigurata;
    }

    public void incrementareSumaAsigurata(double deAdaugat){
        sumaAsigurata += deAdaugat;
    }

    NivelAcoperire(Acoperire acoperire){
        this.acoperire = acoperire;
        this.sumaAsigurata = 0.0;
        if(acoperire == Acoperire.MAXIM){
            procentCrestere=50.0;
        }  
        else if(acoperire == Acoperire.STANDARD){
            procentCrestere=25.0;
        }
        else if(acoperire == Acoperire.MINIM){
            procentCrestere=0.0;
        }

    }


}
