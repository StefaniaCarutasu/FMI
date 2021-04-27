package orders;

import restaurant.MenuItem;

import java.util.List;

public class Order {
    private static int idGenerator = 0;
    protected final String Id;
    protected String Status;
    protected String UserId;
    protected String RestaurantId;
    protected String DriverId;
    protected String PaymentMethod;
    public List<MenuItem> orderedItems;

    public Order() {
        Id = Integer.toString(idGenerator);
        idGenerator++;
    }

    public Order(String userId, String restaurantId, String paymentMethod, String driverId) {
        Id = Integer.toString(idGenerator);
        idGenerator++;
        UserId = userId;
        RestaurantId = restaurantId;
        PaymentMethod = paymentMethod;
        DriverId = driverId;
    }

    public String getId() {
        return Id;
    }


    public String getUserId() {
        return UserId;
    }

    public void setUserId(String userId) {
        UserId = userId;
    }

    public String getRestaurantId() {
        return RestaurantId;
    }

    public void setRestaurantId(String restaurantId) {
        RestaurantId = restaurantId;
    }

    public List<MenuItem> getOrderedItems() {
        return orderedItems;
    }

    public void setOrderedItems(List<MenuItem> orderedItems) {
        this.orderedItems = orderedItems;
    }

    public String getDriverId() {
        return DriverId;
    }

    public void setDriverId(String driverId) {
        DriverId = driverId;
    }

    public String getPaymentMethod() {
        return PaymentMethod;
    }

    public void setPaymentMethod(String paymentMethod) {
        PaymentMethod = paymentMethod;
    }

    public String getStatus() { return Status; }

    public void setStatus(String status) { Status = status; }

    @Override
    public String toString() {
        return "Order{" +
                "orderedItems=" + orderedItems +
                '}';
    }


}
