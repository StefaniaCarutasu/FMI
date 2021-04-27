package demo2;

public class Program {
    public static void main(String[] args) {
        Medic medic = new Medic("primar");
        System.out.println(medic.specializare);
        medic.scrieReteta();
        //medic.planificaConsultatie();
        Medic.planificaConsultatie();
        System.out.println(medic.obtineInformatii());

        System.out.println("-----------");
        Medic medic1 = new Dermatolog("primar");
        medic1.scrieReteta();
        medic1.planificaConsultatie();
        System.out.println(medic1.obtineInformatii());
        System.out.println(medic1.specializare);

        System.out.println("-----------");
        Dermatolog medic2 = new Dermatolog("rezident");
        medic2.scrieReteta();
        medic2.planificaConsultatie();
        System.out.println(medic2.obtineInformatii());
        System.out.println(medic2.specializare);

        System.out.println("-----------");
        Medic medic3 = new Oftalmolog("specialist");
        medic3.scrieReteta();
        medic3.planificaConsultatie();
        System.out.println(medic3.obtineInformatii());
        System.out.println(medic3.specializare);

        System.out.println("-----------");
        Oftalmolog medic4 = new Oftalmolog("specialist");
        medic4.scrieReteta();
        medic4.planificaConsultatie();
        System.out.println(medic4.obtineInformatii());
        System.out.println(medic4.specializare);

        System.out.println("-----------");
        //Dermatolog medicDeramtolog = (Dermatolog) new Medic();
    }
}
