package other;

import java.net.HttpURLConnection;

public class Person implements IHuman{
    private String name;
    public Person(String name){
        this.name = name;
    }

    @Override
    public String getName(){
        return name + " alias " + IHuman.super.getName();
    }
}
