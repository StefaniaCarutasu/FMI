package database;

import orders.Order;
import drivers.Driver;
import users.User;
import restaurant.Restaurant;

import java.util.List;
import java.util.Map;

public class Database {
    static Map<String, List<Order>> Orders;
    static List<User> Users;
    static List<Driver> Drivers;
    static List<Restaurant> Restaurants;


    public static Map<String, List<Order>> getOrders() {
        return Orders;
    }

    public static void setOrders(Map<String, List<Order>> orders) {
        Orders = orders;
    }

    public static List<User> getUsers() {
        return Users;
    }

    public static void setUsers(List<User> users) {
        Users = users;
    }

    public static List<Driver> getDrivers() {
        return Drivers;
    }

    public static void setDrivers(List<Driver> drivers) {
        Drivers = drivers;
    }

    public static List<Restaurant> getRestaurants() {
        return Restaurants;
    }

    public static void setRestaurants(List<Restaurant> restaurants) {
        Restaurants = restaurants;
    }

    public static void addUser(User usr) { Users.add(usr); }
    public static User getUserById(String id){
        for (User user : Users) {
            if (user.getId().equals(id)) {
                return user;
            }
        }
        return null;
    }

    public static void addDriver(Driver driver) { Drivers.add(driver); }
    public static Driver getDriverById(String id){
        for (Driver driver: Drivers) {
            if (driver.getId().equals(id)) {
                return driver;
            }
        }
        return null;
    }

    public static void addRestaurant(Restaurant res) { Restaurants.add(res); }
    public static Restaurant getRestaurantById(String id){
        for(Restaurant res: Restaurants){
            if(res.getId().equals(id)){
                return res;
            }
        }
        return null;
    }

    public static void addOrder(Order order) { Orders.get("active").add(order); }

}
