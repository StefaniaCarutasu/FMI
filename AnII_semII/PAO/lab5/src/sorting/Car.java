package sorting;

public class Car implements Comparable{
    private int age;
    private String brand;
    private String type;

    public Car(int age, String brand, String type) {
        this.age = age;
        this.brand = brand;
        this.type = type;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public int compareTo(Object o) {
        Car car = (Car) o;
        return this.brand.compareTo((car.getBrand()));
    }

    @Override
    public String toString() {
        return "Car{" +
                "age=" + age +
                ", brand='" + brand + '\'' +
                ", type='" + type + '\'' +
                '}';
    }
}
