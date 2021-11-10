package pachet;

public class C{
    B obiect;
    public C(B init) {
        obiect = new B(init);
    }
    public B getB() {
        return new B(obiect);
    }
}