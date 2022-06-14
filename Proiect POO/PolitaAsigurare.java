//Copyright Denis 2021

public class PolitaAsigurare {
    private int numar;
    private String nume;
    private String prenume;
    private String dataNasterii;
    private String adresa;
    private PlanAsigurari planAsigurari;
    private double prima;
    private ProgramInvestitii programInvestitii;
    private String nrTelefon;

    public int getNumar() {
        return numar;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public String getDataNasterii() {
        return dataNasterii;
    }

    public String getAdresa() {
        return adresa;
    }

    public PlanAsigurari getPlanAsigurari() {
        return planAsigurari;
    }

    public double getPrima() {
        return prima;
    }

    public ProgramInvestitii getProgramInvestitii() {
        return programInvestitii;
    }

    public String getNrTelefon() {
        return nrTelefon;
    }

    PolitaAsigurare(int numarPolitaAsigurare, String numarTelefon, String nume, String prenume, String dataNasterii, String adresa, PlanAsigurari planAsigurari, double prima, ProgramInvestitii programInvestitii){
        this.numar = numarPolitaAsigurare;
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.adresa = adresa;
        this.planAsigurari = planAsigurari;
        this.prima = prima;
        this.programInvestitii = programInvestitii;
        this.nrTelefon = numarTelefon;
    }

}
