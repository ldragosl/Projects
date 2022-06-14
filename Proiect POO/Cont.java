//Copyright Dragos 2021

public class Cont {
    private String nume;
    private String parola;
    private boolean esteAgent;

    Cont(String nume, String parola, boolean esteAgent){
        this.nume = nume;
        this.parola = parola;
        this.esteAgent = esteAgent;
    }

    public String getNume() {
        return nume;
    }
    public String getParola() {
        return parola;
    }
    public boolean getEsteAgent(){
        return esteAgent;
    }
}
