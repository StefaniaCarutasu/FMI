package pachet;

public class B{
    A obiect;
    public B(A init) {
        obiect = new A(init);
    }
    public B(B other) {obiect = other.obiect;}
    public A getA() {
        return obiect;
    }
}