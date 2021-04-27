package restaurant;

import java.util.List;
import java.util.Map;

public class Menu {
    protected String restaurantId;
    private static int idGenerator = 0;
    protected final String Id;
    Map<String, List<MenuItem>> menuList;

    public Menu(String resId){
        restaurantId = resId;
        Id = restaurantId + idGenerator;
        idGenerator++;
        menuList.put("Food", null);
        menuList.put("Drinks", null);
    }

    public Menu(List<MenuItem> menuFood, List<MenuItem> menuDrink) {
        Id = restaurantId + idGenerator;
        idGenerator++;
        menuList.get("Food").addAll(menuFood);
        menuList.get("Drinks").addAll(menuDrink);
    }

    public String getRestaurantId() {
        return restaurantId;
    }

    public String getId() {
        return Id;
    }

    public Map<String, List<MenuItem>> getMenuList() {
        return menuList;
    }

    public void setMenuList(Map<String, List<MenuItem>> menu) {
        this.menuList = menu;
    }

    @Override
    public String toString() {
        return "Menu{" +
                "menu=" + menuList +
                '}';
    }

    public Integer findItemById(String id){
        for (int i = 0; i < menuList.get("Food").size(); i++){
            if(menuList.get("Food").get(i).getId().equals(id)){
                return i;
            }
        }
        for (int i = 0; i < menuList.get("Drinks").size(); i++){
            if(menuList.get("Drinks").get(i).getId().equals(id)){
                return i;
            }
        }
        return null;
    }
    public void addItem(MenuItem item){
        String type = item.getClass().getName();
        switch (type) {
            case "FoodItem" -> menuList.get("Food").add(item);
            case "DrinkItem" -> menuList.get("Drinks").add(item);
        }
    }

    public void removeItem(MenuItem item){
        int pozition = findItemById(item.getId());
        String type = item.getClass().getName();
        switch (type) {
            case "FoodItem" -> menuList.get("Food").remove(pozition);
            case "DrinkItem" -> menuList.get("Drinks").remove(pozition);
        }
    }
}
