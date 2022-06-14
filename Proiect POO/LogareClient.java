//Copyright Dragos 2021

public class LogareClient extends Logare {
    @Override
    protected boolean autorizare() {
        return !contAutentificat.getEsteAgent();
    }
    @Override
    protected void accesCont() {
        dispose();
        new MeniuClient(((ContClient)contAutentificat).getPoliteAsociate());
    }

    LogareClient(){
        super("Logare client");
    }
}
