//Copyright Denis 2022

import javax.swing.JFrame;
import java.awt.GridLayout;
import java.util.Calendar;
import java.util.HashSet;
import javax.swing.BorderFactory;
import java.util.Date;
import java.text.SimpleDateFormat;
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

public class VizualizareVoucher extends JFrame {
    
    private JButton butonInapoi;

    private HashSet<Integer> politeCitite;

    public HashSet<Integer> getPoliteCitite() {
        return politeCitite;
    }

    VizualizareVoucher(HashSet<Integer> politeCitite){
        super("Meniu Voucher");

        this.politeCitite = politeCitite;

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
        HashSet<Voucher> vouchereCitite = CitireFisier.citesteVouchere();
        for(int curent:politeCitite){
            for(Voucher voucherCurent : vouchereCitite){
                if(curent == voucherCurent.getNrPolita()){
                    JPanel panouVouchere = new JPanel();
                    JPanel panouCombinat = new JPanel();
                    JButton plateste = new JButton("Plateste");
                    
    
                    panouCombinat.setLayout(new BoxLayout(panouCombinat, BoxLayout.LINE_AXIS));
                    panouCombinat.add(panouVouchere);
                    panouCombinat.add(Box.createHorizontalStrut(100));
                    panouCombinat.add(plateste);
                    panouCombinat.setPreferredSize(new Dimension(getWidth(), getHeight() / 3));
                    panouCombinat.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(BorderFactory.createRaisedBevelBorder(), "Voucher-ul nr.  " + curent ), BorderFactory.createEmptyBorder(10, 100, 10, 100)));
                    panouWrapper.add(panouCombinat);
                    panouVouchere.setLayout(new GridLayout(0, 2));
                    JLabel textNrPolita = new JLabel ("Nr. polita");
                    textNrPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textNrPolita);
                    

                    JTextField campNrPolita = new JTextField() ;
                    panouVouchere.add(campNrPolita);
                    campNrPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    campNrPolita.setText(String.valueOf(voucherCurent.getNrPolita()));
                    campNrPolita.setEnabled(false);

                    JLabel textNumePolita = new JLabel ("Nume");
                    textNumePolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textNumePolita);
                    JTextField campNume = new JTextField() ;
                    panouVouchere.add(campNume);
                    campNume.setText(voucherCurent.getNume());
                    campNume.setFont(new Font("Serif", Font.PLAIN, 40));
                    campNume.setEnabled(false);

                    JLabel textcnpPolita = new JLabel ("CNP");
                    textcnpPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textcnpPolita);
                    JTextField campCnp = new JTextField() ;
                    panouVouchere.add(campCnp);
                    campCnp.setText(voucherCurent.getCnp());
                    campCnp.setFont(new Font("Serif", Font.PLAIN, 40));
                    campCnp.setEnabled(false);

                    JLabel textSumaPolita = new JLabel ("Suma");
                    textSumaPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textSumaPolita);
                    JTextField campSuma = new JTextField() ;
                    panouVouchere.add(campSuma);
                    campSuma.setText(String.format("%.2f", voucherCurent.getSuma()));//setText(String.valueOf(voucherCurent.getSuma()));
                    campSuma.setFont(new Font("Serif", Font.PLAIN, 40));
                    campSuma.setEnabled(false);

                    JLabel textDataScadentaPolita = new JLabel ("Data scadenta");
                    textDataScadentaPolita.setFont(new Font("Serif", Font.PLAIN, 40));
                    panouVouchere.add(textDataScadentaPolita);
                    JTextField campDataScadenta = new JTextField() ;
                    panouVouchere.add(campDataScadenta);
                    Calendar c = Calendar.getInstance();
                    c.setTime(new Date(voucherCurent.getDataScadenta()));
                    campDataScadenta.setText(new SimpleDateFormat("MMM").format(c.getTime()) + " " + String.valueOf(c.get(Calendar.DAY_OF_MONTH)) + " " + String.valueOf(c.get(Calendar.YEAR)));
                    campDataScadenta.setFont(new Font("Serif", Font.PLAIN, 40));
                    campDataScadenta.setEnabled(false);

                    plateste.addActionListener(new AscultatorPlati(voucherCurent.getNrPolita(), this));
                    
                }
            }
        }
        
        panouButoane.add(Box.createHorizontalStrut(100));
        panouButoane.add(butonInapoi);
        butonInapoi.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                new MeniuClient(politeCitite); 
                dispose();
            } 
        });
        getContentPane().add(BorderLayout.SOUTH, panouButoane);
        getContentPane().add(BorderLayout.CENTER, scroll);

    }
}
