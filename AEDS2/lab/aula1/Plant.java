public class Plant {
    // attrs
    private boolean alive;
    private double height;
    private String type;
    private Leaf leaf;

    // methods
    public Plant() {
        this.alive = true;
        this.height = 0;
        this.type = "";
    }
    public Plant(String type, double height) { // overload
        this.alive = true;
        this.height = height;
        this.type = type;
    }

    public boolean isAlive() {
        return this.alive;
    }
    public double getHeight() {
        return this.height;
    }
    public String getType() {
        return this.type;
    }
    public void setIsAlive(boolean alive) {
        this.alive = alive;
    }
    public void setHeight(double height) {
        this.height = height > 0 ? height : 0;
    }
    public void setType(String type) {
        this.type = type;
    }
}
