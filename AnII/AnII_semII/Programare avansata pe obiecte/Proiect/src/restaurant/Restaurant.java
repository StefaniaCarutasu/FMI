package restaurant;

public class Restaurant {
    private static int idGenerator = 0;
    protected final String Id;
    protected String Name;
    protected String OwnerName;
    protected String PhoneNumber;
    protected String Email;
    private int noOfEmployees;
    Menu menu;

    public Restaurant(){
        Id = Integer.toString(idGenerator);
        idGenerator++;
    }

    public Restaurant(String name, String ownerName) {
        Id = Integer.toString(idGenerator);
        idGenerator++;
        Name = name;
        OwnerName = ownerName;
    }

    public String getId() {
        return Id;
    }

    public String getName() {
        return Name;
    }

    public void setName(String name) {
        Name = name;
    }

    public String getOwnerName() {
        return OwnerName;
    }

    public void setOwnerName(String ownerName) {
        OwnerName = ownerName;
    }

    public int getNoOfEmployees() {
        return noOfEmployees;
    }

    public void setNoOfEmployees(int noOfEmployees) {
        this.noOfEmployees = noOfEmployees;
    }

    public Menu getMenu() {
        return menu;
    }

    public void setMenu(Menu menu) {
        this.menu = menu;
    }

    public String getPhoneNumber() {
        return PhoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        PhoneNumber = phoneNumber;
    }

    public String getEmail() {
        return Email;
    }

    public void setEmail(String email) {
        Email = email;
    }
}
