//Copyright Dragos 2021-2022

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;

public class CitireFisier {
    static public HashSet<Cont> citesteConturi(){
        HashSet<Cont> c = citesteConturi(true);
        c.addAll(citesteConturi(false));
        return c;
    }

    static private HashSet<Integer> citestePoliteAsociate(Scanner sursa){
        HashSet<Integer> citit = new HashSet<Integer>();
        int n = sursa.nextInt();
        for(int i = 0; i < n; i++){
            citit.add(sursa.nextInt());
        }
        return citit;
    }

    static public Voucher citesteVoucher(int numar){
        HashSet<Voucher> citite = citesteVouchere();
        for(Voucher curent : citite)
            if(curent.getNrPolita() == numar)
                return curent;
        return null;
    }
    
    static public HashSet<Cont> citesteConturi(boolean doarAgenti /*Daca e true, vor fii citit doar agentii. Altfel, doar clientii */){
        Scanner intrare = null;
        HashSet<Cont> conturi = new HashSet<Cont>();
        try{
            if(doarAgenti){
                intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/ConturiAsiguratori.txt"));
            }
            else{
                intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/ConturiClienti.txt"));
            }
        }
        catch(FileNotFoundException e){
            System.out.println("Nu avem fisier conturi!");
            return conturi;
        }
        while(intrare.hasNextLine() && intrare.hasNext()){
            if(doarAgenti){
                conturi.add(new Cont(intrare.next(), intrare.next(), doarAgenti));
            }
            else{
                conturi.add(new ContClient(intrare.next(), intrare.next(), doarAgenti, citestePoliteAsociate(intrare)));
            }
        }
        return conturi;
    }
    static public HashSet<Voucher> citesteVouchere(){
        HashSet<Voucher> citite = new HashSet<Voucher>();
        Scanner intrare = null;
        try{
            intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/Vouchere.txt"));
        }
        catch(FileNotFoundException e){
            System.out.println("Fisierul de vouchere lipseste");
            return citite;
        }
        while(intrare.hasNextLine() && intrare.hasNext()){
            String[] randCitit = intrare.nextLine().split(",");

            citite.add(new Voucher(Integer.valueOf(randCitit[0]), randCitit[1], randCitit[2], Double.valueOf(randCitit[3]), Long.valueOf(randCitit[4])));
        }
        return citite;
    }
    static public HashSet<PolitaAsigurare> citestePolite(){
        HashSet<PolitaAsigurare> citite = new HashSet<PolitaAsigurare>();
        Scanner intrare = null;
        try{
            intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/PoliteAsigurare.txt"));
        }
        catch(FileNotFoundException e){
            System.out.println("Fisierul de asigurari lipseste");
            return citite;
        }
        while(intrare.hasNextLine() && intrare.hasNext()){
            String[] randCitit = intrare.nextLine().split(",");

            citite.add(new PolitaAsigurare(Integer.valueOf(randCitit[0]), randCitit[1], randCitit[2], randCitit[3], randCitit[4], randCitit[5], PlanAsigurari.valueOf(randCitit[6]), Double.valueOf(randCitit[7]), ProgramInvestitii.valueOf(randCitit[8])));
        }
        return citite;
    }
    static public int citesteNumarPolite(){
        int numarPoliteCitite = 0;
        Scanner intrare = null;
        try{
            intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/Vouchere.txt"));
        }
        catch(FileNotFoundException e){
            System.out.println("Fisierul de vouchere lipseste");
            return 0;
        }
        while(intrare.hasNextLine() && intrare.hasNext()){
            intrare.nextLine();
            numarPoliteCitite++;
        }
        return numarPoliteCitite;
    }
    static public Asigurare citesteAsigurare(int numarAsigurareCitit){
        Scanner intrare = null;
        try{
            intrare = new Scanner(new File("C:/Users/Utente/Desktop/Proiect/FisiereText/Asigurari.txt"));
        }
        catch(FileNotFoundException e){
            System.out.println("Fisierul de asigurari lipseste");
            return null;
        }        
        while(intrare.hasNextLine() && intrare.hasNext()){
            String[] randCitit = intrare.nextLine().split(",");
            if(numarAsigurareCitit == Integer.valueOf(randCitit[0])){
                HashSet<String> boli = new HashSet<String>();
                HashSet<String> interventii = new HashSet<String>();
                int nrBoli = Integer.valueOf(randCitit[15]);
                for(int i = 0; i < nrBoli; i++){
                    boli.add(randCitit[16+i]);
                }
                int nrInterventii = Integer.valueOf(randCitit[16 + nrBoli]);
                for(int i = 0; i < nrInterventii; i++){
                    interventii.add(randCitit[17+i+nrBoli]);
                }
                NivelAcoperire acoperire = new NivelAcoperire(Acoperire.valueOf(randCitit[6]));
                acoperire.incrementareSumaAsigurata(Double.valueOf(randCitit[17 + nrBoli + nrInterventii]));
                
                return new Asigurare(new Formular(randCitit[5], Moneda.valueOf(randCitit[1]), Frecventa.valueOf(randCitit[2]), ProgramInvestitii.valueOf(randCitit[4]), acoperire, new Persoana(randCitit[7], randCitit[8], randCitit[9], randCitit[10], randCitit[11], randCitit[12])), new DeclaratiaMedicala(boli, Boolean.valueOf(randCitit[13]), interventii, Boolean.valueOf(randCitit[14])), numarAsigurareCitit);
            }
        }

        return null;
    }
}
