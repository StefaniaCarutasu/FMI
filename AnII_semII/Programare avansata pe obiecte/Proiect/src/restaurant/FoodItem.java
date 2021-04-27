package restaurant;

import java.util.Set;

public class FoodItem extends MenuItem {
    public boolean isSpicy;
    public boolean isVegetarian;

    public FoodItem(String menuId, String name, int price, Set<String> ingredients, Set<String> allergens, boolean isSpicy, boolean isVegetarian) {
        super(menuId, name, price, ingredients, allergens);
        this.isSpicy = isSpicy;
        this.isVegetarian = isVegetarian;
    }

    public boolean isSpicy() {
        return isSpicy;
    }

    public void setSpicy(boolean spicy) {
        isSpicy = spicy;
    }

    public boolean isVegetarian() {
        return isVegetarian;
    }

    public void setVegetarian(boolean vegetarian) {
        isVegetarian = vegetarian;
    }
}
