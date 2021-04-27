package demo1;

public class Bike extends Vehicle{
    private String type;
    public Bike()
    {
        System.out.println("Bike constr no params");
    }

    public Bike(String model, int wheelsNo, String type)
    {
        super(model, wheelsNo);
        this.type = type;
    }

    public Bike(String model, String type)
    {
        super(model, 2);
        this.type = type;
    }

    public String getType() {
        return type;
    }

    @Override
    protected void stop()
    {
        System.out.println("Bike stopped");
        super.start();
    }

    @Override
    protected void start()
    {
        System.out.println("Bike started");
    }
}
