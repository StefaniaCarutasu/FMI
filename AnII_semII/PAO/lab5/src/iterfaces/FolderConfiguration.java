package iterfaces;

public class FolderConfiguration extends Configuration implements ISerializable, IFolderConfigurationConstants{

    public FolderConfiguration(String path) {
        super(path);
    }

    @Override
    public void print() {
        System.out.println(String.format("%s[%s/%s]", getClass().getSimpleName(), getRoot(),getFilter()));
    }

    public String getRoot(){
        return (String) getProperty(ROOT);
    }
    public void setRoot(String value) {
        setPropoerty(ROOT, value);
    }

    public String getFilter(){
        return (String) getProperty(FILTER);
    }
    public void setFilter(String value) {
        setPropoerty(FILTER, value);
    }
}
