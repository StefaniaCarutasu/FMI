package users;

public class User {
    private static int idGenerator = 0;
    protected final String Id;
    protected String UserName;
    protected String Address;
    protected int Age;
    private String password;
    private String email;

    public User(){
        Id = Integer.toString(idGenerator);
        idGenerator ++;
    }

    public User(String userName, String address, int age, String password, String email) {
        Id = Integer.toString(idGenerator);
        idGenerator++;
        UserName = userName;
        Address = address;
        Age = age;
        this.password = password;
        this.email = email;
    }

    public String getId() {
        return Id;
    }

    public String getUserName() {
        return UserName;
    }

    public void setUserName(String userName) {
        UserName = userName;
    }

    public String getAddress() {
        return Address;
    }

    public void setAddress(String address) {
        Address = address;
    }

    public int getAge() {
        return Age;
    }

    public void setAge(int age) {
        Age = age;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
