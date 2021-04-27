package restaurant;

import java.util.Arrays;
import java.util.List;
import java.util.Set;

public class MenuItem {
    private static int idGenerator = 0;
    private String Id;
    protected String menuId;
    protected String name;
    protected int price;
    protected Set<String> ingredients;
    protected Set<String> allergens;

    public MenuItem(String menuId, String name, int price, Set<String> ingredients, Set<String> allergens) {
        this.menuId = menuId;
        Id = menuId + idGenerator;
        idGenerator++;
        this.name = name;
        this.price = price;
        this.ingredients = ingredients;
        this.allergens = allergens;
    }

    public String getId() {
        return Id;
    }

    public void setId(String id) {
        Id = id;
    }

    public String getMenuId() {
        return menuId;
    }

    public void setMenuId(String menuId) {
        this.menuId = menuId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public Set<String> getIngredients() {
        return ingredients;
    }

    public void setIngredients(Set<String> ingredients) {
        this.ingredients = ingredients;
    }

    public Set<String> getAllergens() {
        return allergens;
    }

    public void setAllergens(Set<String> allergens) {
        this.allergens = allergens;
    }

    @Override
    public String toString() {
        return "MenuItem{" +
                ", name='" + name + '\'' +
                ", price=" + price +
                ", ingredients=" + ingredients +
                ", allergens=" + allergens +
                '}' + '\n';
    }
}
