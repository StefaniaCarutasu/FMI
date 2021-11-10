package demo2;

public class Oftalmolog extends Medic{
    protected String specializare;
    public Oftalmolog(String grad) {
        super(grad);
        specializare = "Oftalmologie";
    }

    @Override
    protected void scrieReteta()
    {
        System.out.println("Reteta a fost scrisa de oftalmolog");
    }

    protected static void planificaConsultatie()
    {
        System.out.println("Consultatie la medic oftalmolog");
    }

    @Override
    protected String obtineInformatii()
    {
        return super.obtineInformatii() + " " + this.specializare;
    }
}
