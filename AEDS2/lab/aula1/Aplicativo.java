public class Aplicativo {
    public static void main(String[] args) {
        String nome = "Rafael";
        System.out.println(nome);
        nome = "Rr"; // New space, garbage collected.
        System.out.println(nome);

        Plant p = new Plant("tyest", 100);
        p.setIsAlive(true);
        System.out.println(p.isAlive());

        Cacto c = new Cacto();
        System.out.println(c.getType());
    }
}
