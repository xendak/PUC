import java.util.*;
import java.util.regex.*;

public class BooleanExpressionEvaluator {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) continue;

            String[] parts = line.split(" ");
            int n = Integer.parseInt(parts[0]);
            boolean[] values = new boolean[n];
            for (int i = 0; i < n; i++) {
                values[i] = Integer.parseInt(parts[i + 1]) == 1;
            }
            String expression = parts[n + 1];

            boolean result = evaluateExpression(expression, values);
            System.out.println(result ? "1" : "0");
        }
        scanner.close();
    }

    private static boolean evaluateExpression(String expression, boolean[] values) {
        // Replace variables with their values
        for (int i = 0; i < values.length; i++) {
            char var = (char) ('A' + i);
            expression = expression.replace(String.valueOf(var), values[i] ? "1" : "0");
        }
        return evaluate(expression);
    }

    private static boolean evaluate(String expression) {
        expression = expression.replaceAll("\\s", ""); // Remove whitespace
        List<String> tokens = tokenize(expression);
        Stack<Boolean> stack = new Stack<>();
        Stack<String> operators = new Stack<>();

        for (String token : tokens) {
            if (token.matches("[01]")) {
                stack.push(token.equals("1"));
            } else if (token.equals("(")) {
                operators.push(token);
            } else if (token.equals(")")) {
                while (!operators.isEmpty() && !operators.peek().equals("(")) {
                    applyOperator(operators.pop(), stack);
                }
                operators.pop(); // Remove the '('
            } else if (token.equals(",")) {
                // Ignore commas
            } else if (isOperator(token)) {
                operators.push(token);
            } else {
                throw new IllegalArgumentException("Unknown token: " + token);
            }
        }

        while (!operators.isEmpty()) {
            applyOperator(operators.pop(), stack);
        }

        return stack.pop();
    }

    private static List<String> tokenize(String expr) {
        List<String> tokens = new ArrayList<>();
        Matcher matcher = Pattern.compile("([01])|([a-z]+)|([(),])").matcher(expr);
        while (matcher.find()) {
            String token = matcher.group();
            if (token != null) tokens.add(token);
        }
        return tokens;
    }

    private static boolean isOperator(String token) {
        return token.equals("and") || token.equals("or") || token.equals("not");
    }

    private static void applyOperator(String op, Stack<Boolean> stack) {
        if (op.equals("not")) {
            boolean a = stack.pop();
            stack.push(!a);
        } else if (op.equals("and")) {
            boolean b = stack.pop();
            boolean a = stack.pop();
            stack.push(a && b);
        } else if (op.equals("or")) {
            boolean b = stack.pop();
            boolean a = stack.pop();
            stack.push(a || b);
        } else {
            throw new IllegalArgumentException("Unknown operator: " + op);
        }
    }
}
