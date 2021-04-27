package controllers;

import controllers.OrdersController;
import controllers.UsersController;
import database.Database;
import drivers.Driver;
import orders.Order;
import users.User;

import java.util.ArrayList;
import java.util.List;

//create new driver
//delete a driver
//update a driver
//show order history for a driver
//mark an order as delivered

public class DriversController {

    public void createDriver(String username, String address, String email, String password, int age, String vehicleType, String vehicleNumber, Boolean availability)  {
        Driver driver = new Driver(username, address, email, password, age, vehicleType, vehicleNumber, availability);
        Database.addDriver(driver);
    }

    public void deleteDriver(String id){
        int i = 0;
        while(i < Database.getDrivers().size()){
            if(Database.getDrivers().get(i).getId().equals(id)){
                List<Driver> driversList = Database.getDrivers();
                driversList.remove(i);
                Database.setDrivers(driversList);
                break;
            }
            i++;
        }
    }

    public void updateDriver(String id, String fieldToUpdate, String updatedValue){
        int i = 0;
        while(i < Database.getDrivers().size()){
            if(Database.getDrivers().get(i).getId().equals(id)){
                switch (fieldToUpdate){
                    case "Email":
                        Database.getDrivers().get(i).setEmail(updatedValue);
                        break;
                    case "Username:":
                        Database.getDrivers().get(i).setUserName(updatedValue);
                        break;
                    case "Age":
                        Database.getDrivers().get(i).setAge(Integer.parseInt(updatedValue));
                        break;
                    case "Password":
                        Database.getDrivers().get(i).setPassword(updatedValue);
                        break;
                    case "Address":
                        Database.getDrivers().get(i).setAddress(updatedValue);
                        break;
                    case "VehicleType":
                        Database.getDrivers().get(i).setVehicleType(updatedValue);
                        break;
                    case "VehicleNumber":
                        Database.getDrivers().get(i).setVehicleNumber(updatedValue);
                        break;
                    case "Availability":
                        Database.getDrivers().get(i).setAvailability(Boolean.parseBoolean(updatedValue));
                        break;
                    default:
                        break;
                }
                break;
            }
            i++;
        }
    }

    public void showOrderHistory(String driverId){
        Driver driver = Database.getDriverById(driverId);
        List<Order> orderHistory = new ArrayList<Order>();
        int i = 0;
        while(i < Database.getOrders().get("resolved").size()){
            if(Database.getOrders().get("resolved").get(i).getUserId().equals(driverId)){
                orderHistory.add(Database.getOrders().get("resolved").get(i));
            }
            i++;
        }
        assert driver != null;
        System.out.println("Driver: " + driver.getUserName() + "\n");
        System.out.println("Orders:\n");
        for(Order order: orderHistory){
            System.out.println(order.toString() + "\n");
        }
    }

    public void markAsDeliveredByDriver(String orderId, String driverId){
        for(Order ord: Database.getOrders().get("active")){
            if(ord.getId().equals(orderId) && ord.getDriverId().equals(driverId)){
                OrdersController.markAsDelivered(orderId);
            }
        }
    }
}