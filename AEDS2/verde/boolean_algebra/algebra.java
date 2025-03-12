import java.util.*;
import java.util.regex.*;

public class BooleanExpressionEvaluator {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            int n = scanner.nextInt();
            try {
                boolean[] values = new boolean[n];
                for (int i = 0; i < n; i++) {
                    values[i] = scanner.nextInt() == 1 ? true : false;
                }
                String expression = scanner.nextLine();
                System.out.println(expression);

                boolean result = evaluateExpression(expression, values);
                System.out.println(result ? "1" : "0");
            } catch (Exception e) {
                continue;
            }
        }
        scanner.close();
    }

    private static boolean evaluateExpression(String expression, boolean[] values) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                // basically equates A = 0
                int letterIndex = c - 'A';
                if (letterIndex >= 0 && letterIndex < values.length) {
                    result.append(values[letterIndex] ? "1" : "0");
                }
            } else {
                result.append(c);
            }
        }
        System.out.println(result.toString());
        return evaluate(result.toString());
    }


    private static boolean evaluate(String expression) {
        List<String> tokens = tokenize(expression);
        System.out.println("t: " + tokens);
        Stack<Boolean> stack = new Stack<>();
        Stack<String> operators = new Stack<>();

        for (String token : tokens) {
            if (token.equals("1") || token.equals("0")) {
                stack.push(token.equals("1"));
            } else if (token.equals("(")) {
                operators.push(token);
            } else if (token.equals(")")) {
                // .peek() just returns last element.
                // doo all operations until the matching (, by popping from operators stack.
                while (!operators.isEmpty() && !operators.peek().equals("(")) {
                    System.out.println("Apply: " + operators + "\tstack = " + stack);
                    applyOperator(operators.pop(), stack);
                }
                // remove the trailing ), we're done with this () set.
                operators.pop();
            } else if (isOperator(token)) {
                // check for and/not/or, if so add to operators stack
                operators.push(token);
            } else {
                // might as well try to debug
                throw new IllegalArgumentException("Unknown token: " + token);
            }
            System.out.println(operators);
        }

        while (!operators.isEmpty()) {
            System.out.println("FinalApply: " + operators + "\tstack = " + stack);
            applyOperator(operators.pop(), stack);
        }

        // resulting element is our answer.
        return stack.pop();
    }

    private static List<String> tokenize(String expr) {
        List<String> tokens = new ArrayList<>();
        StringBuilder currentToken = new StringBuilder();

        for (int i = 0; i < expr.length(); i++) {
            char c = expr.charAt(i);

            // if we find a match we want to save, i.e (),
            // we save current tokenString and then we ()
            // as a new entry by itself.
            // "and(" becomes "and" and "("
            if (c == '(' || c == ')') {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
                tokens.add(String.valueOf(c));
            // if we dont really care about the next term, i.e 
            // space or commas, then we just append our current token string
            // and proceed the loop without adding the specific character.
            } else if (c == ' ' || c == ',') {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
            } else {
                // if current token is not one of the above, it means it needs to be add in full length
                // i.e "and" would be "a" "n" "d" so they get appended properly.
                currentToken.append(c);
            }
        }

        // may be needed in an edge case
        // haven't really thought when/why though.
        if (currentToken.length() > 0) {
            tokens.add(currentToken.toString());
        }

        return tokens;
    }


    private static boolean isOperator(String token) {
        return token.equals("and") || token.equals("or") || token.equals("not");
    }

    private static void applyOperator(String op, Stack<Boolean> stack) {
        if (op.equals("not")) {
            boolean a = stack.pop();
            System.out.println("op = " + op + "\t'A' = " + a + "\t'!A' = " + !a);
            stack.push(!a);
        } else if (op.equals("and")) {
            boolean b = stack.pop();
            boolean a = stack.pop();
            boolean c = a && b;
            System.out.println("op = " + op + "\t'A' = " + a + "\t'B' = " + b + "\t'A && B' = " + c);
            stack.push(c);
        } else if (op.equals("or")) {
            boolean b = stack.pop();
            boolean a = stack.pop();
            boolean c = a || b;
            System.out.println("op = " + op + "\t'A' = " + a + "\t'B' = " + b + "\tA || B = " + c);
            stack.push(c);
        } else {
            throw new IllegalArgumentException("Unknown operator: " + op);
        }
    }
}
