//Copyright Dragos 2022

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import java.awt.Color;
import java.awt.Dimension;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;

import javax.swing.Box;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashSet;
import java.awt.Font;
import javax.swing.JLabel;
import java.awt.GridLayout;

public class MeniuCreareAsigurare extends JFrame {
    private int numarAsigurare;
    private Asigurare asigurareEliberata;
    private PolitaAsigurare politaEliberata;
    private Voucher voucherEliberat;

    //chemat intotdeauna inainte de accesarea unui element de formular!
    private void validareExistentaFormular(){
        if(asigurareEliberata == null)
            modificareFormular();
    }

    private void modificareFormular(){
        HashSet<String> s_boli = new HashSet<String>();
        HashSet<String> s_interventii = new HashSet<String>();
        for(JTextField curent : interventiiChirgicale){
            s_interventii.add(curent.getText());
        }
        for(JTextField curent : boli){
            s_boli.add(curent.getText());
        }

        DeclaratiaMedicala declaratieMedicala = new DeclaratiaMedicala(s_boli, consumAlcool.isSelected(), s_interventii, profesieRiscanta.isSelected());
        Persoana persoanaDeclarata = new Persoana(campNume.getText(), campPrenume.getText(), campCnp.getText(), campAdresa.getText(), campLocMunca.getText(), campDataNasterii.getText());
        NivelAcoperire nivelAcoperireDeclarat = new NivelAcoperire((Acoperire)selectorAcoperire.getSelectedItem());
        if(numarAsigurare > 0){
            nivelAcoperireDeclarat.incrementareSumaAsigurata(CitireFisier.citesteAsigurare(numarAsigurare).getFormular().getAcoperire().getSumaAsigurata());
        }
        Formular formularCompletat = new Formular(campNumarTelefon.getText(), (Moneda)selectorMoneda.getSelectedItem(), (Frecventa)selectorFrecventaPlata.getSelectedItem(), (ProgramInvestitii)selectorProgramInvestitii.getSelectedItem(), nivelAcoperireDeclarat, persoanaDeclarata);
        if(numarAsigurare > 0)
            asigurareEliberata = new Asigurare(formularCompletat, declaratieMedicala, numarAsigurare);
        else asigurareEliberata = new Asigurare(formularCompletat, declaratieMedicala);
        politaEliberata = asigurareEliberata.obtinePolitaAsigurare();
        voucherEliberat = asigurareEliberata.creeazaVoucher();
        if(numarAsigurare > 0){
            voucherEliberat.setDataScadenta(CitireFisier.citesteVoucher(numarAsigurare).getDataScadenta());
        }
    }



    private JButton butonSalvare;
    private JButton butonAnulare;

    private JPanel panouDeclaratieMedicala;

    private JLabel eroare;

    private JTextField campNume;
    private JTextField campPrenume;
    private JTextField campCnp;
    private JTextField campAdresa;
    private JTextField campLocMunca;
    private JTextField campDataNasterii;
    private JComboBox<Moneda> selectorMoneda;
    private JComboBox<Frecventa> selectorFrecventaPlata;
    private JComboBox<ProgramInvestitii> selectorProgramInvestitii;
    private JComboBox<Acoperire> selectorAcoperire;
    private JCheckBox consumAlcool;
    private JCheckBox profesieRiscanta;
    private JTextField campNumarTelefon;
    private JTextField campProcentCrestere;
    private ArrayList<JTextField> interventiiChirgicale;
    private ArrayList<JTextField> boli;
    private JButton adaugaInterventie;
    private JButton adaugaBoala;
    private JTextField campSumaAcoperita;
    private JTextField campPrima;
    private JTextField campDataScadenta;
    private JTextField campContAsociat;
    private JTextField campParola;

    private void adaugareCampBoala(){
        JLabel textInterventie = new JLabel("Boala nr. " + (boli.size()+1));
        textInterventie.setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(textInterventie);
        boli.add(new JTextField());
        boli.get(boli.size() - 1).setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(boli.get(boli.size() - 1));
    }

    private void adaugareCampBoala(String boalaAdaugata, boolean editabil){
        JLabel textInterventie = new JLabel("Boala nr. " + (boli.size()+1));
        textInterventie.setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(textInterventie);
        boli.add(new JTextField());
        boli.get(boli.size() - 1).setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(boli.get(boli.size() - 1));
        boli.get(boli.size() - 1).setEnabled(editabil);
        boli.get(boli.size() - 1).setText(boalaAdaugata);
    }

    private void adaugareCampInterventieChirurgicala(){
        interventiiChirgicale.add(new JTextField());
        interventiiChirgicale.get(interventiiChirgicale.size() - 1).setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(interventiiChirgicale.get(interventiiChirgicale.size() - 1), 2);
        JLabel textInterventie = new JLabel("Interventie nr. " + interventiiChirgicale.size());
        textInterventie.setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(textInterventie, 2);
    }

    private void adaugareCampInterventieChirurgicala(String interventieAdaugata, boolean editabil){
        interventiiChirgicale.add(new JTextField());
        interventiiChirgicale.get(interventiiChirgicale.size() - 1).setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(interventiiChirgicale.get(interventiiChirgicale.size() - 1), 2);
        interventiiChirgicale.get(interventiiChirgicale.size() - 1).setEnabled(editabil);
        interventiiChirgicale.get(interventiiChirgicale.size() - 1).setText(interventieAdaugata);
        JLabel textInterventie = new JLabel("Interventie nr. " + interventiiChirgicale.size());
        textInterventie.setFont(new Font("Serif", Font.PLAIN, 30));
        panouDeclaratieMedicala.add(textInterventie, 2);
    }

    private void afisarePrima(){
        validareExistentaFormular();

        campPrima.setText(String.format("%.2f", asigurareEliberata.getFormular().getPrima()));
        Calendar c = Calendar.getInstance();
        c.setTime(new Date(asigurareEliberata.getFormular().calculeazaDataScadenta()));
        campDataScadenta.setText(new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)));
    }

    MeniuCreareAsigurare(int numarAsigurareEditat){
        super("Creare asigurare");

        numarAsigurare = numarAsigurareEditat;

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS));

        JPanel wrapper = new JPanel();
        wrapper.setLayout(new BoxLayout(wrapper, BoxLayout.PAGE_AXIS));

        JScrollPane scrollare = new JScrollPane(wrapper);
        scrollare.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

        JPanel panouPersoana = new JPanel();
        JPanel panouFormular = new JPanel();
        JPanel panouContinutFormular = new JPanel();
        JPanel panouAcoperire = new JPanel();
        panouDeclaratieMedicala = new JPanel();

        panouContinutFormular.setLayout(new GridLayout(0, 2));
        panouPersoana.setLayout(new GridLayout(0, 2));
        panouAcoperire.setLayout(new GridLayout(0, 2));
        panouDeclaratieMedicala.setLayout(new GridLayout(0, 2));
        panouFormular.setLayout(new BoxLayout(panouFormular, BoxLayout.PAGE_AXIS));

        JLabel textNume = new JLabel("Nume");
        textNume.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textNume);
        campNume = new JTextField();
        campNume.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campNume);

        JLabel textPrenume = new JLabel("Prenume");
        textPrenume.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textPrenume);
        campPrenume = new JTextField();
        campPrenume.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campPrenume);

        JLabel textCnp = new JLabel("CNP");
        textCnp.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textCnp);
        campCnp = new JTextField();
        campCnp.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campCnp);

        JLabel textAdresa = new JLabel("Adresa");
        textAdresa.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textAdresa);
        campAdresa = new JTextField();
        campAdresa.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campAdresa);

        JLabel textLocMunca = new JLabel("Loc munca");
        textLocMunca.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textLocMunca);
        campLocMunca = new JTextField();
        campLocMunca.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campLocMunca);

        JLabel textDataNasterii = new JLabel("Data nasterii");
        textDataNasterii.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(textDataNasterii);
        campDataNasterii = new JTextField();
        campDataNasterii.setFont(new Font("Serif", Font.PLAIN, 40));
        panouPersoana.add(campDataNasterii);

        JLabel textTelefon = new JLabel("Numar telefon: ");
        textTelefon.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textTelefon);
        campNumarTelefon = new JTextField();
        campNumarTelefon.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(campNumarTelefon);

        JLabel textMoneda = new JLabel("Moneda ");
        textMoneda.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textMoneda);
        selectorMoneda = new JComboBox<Moneda>(Moneda.values());
        selectorMoneda.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(selectorMoneda);

        JLabel textFrecventaPlata = new JLabel("Frecventa plata");
        textFrecventaPlata.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textFrecventaPlata);
        selectorFrecventaPlata = new JComboBox<Frecventa>(Frecventa.values());
        selectorFrecventaPlata.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(selectorFrecventaPlata);

        JLabel textProgramInvestitii = new JLabel("Program investitii ");
        textProgramInvestitii.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textProgramInvestitii);
        selectorProgramInvestitii = new JComboBox<ProgramInvestitii>(ProgramInvestitii.values());
        selectorProgramInvestitii.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(selectorProgramInvestitii);

        JLabel textPrima = new JLabel("Prima");
        textPrima.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textPrima);
        campPrima = new JTextField();
        campPrima.setFont(new Font("Serif", Font.PLAIN, 40));
        campPrima.setEnabled(false);
        panouContinutFormular.add(campPrima);

        JLabel textDataScadenta = new JLabel("Data scadenta");
        textDataScadenta.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textDataScadenta);
        campDataScadenta = new JTextField();
        campDataScadenta.setFont(new Font("Serif", Font.PLAIN, 40));
        campDataScadenta.setEnabled(false);
        panouContinutFormular.add(campDataScadenta);

        JLabel textContAsociat = new JLabel("Cont asociat");
        textContAsociat.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textContAsociat);
        campContAsociat = new JTextField();
        campContAsociat.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(campContAsociat);

        JLabel textParola = new JLabel("Parola (doar cont nou)");
        textParola.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(textParola);
        campParola = new JTextField();
        campParola.setFont(new Font("Serif", Font.PLAIN, 40));
        panouContinutFormular.add(campParola);

        JLabel textAcoperire = new JLabel("Tip acoperire ");
        textAcoperire.setFont(new Font("Serif", Font.PLAIN, 40));
        panouAcoperire.add(textAcoperire);
        selectorAcoperire = new JComboBox<Acoperire>(Acoperire.values());
        selectorAcoperire.setFont(new Font("Serif", Font.PLAIN, 40));
        panouAcoperire.add(selectorAcoperire);

        JLabel textSumaAcoperita = new JLabel("Suma acoperita");
        textSumaAcoperita.setFont(new Font("Serif", Font.PLAIN, 40));
        panouAcoperire.add(textSumaAcoperita);
        campSumaAcoperita = new JTextField();
        campSumaAcoperita.setFont(new Font("Serif", Font.PLAIN, 40));
        campSumaAcoperita.setEnabled(false);
        panouAcoperire.add(campSumaAcoperita);

        JLabel textProcentCrestere = new JLabel("Procent crestere");
        textProcentCrestere.setFont(new Font("Serif", Font.PLAIN, 40));
        panouAcoperire.add(textProcentCrestere);
        campProcentCrestere = new JTextField();
        campProcentCrestere.setText("50.0");
        campProcentCrestere.setFont(new Font("Serif", Font.PLAIN, 40));
        campProcentCrestere.setEnabled(false);
        panouAcoperire.add(campProcentCrestere);

        JLabel textinterventiiChirurgicale = new JLabel("Interventii chirurgicale");
        textinterventiiChirurgicale.setFont(new Font("Serif", Font.PLAIN, 40));
        panouDeclaratieMedicala.add(textinterventiiChirurgicale);
        adaugaInterventie = new JButton("Adauga o interventie");
        adaugaInterventie.setFont(new Font("Serif", Font.PLAIN, 40));
        interventiiChirgicale = new ArrayList<JTextField>();
        adaugaInterventie.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                adaugareCampInterventieChirurgicala();

                revalidate();
                repaint();
            } 
        });
        panouDeclaratieMedicala.add(adaugaInterventie);

        JLabel textConsumAlcool = new JLabel("Consum alcool?");
        textConsumAlcool.setFont(new Font("Serif", Font.PLAIN, 40));
        panouDeclaratieMedicala.add(textConsumAlcool);
        consumAlcool = new JCheckBox();
        panouDeclaratieMedicala.add(consumAlcool);

        JLabel textProfesieRiscanta = new JLabel("Profesie riscanta?");
        textProfesieRiscanta.setFont(new Font("Serif", Font.PLAIN, 40));
        panouDeclaratieMedicala.add(textProfesieRiscanta);
        profesieRiscanta = new JCheckBox();
        panouDeclaratieMedicala.add(profesieRiscanta);

        JLabel textiBoli = new JLabel("Boli");
        textiBoli.setFont(new Font("Serif", Font.PLAIN, 40));
        panouDeclaratieMedicala.add(textiBoli);
        adaugaBoala = new JButton("Adauga o boala");
        adaugaBoala.setFont(new Font("Serif", Font.PLAIN, 40));
        boli = new ArrayList<JTextField>();
        adaugaBoala.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                adaugareCampBoala();

                revalidate();
                repaint();
            } 
        });
        panouDeclaratieMedicala.add(adaugaBoala);

        panouPersoana.setBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Persoana"));
        panouFormular.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Formular"), BorderFactory.createEmptyBorder(10, 100, 10, 100)));
        panouAcoperire.setBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Acoperire"));
        panouDeclaratieMedicala.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Declaratie medicala"), BorderFactory.createEmptyBorder(10, 100, 10, 100)));
        panouFormular.add(panouPersoana);
        panouFormular.add(panouAcoperire);
        panouFormular.add(panouContinutFormular);

        wrapper.add(panouFormular);
        wrapper.add(panouDeclaratieMedicala);

        JPanel panouButoane = new JPanel();

        butonAnulare = new JButton("Anuleaza");
        butonSalvare = new JButton("Salveaza");

        butonAnulare.setFont(new Font("Serif", Font.PLAIN, 50));
        butonSalvare.setFont(new Font("Serif", Font.PLAIN, 50));

        butonAnulare.setPreferredSize(new Dimension(500, 120));
        butonSalvare.setPreferredSize(new Dimension(500, 120));

        afisarePrima();

        butonAnulare.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                dispose();
                new MeniuAsigurator();
            }
        });

        selectorAcoperire.addItemListener(event -> {
            modificareFormular();
            campProcentCrestere.setText(String.valueOf(asigurareEliberata.getFormular().getAcoperire().getProcentCrestere()));
            campSumaAcoperita.setText(String.format("%.2f", asigurareEliberata.getFormular().getAcoperire().getSumaAsigurata()));

            afisarePrima();
        });

        selectorMoneda.addItemListener(event -> {
            modificareFormular();
            afisarePrima();
        });

        selectorProgramInvestitii.addItemListener(event -> {
            modificareFormular();
            afisarePrima();
        });

        selectorFrecventaPlata.addItemListener(event -> {
            modificareFormular();
            afisarePrima();
        });

        panouButoane.add(butonAnulare);
        panouButoane.add(Box.createHorizontalStrut(100));
        panouButoane.add(butonSalvare);

        eroare = new JLabel("Cel putin un camp e invalid");
        eroare.setForeground(Color.RED);
        eroare.setVisible(false);

        add(scrollare);
        add(eroare);
        add(panouButoane);
        
        if(numarAsigurareEditat <= 0){
            butonSalvare.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    if(campCnp.getText().length() == 13 && campNume.getText().length() != 0 && campPrenume.getText().length() != 0 && campCnp.getText().length() != 0 && campAdresa.getText().length() != 0 && campLocMunca.getText().length() != 0 && campDataNasterii.getText().length() != 0 && campNumarTelefon.getText().length() != 0
                        && !campNume.getText().contains(",") && !campPrenume.getText().contains(",") && !campCnp.getText().contains(",") && !campAdresa.getText().contains(",") && !campLocMunca.getText().contains(",") && !campDataNasterii.getText().contains(",") && !campContAsociat.getText().contains(" ") && !campParola.getText().contains(" ") && !campNumarTelefon.getText().contains(",")
                    ){
                        HashSet<String> s_boli = new HashSet<String>();
                        HashSet<String> s_interventii = new HashSet<String>();
                        for(JTextField curent : interventiiChirgicale){
                            s_interventii.add(curent.getText());
                        }
                        for(JTextField curent : boli){
                            s_boli.add(curent.getText());
                        }
                        
                        modificareFormular();

                        SalvareFisier.salveazaVoucher(voucherEliberat);
                        SalvareFisier.salveazaPolita(politaEliberata);
                        SalvareFisier.salveazaAsigurare(asigurareEliberata);
                        if(campContAsociat.getText().length() != 0){
                            if(campParola.getText().length() == 0) 
                                campParola.setText("parola");

                            SalvareFisier.adaugaAsigurareLaCont(campContAsociat.getText(), campParola.getText(), asigurareEliberata.getNumarPolitaAsociat());
 
                        }
                        dispose();
                        new MeniuAsigurator();
                    }
                    else{
                        eroare.setVisible(true);
                    }
                }
            });
        }
        else{
            butonSalvare.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    if(campCnp.getText().length() == 13 && campNume.getText().length() != 0 && campPrenume.getText().length() != 0 && campCnp.getText().length() != 0 && campAdresa.getText().length() != 0 && campLocMunca.getText().length() != 0 && campDataNasterii.getText().length() != 0 && campNumarTelefon.getText().length() != 0
                    && !campNume.getText().contains(",") && !campPrenume.getText().contains(",") && !campCnp.getText().contains(",") && !campAdresa.getText().contains(",") && !campLocMunca.getText().contains(",") && !campDataNasterii.getText().contains(",") && !campContAsociat.getText().contains(" ") && !campParola.getText().contains(" ") && !campNumarTelefon.getText().contains(",")){

                        modificareFormular();

                        SalvareFisier.salveazaPolita(politaEliberata, numarAsigurareEditat);
                        SalvareFisier.salveazaAsigurare(asigurareEliberata, numarAsigurareEditat);
                        SalvareFisier.salveazaVoucher(voucherEliberat, numarAsigurareEditat);

                        dispose();
                        new MeniuAsigurator();
                    }
                    else{
                        eroare.setVisible(true);
                    }
                }
            });
            
            campContAsociat.setEnabled(false);
            campParola.setEnabled(false);
            Asigurare citit = CitireFisier.citesteAsigurare(numarAsigurareEditat);
            campNume.setText(citit.getFormular().getPersoana().getNume());
            campPrenume.setText(citit.getFormular().getPersoana().getPrenume());
            campCnp.setText(citit.getFormular().getPersoana().getCnp());
            campAdresa.setText(citit.getFormular().getPersoana().getAdresa());
            campLocMunca.setText(citit.getFormular().getPersoana().getLocMunca());
            campDataNasterii.setText(citit.getFormular().getPersoana().getDataNasterii());
            selectorAcoperire.setSelectedItem(citit.getFormular().getAcoperire().getAcoperire());
            campNumarTelefon.setText(citit.getFormular().getNumarTelefon());
            selectorMoneda.setSelectedItem(citit.getFormular().getMoneda());
            selectorFrecventaPlata.setSelectedItem(citit.getFormular().getFrecventaPlata());
            selectorProgramInvestitii.setSelectedItem(citit.getFormular().getProgramInvestitii());
            consumAlcool.setSelected(citit.getDeclaratieMedicala().getConsumAlcool());
            profesieRiscanta.setSelected(citit.getDeclaratieMedicala().getProfesieRiscanta());

            for(String curent : citit.getDeclaratieMedicala().getBoli()){
                adaugareCampBoala(curent, true);
            }
            for(String curent : citit.getDeclaratieMedicala().getInterventiiChirurgicale()){
                adaugareCampInterventieChirurgicala(curent, true);
            }

            afisarePrima();
        }
    }
}
