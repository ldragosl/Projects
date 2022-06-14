//Copyright Dragos 2021

public class LogareAsigurator extends Logare {
    @Override
    protected boolean autorizare() {
        return contAutentificat.getEsteAgent();
    }
    @Override
    protected void accesCont() {
        new MeniuAsigurator();
        dispose();
    }
    LogareAsigurator(){
        super("Logare asigurator");
    }
}
