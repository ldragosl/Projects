//Copyright Denis 2021

public class Voucher {
    private int nrPolita;
    private String nume;
    private String cnp;
    private double suma;
    private long dataScadenta;//in milisecunde din 1970

    public int getNrPolita() {
        return nrPolita;
    }

    public String getNume() {
        return nume;
    }

    public String getCnp() {
        return cnp;
    }

    public double getSuma() {
        return suma;
    }

    public long getDataScadenta() {
        return dataScadenta;
    }

    public void setDataScadenta(long dataScadenta) {
        this.dataScadenta = dataScadenta;
    }

    Voucher(int numarPolitaAsigurare, String nume, String cnp, double suma, long dataScadenta){
        this.nrPolita = numarPolitaAsigurare;
        this.nume = nume;
        this.cnp = cnp;
        this.suma = suma;
        this.dataScadenta = dataScadenta;
    }
}
