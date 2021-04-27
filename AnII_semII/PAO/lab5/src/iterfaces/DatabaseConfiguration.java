package iterfaces;

public class DatabaseConfiguration extends Configuration implements ISerializable, IDatabaseConfigurationConstants{
    public DatabaseConfiguration(String path) {
        super(path);
    }

    @Override
    public void print() {
        System.out.println(String.format("%s[jdbc:%s://%s:%s/%s?user=%s&password=%s]",getClass().getSimpleName(), getType(), getHost(), getPort(), getUser(), getPassword()));
    }
    public String getType(){
        return (String) getProperty(TYPE);
    }
    public void setType(String value){
        setPropoerty(TYPE, value);
    }

    public String getHost(){
        return (String) getProperty(HOST);
    }
    public void setHost(String value){
        setPropoerty(HOST, value);
    }

    public String getName(){
        return (String) getProperty(NAME);
    }
    public void setName(String value){
        setPropoerty(NAME, value);
    }

    public String getPassword(){
        return (String) getProperty(PASSWORD);
    }
    public void setPassword(String value){
        setPropoerty(PASSWORD, value);
    }

    public String getUser(){
        return (String) getProperty(USER);
    }
    public void setUser(String value){
        setPropoerty(USER, value);
    }

    public String getPort(){
        return (String) getProperty(PORT);
    }
    public void setPort(String value){
        setPropoerty(PORT, value);
    }
}
