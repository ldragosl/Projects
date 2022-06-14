//Copyright Denis 2021

public class Asigurare {
    private int numarPolitaAsociat;
    private Formular formular;
    private DeclaratiaMedicala declaratieMedicala;
    public int getNumarPolitaAsociat() {
        return numarPolitaAsociat;
    }
    public DeclaratiaMedicala getDeclaratieMedicala() {
        return declaratieMedicala;
    }
    public Formular getFormular() {
        return formular;
    }
    public PolitaAsigurare obtinePolitaAsigurare(){
        return new PolitaAsigurare(numarPolitaAsociat, formular.getNumarTelefon(), formular.getPersoana().getNume(), formular.getPersoana().getPrenume(), formular.getPersoana().getDataNasterii(), formular.getPersoana().getAdresa(), PlanAsigurari.PENSII, formular.getPrima(), formular.getProgramInvestitii());
    }
    public Voucher creeazaVoucher(){
        return new Voucher(numarPolitaAsociat, formular.getPersoana().getNume()+ " " + formular.getPersoana().getPrenume(), formular.getPersoana().getCnp(), formular.getPrima(), formular.calculeazaDataScadenta());
    }
    Asigurare(Formular formular, DeclaratiaMedicala declaratiaMedicala){
        this.numarPolitaAsociat = CitireFisier.citesteNumarPolite() + 1;
        this.formular = formular;
        this.declaratieMedicala = declaratiaMedicala;
    }
    Asigurare(Formular formular, DeclaratiaMedicala declaratiaMedicala, int nrPolitaAsociat){
        this.numarPolitaAsociat = nrPolitaAsociat;
        this.formular = formular;
        this.declaratieMedicala = declaratiaMedicala;
    }

    
}
