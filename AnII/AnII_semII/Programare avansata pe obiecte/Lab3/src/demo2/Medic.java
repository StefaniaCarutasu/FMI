package demo2;

public class Medic {
    protected String grad;
    protected String specializare;

    public Medic(String grad)
    {
        this.grad = grad;
        this.specializare = "Generalist";
    }

    protected void scrieReteta()
    {
        System.out.println("Reteta a fost scrisa de medic");
    }

    protected static void planificaConsultatie()
    {
        System.out.println("Consultatie la medic generalist");
    }

    protected String obtineInformatii()
    {
        return "Medic " + grad;
    }

}
