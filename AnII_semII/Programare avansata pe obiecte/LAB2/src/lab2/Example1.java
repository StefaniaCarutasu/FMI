package lab2;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;

public class Example1 {
    public static void main(String[] args)
    {
        String[] cities = {"Bucuresti", "Timisoara", "Pitesti", "Constanta"};
        System.out.println(cities.length);
        Arrays.sort(cities);
        System.out.println(Arrays.toString(cities));
        Arrays.sort(cities, new Comparator<String>() {
            public int compare(String o1, String o2) {
                return o1.charAt(1) < o2.charAt(1) ? -1 : 1;
            }
        });
        System.out.println(Arrays.toString(cities));
    }

}
