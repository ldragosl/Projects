//Copyright Denis 2022

import javax.swing.JFrame;
import java.awt.GridLayout;
import java.util.HashSet;
import javax.swing.BorderFactory;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VizualizarePolita extends JFrame {
    private JButton butonInapoi;

    VizualizarePolita(HashSet<Integer> politeDeCitit){
        super("Meniu Polite");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);

        
        butonInapoi = new JButton("Mergi inapoi");

       
        butonInapoi.setFont(new Font("Serif", Font.PLAIN, 50));

        
        butonInapoi.setPreferredSize(new Dimension(500, 120));

        JPanel panouWrapper = new JPanel();
        JScrollPane scroll = new JScrollPane(panouWrapper);
        panouWrapper.setLayout(new BoxLayout(panouWrapper, BoxLayout.PAGE_AXIS));
        scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        JPanel panouButoane = new JPanel();
        HashSet<PolitaAsigurare> politeCitite = CitireFisier.citestePolite();
        
        for(int curent:politeDeCitit){
            for(PolitaAsigurare politaCurenta : politeCitite){
                if(curent == politaCurenta.getNumar()){
                    JPanel panouVouchere = new JPanel();
                    JPanel panouCombinat = new JPanel();

                    
    
                    panouCombinat.setLayout(new BoxLayout(panouCombinat, BoxLayout.LINE_AXIS));
                    panouCombinat.add(panouVouchere);
                    panouCombinat.add(Box.createHorizontalStrut(100));
                    panouCombinat.setPreferredSize(new Dimension(getWidth(), getHeight() / 3));
                    panouCombinat.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Polita nr.  " + curent ), BorderFactory.createEmptyBorder(10, 100, 10, 100)));
                    panouWrapper.add(panouCombinat);
                    panouVouchere.setLayout(new GridLayout(0, 2));

                    JLabel textNrPolita = new JLabel ("Nr. polita");
                    textNrPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textNrPolita);
                    JTextField campNrPolita = new JTextField() ;
                    panouVouchere.add(campNrPolita);
                    campNrPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    campNrPolita.setText(String.valueOf(politaCurenta.getNumar()));
                    campNrPolita.setEnabled(false);

                    JLabel textNumePolita = new JLabel ("Nume");
                    textNumePolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textNumePolita);
                    JTextField campNume = new JTextField() ;
                    panouVouchere.add(campNume);
                    campNume.setText(politaCurenta.getNume());
                    campNume.setFont(new Font("Serif", Font.PLAIN, 40));
                    campNume.setEnabled(false);

                    JLabel textPrenumePolita = new JLabel ("Prenume");
                    textPrenumePolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textPrenumePolita);
                    JTextField campPrenume = new JTextField() ;
                    panouVouchere.add(campPrenume);
                    campPrenume.setText(politaCurenta.getPrenume());
                    campPrenume.setFont(new Font("Serif", Font.PLAIN, 40));
                    campPrenume.setEnabled(false);

                    JLabel textDataNasteriiPolita = new JLabel ("Data nasterii");
                    textDataNasteriiPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textDataNasteriiPolita);
                    JTextField campDataNasterii = new JTextField() ;
                    panouVouchere.add(campDataNasterii);
                    campDataNasterii.setText(politaCurenta.getDataNasterii());
                    campDataNasterii.setFont(new Font("Serif", Font.PLAIN, 40));
                    campDataNasterii.setEnabled(false);

                    JLabel textAdresaPolita = new JLabel ("Adresa");
                    textAdresaPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textAdresaPolita);
                    JTextField campAdresa = new JTextField() ;
                    panouVouchere.add(campAdresa);
                    campAdresa.setText(politaCurenta.getAdresa());
                    campAdresa.setFont(new Font("Serif", Font.PLAIN, 40));
                    campAdresa.setEnabled(false);

                    JLabel textPlanAsigurariPolita = new JLabel ("Plan Asigurari");
                    textPlanAsigurariPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textPlanAsigurariPolita);
                    JTextField campPlanAsigurari = new JTextField() ;
                    panouVouchere.add(campPlanAsigurari);
                    campPlanAsigurari.setText(String.valueOf(politaCurenta.getPlanAsigurari()));
                    campPlanAsigurari.setFont(new Font("Serif", Font.PLAIN, 40));
                    campPlanAsigurari.setEnabled(false);
                    
                    JLabel textPrimaPolita = new JLabel ("Prima");
                    textPrimaPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textPrimaPolita);
                    JTextField campPrima = new JTextField() ;
                    panouVouchere.add(campPrima);
                    campPrima.setText(String.format("%.2f", politaCurenta.getPrima()));
                    campPrima.setFont(new Font("Serif", Font.PLAIN, 40));
                    campPrima.setEnabled(false);

                    JLabel textPogramInvestitiiPolita = new JLabel ("Pogram Investitii");
                    textPogramInvestitiiPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textPogramInvestitiiPolita);
                    JTextField campPogramInvestitii = new JTextField() ;
                    panouVouchere.add(campPogramInvestitii);
                    campPogramInvestitii.setText(String.valueOf(politaCurenta.getProgramInvestitii()));
                    campPogramInvestitii.setFont(new Font("Serif", Font.PLAIN, 40));
                    campPogramInvestitii.setEnabled(false);

                    JLabel textNrTelefonPolita = new JLabel ("Nr. Telefon");
                    textNrTelefonPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textNrTelefonPolita);
                    JTextField campNrTelefon = new JTextField() ;
                    panouVouchere.add(campNrTelefon);
                    campNrTelefon.setText(politaCurenta.getNrTelefon());
                    campNrTelefon.setFont(new Font("Serif", Font.PLAIN, 40));
                    campNrTelefon.setEnabled(false);
                
                }
            }
        }
        
        panouButoane.add(Box.createHorizontalStrut(100));
        panouButoane.add(butonInapoi);
        butonInapoi.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                new MeniuClient(politeDeCitit); 
                dispose();
            } 
        });
        getContentPane().add(BorderLayout.SOUTH, panouButoane);
        getContentPane().add(BorderLayout.CENTER, scroll);

    }
}
