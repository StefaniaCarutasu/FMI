package drivers;

import users.User;

public class Driver extends User {
    protected String VehicleType;
    protected String VehicleNumber;
    protected Boolean Availability;

    public Driver(){super();}

    public Driver(String username, String address, String email, String password, int age, String vehicleType, String vehicleNumber, Boolean availability)  {
        super(username, address, age, password, email);
        this.VehicleType = vehicleType;
        this.VehicleNumber = vehicleNumber;
        this.Availability = availability;
    }
    public String getVehicleType() {
        return VehicleType;
    }

    public void setVehicleType(String vehicleType) {
        VehicleType = vehicleType;
    }

    public String getVehicleNumber() {
        return VehicleNumber;
    }

    public void setVehicleNumber(String vehicleNumber) {
        VehicleNumber = vehicleNumber;
    }

    public Boolean getAvailability() {
        return Availability;
    }

    public void setAvailability(Boolean availability) {
        Availability = availability;
    }
}
