package demo1;

public class Car extends Vehicle {
    String fuel;

    public Car()
    {
        super(null,0);
        System.out.println("Car constructor no params");
    }
    public Car(String model, int wheelsNumber, String fuel)
    {
        super(model,wheelsNumber);
        this.fuel=fuel;
        System.out.println("Car constructor with 3 params");
    }

    public Car(String model, String fuel)
    {
        super(model,4);
        this.fuel=fuel;
        System.out.println("Car constructor with 2 params");
    }

    @Override
    protected void stop()
    {
        System.out.println("Car stopped");
        super.start();
    }

    @Override
    protected void start()
    {
        System.out.println("Car started");
    }
}
