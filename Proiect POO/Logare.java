//Copyright Dragos 2021

import javax.swing.JTextField;
import javax.swing.JFrame;

import java.awt.Color;
import java.awt.Font;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JPasswordField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashSet;

abstract class Logare extends JFrame{
    private JTextField campNume;
    private JPasswordField campParola;

    private JButton butonConectare;

    protected Cont contAutentificat;
    
    private boolean autentificare(){
        HashSet<Cont> conturiCitite = CitireFisier.citesteConturi();
        for(Cont curent : conturiCitite){
            if(curent.getNume().matches(campNume.getText())){
                if(curent.getParola().matches(String.valueOf(campParola.getPassword()))){
                    contAutentificat = curent;
                    return true;
                }
                else return false;

            }
        }
        return false;
    } 
    protected abstract boolean autorizare();

    protected abstract void accesCont();

    Logare(String numeFereastra){
        super(numeFereastra);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setLayout(null);
        setVisible(true);

        JLabel textScrieNume;
        JLabel textScrieParola;
    
        JLabel eroareAutentificare;

        campNume = new JTextField(20);
        campParola = new JPasswordField(20);
        butonConectare = new JButton("Logare");

        textScrieNume = new JLabel("Nume utilizator: ");
        textScrieParola = new JLabel("Parola: ");
        eroareAutentificare = new JLabel("Eroare la autentificare");
        eroareAutentificare.setForeground(Color.RED);
        eroareAutentificare.setVisible(false);

        campNume.setFont(new Font("DialogInput", Font.PLAIN, 50));
        campParola.setFont(new Font("Serif", Font.PLAIN, 50));
        butonConectare.setFont(new Font("Serif", Font.PLAIN, 50));

        textScrieNume.setFont(new Font("Serif", Font.PLAIN, 30));
        textScrieParola.setFont(new Font("Serif", Font.PLAIN, 30));
        eroareAutentificare.setFont(new Font("Serif", Font.PLAIN, 30));

        textScrieNume.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 300, 300, 80);
        textScrieParola.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 170, 300, 80);

        campNume.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 230, 300, 80);
        campParola.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 100, 300, 80);
        butonConectare.setBounds(getWidth() / 2 - 150, getHeight() / 2 + 50, 300, 80);

        eroareAutentificare.setBounds(getWidth() / 2 - 150, getHeight() / 2 - 20, 300, 80);

        add(campNume);
        add(campParola);
        add(butonConectare);

        add(textScrieNume);
        add(textScrieParola);

        add(eroareAutentificare);

        butonConectare.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) { 
                if(autentificare() && autorizare())
                    accesCont();
                else eroareAutentificare.setVisible(true);
            } 
        });

        repaint();//fara aceasta catoedata nu apar butoanele
    }

    @Override
    public void repaint() {
        super.repaint();
    }
}