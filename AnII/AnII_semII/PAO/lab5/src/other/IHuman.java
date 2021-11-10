package other;

public interface IHuman {
    String DEFAULT_NAME = "Jane Doe";
    default String getName(){
        test();
        return DEFAULT_NAME;
    }
    private void test(){
        System.out.println("Private method was called");
    }
    static boolean isAdult(int age){
        return age >= 18;
    }
}
