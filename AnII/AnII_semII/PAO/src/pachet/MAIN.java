package pachet;

public class MAIN {
    public static void main(String[] args) {
        A obA = new A(1);
        B obB = new B(obA);
        C obC = new C(obB);

        obC.obiect.getA().set(2);
        
    }

}
