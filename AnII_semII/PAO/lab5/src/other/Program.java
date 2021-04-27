package other;

public class Program {
    public static void main(String[] args) {
        Person person = new Person("Stefania Carutasu");
        System.out.println(person.getName());
        System.out.println(IHuman.isAdult(25));
        System.out.println(IHuman.isAdult(16));
    }
}
