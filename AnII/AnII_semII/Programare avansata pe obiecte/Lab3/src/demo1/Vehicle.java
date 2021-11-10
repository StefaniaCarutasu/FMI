package demo1;

public class Vehicle {
    protected String model;
    protected int wheelsNumber;

    public Vehicle()
    {
        System.out.println("Vehicle no params");
    }

    public Vehicle(String model, int wheelsNumber)
    {
        this.model = model;
        this.wheelsNumber = wheelsNumber;
        System.out.println("Vehicle constructor with params");

    }
    protected void start()
    {
        System.out.println("Vechicle started");
    }
    protected void stop()
    {
        System.out.println("Vehicle stopped");
    }

    private void checkVehicle()
    {
        System.out.println("This is a private method");
    }

    protected final void info()
    {
        System.out.println("Have a nice trip!");
    }


}
