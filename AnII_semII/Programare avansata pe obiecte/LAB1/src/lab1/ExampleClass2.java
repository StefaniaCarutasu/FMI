package lab1;

import java.util.Locale;

public class ExampleClass2 {
    public static void main(String[] args) {
        int x = 20;
        Integer y = x;
        int z = y.intValue();
        Double a = 6.89;
        double b = a.doubleValue();
        int c = Integer.parseInt("56");
        System.out.println(Integer.toString(6825).length());
        System.out.println("tHiS iS A tEst".toLowerCase());
        System.out.println("Test".equals("test"));
        System.out.println("Test".equalsIgnoreCase("test"));
    }
    public static void increment(int i){
        i++;
    }
    public static void incrementWrapper (Integer i){
        i = Integer.valueOf(i++);
    }

}
