package restaurant;

import java.util.Set;

public class DrinkItem extends MenuItem {
    public boolean isAlcoholic;

    public DrinkItem(String id, String menuId, String name, int price, Set<String> ingredients, Set<String> allergens, boolean isAlcoholic) {
        super(id, menuId, name, price, ingredients, allergens);
        this.isAlcoholic = isAlcoholic;
    }

    public boolean isAlcoholic() {
        return isAlcoholic;
    }

    public void setAlcoholic(boolean alcoholic) {
        isAlcoholic = alcoholic;
    }
}
