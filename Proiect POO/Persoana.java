//Copyright Denis 2021

public class Persoana{
    private String nume;
    private String prenume; 
    private String dataNasterii;
    private String cnp;
    private String adresa;
    private String locMunca;
    
    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public String getCnp() {
        return cnp;
    }

    public String getAdresa() {
        return adresa;
    }

    public String getLocMunca() {
        return locMunca;
    }
    public String getDataNasterii() {
        return dataNasterii;
    }

    Persoana(String nume, String prenume, String cnp, String adresa, String locMunca, String dataNasterii){
        this.nume = nume;
        this.prenume = prenume;
        this.cnp = cnp;
        this.adresa = adresa;
        this.locMunca = locMunca;
        this.dataNasterii = dataNasterii;
    }
    

}