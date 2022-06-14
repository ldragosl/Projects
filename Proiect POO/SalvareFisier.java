//Copyright Dragos 2022

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class SalvareFisier {
    public static void salveazaAsigurare(Asigurare salvat){
        try{
            BufferedWriter out=new BufferedWriter(new FileWriter("C:/Users/Utente/Desktop/Proiect/FisiereText/Asigurari.txt", true));
            out.write(salvat.getNumarPolitaAsociat() + "," + salvat.getFormular().getMoneda() + "," + salvat.getFormular().getFrecventaPlata() + "," + salvat.getFormular().getPrima() + "," + salvat.getFormular().getProgramInvestitii() + "," + salvat.getFormular().getNumarTelefon() + "," + salvat.getFormular().getAcoperire().getAcoperire() + "," + salvat.getFormular().getPersoana().getNume() + "," + salvat.getFormular().getPersoana().getPrenume() + "," + salvat.getFormular().getPersoana().getCnp() + "," + salvat.getFormular().getPersoana().getAdresa() + "," + salvat.getFormular().getPersoana().getLocMunca() + "," + salvat.getFormular().getPersoana().getDataNasterii() + "," + salvat.getDeclaratieMedicala().getConsumAlcool() + "," + salvat.getDeclaratieMedicala().getProfesieRiscanta() + "," + salvat.getDeclaratieMedicala().getBoli().size() + ",");
            for(String boala : salvat.getDeclaratieMedicala().getBoli()){
                out.write(boala + ",");
            }
            out.write(salvat.getDeclaratieMedicala().getInterventiiChirurgicale().size() + ",");
            for(String interventieChirurgicala : salvat.getDeclaratieMedicala().getInterventiiChirurgicale()){
                out.write(interventieChirurgicala + ",");
            }
            out.write(String.valueOf(salvat.getFormular().getAcoperire().getSumaAsigurata()));
            out.write("\n");
            out.close();
        }
        catch(IOException e){
            System.out.println("Fisier asigurari negasit");
        }
    }
    public static void salveazaAsigurare(Asigurare salvat, int numar){
        stergeAsigurare(numar);
        salveazaAsigurare(salvat);
    }
    private static void stergeAsigurare(int numar){
        sterge("C:/Users/Utente/Desktop/Proiect/FisiereText/Asigurari.txt", numar);
    }
    public static void salveazaVoucher(Voucher salvat){
        try{
            BufferedWriter out=new BufferedWriter(new FileWriter("C:/Users/Utente/Desktop/Proiect/FisiereText/Vouchere.txt", true));
            out.write(salvat.getNrPolita() + "," + salvat.getNume() + "," + salvat.getCnp() + "," + salvat.getSuma() + "," + salvat.getDataScadenta() + "\n");
            out.close();
        }
        catch(IOException e){
            System.out.println("Fisier vouchere negasit");
        }
    }
    public static void salveazaVoucher(Voucher salvat, int numarAsigurare){
        stergeVoucher(numarAsigurare);
        salveazaVoucher(salvat);
    }
    public static void stergeVoucher(int numarAsigurare){
        sterge("C:/Users/Utente/Desktop/Proiect/FisiereText/Vouchere.txt", numarAsigurare);
    }
    public static void salveazaPolita(PolitaAsigurare salvat){
        try{
            BufferedWriter out=new BufferedWriter(new FileWriter("C:/Users/Utente/Desktop/Proiect/FisiereText/PoliteAsigurare.txt", true));
            out.write(salvat.getNumar() + "," + salvat.getNrTelefon() + "," + salvat.getNume() + "," + salvat.getPrenume() + "," + salvat.getDataNasterii() + "," + salvat.getAdresa() + "," + salvat.getPlanAsigurari() + "," + salvat.getPrima() + "," + salvat.getProgramInvestitii() + "\n");
            out.close();
        }
        catch(IOException e){
            System.out.println("Fisier polite negasit");
        }
    }
    public static void salveazaPolita(PolitaAsigurare salvat, int numarAsigurare){
        stergePolita(numarAsigurare);
        salveazaPolita(salvat);
    }
    public static void stergePolita(int numarAsigurare){
        sterge("C:/Users/Utente/Desktop/Proiect/FisiereText/PoliteAsigurare.txt", numarAsigurare);
    }
    private static void sterge(String carare, int numarAsigurare){
        Scanner intrare = null;
        try{
            intrare = new Scanner(new File(carare));
        }
        catch(FileNotFoundException e){
            System.out.println("Fisierul de sters lipseste");
            return;
        }
        ArrayList<String> randuriCitite = new ArrayList<String>();
        while(intrare.hasNextLine() && intrare.hasNext()){
            String randUrmator = intrare.nextLine();
            String[] randImpartit = randUrmator.split(",");

            if(Integer.valueOf(randImpartit[0]) != numarAsigurare){
                randuriCitite.add(randUrmator);
            }
        }
        intrare.close();

        try{
            BufferedWriter out=new BufferedWriter(new FileWriter(carare, false));
            
            for(String curent : randuriCitite){
                out.write(curent + "\n");
            }
            out.close();
        }
        catch(IOException e){
            System.out.println("Fisier de sters negasit");
        }
    }

    public static void adaugaAsigurareLaCont(String cont, String parola, int numarAsigurare){
        HashSet<Cont> conturi = CitireFisier.citesteConturi(false);
        ContClient contClient = null;
        for(Cont curent : conturi){
            if(curent.getNume().matches(cont)){
                contClient = (ContClient)curent;
            }
        }
        HashSet<Integer> conturiDetiunte = new HashSet<Integer>();
        conturiDetiunte.add(numarAsigurare);
        if(contClient == null){
            contClient = new ContClient(cont, parola, false, conturiDetiunte);
            conturi.add(contClient);
        }
        else {
            contClient.getPoliteAsociate().add(numarAsigurare);
        }

        BufferedWriter scriitor = null;
        try{
            scriitor = new BufferedWriter(new FileWriter("C:/Users/Utente/Desktop/Proiect/FisiereText/ConturiClienti.txt", false));
            for(Cont curent : conturi){
                scriitor.write(curent.getNume() + " " + curent.getParola() + " " + ((ContClient)curent).getPoliteAsociate().size());
                for(Integer i : ((ContClient)curent).getPoliteAsociate()){
                    scriitor.write(" " + i);
                }
                scriitor.write("\n");
            }
            scriitor.close();
        }
        catch(IOException e){
            System.out.println("Fisierul de conturi lipseste");
            return;
        }
    }
}
