//Copyright Dragos 2022

import java.util.HashSet;

public class ContClient extends Cont{
    private HashSet<Integer> politeAsociate; 

    ContClient(String nume, String parola, boolean esteAgent, HashSet<Integer> polite){
        super(nume, parola, esteAgent);

        politeAsociate = polite;
    }

    public HashSet<Integer> getPoliteAsociate() {
        return politeAsociate;
    }
}
