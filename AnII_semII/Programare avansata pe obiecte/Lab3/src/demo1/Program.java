package demo1;

public class Program {
    public static void main(String[] args) {
        Car car1 = new Car("Opel", 5, "gasoline");
        System.out.println("Model: " + car1.model + ", wheels: " + car1.wheelsNumber + ", fuel: " + car1.fuel);
        Car car2 = new Car("Toyota", "diesel");
        System.out.println("Model: " + car2.model + ", wheels: " + car2.wheelsNumber + ", fuel: " + car2.fuel);
        Car car3 = new Car();
        System.out.println("Model: " + car3.model + ", wheels: " + car3.wheelsNumber + ", fuel: " + car3.fuel);

        car1.start();
        car1.stop();
        //car1.checkVechicle();
        car1.info();
        System.out.println(car1 instanceof Vehicle);

        Bike bike1 = new Bike();
        System.out.println("Model: " + bike1.model + ", wheels: " + bike1.wheelsNumber + ", type: " + bike1.getType());
        Bike bike2 = new Bike("DHS", "city");
        System.out.println("Model: " + bike2.model + ", wheels: " + bike2.wheelsNumber + ", type: " + bike2.getType());
    }
}
