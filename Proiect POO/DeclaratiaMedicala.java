//Copyright Denis 2021

import java.util.Set;
public class DeclaratiaMedicala {
    private Set<String> boli;
    private boolean consumAlcool;
    private Set<String> interventiiChirurgicale;
    private boolean profesieRiscanta;

    public Set<String> getBoli() {
        return boli;
    }

    public boolean getConsumAlcool(){
        return consumAlcool;
    }

    public Set<String> getInterventiiChirurgicale() {
        return interventiiChirurgicale;
    }
    public boolean getProfesieRiscanta(){
        return profesieRiscanta;
    }

    DeclaratiaMedicala(Set<String> boli, boolean consumAlcool, Set<String> interventii, boolean profesieRiscanta){
        this.boli = boli;
        this.consumAlcool = consumAlcool;
        this.interventiiChirurgicale = interventii;
        this.profesieRiscanta = profesieRiscanta;
    }
    



}
