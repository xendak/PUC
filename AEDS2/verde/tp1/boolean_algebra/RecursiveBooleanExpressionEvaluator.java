import java.util.Scanner;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class RecursiveBooleanExpressionEvaluator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        while (n > 0) {
            boolean[] values = new boolean[n];
            for (int i = 0; i < n; i++) {
                values[i] = scanner.nextInt() == 1 ? true : false;
            }
            String expression = scanner.nextLine().trim();
            boolean result = evaluateExpression(expression, values);
            System.out.println(result ? "1" : "0");
            n = scanner.nextInt();
        }
        scanner.close();
    }

    private static boolean evaluateExpression(String expression, boolean[] values) {
        
        // check for NOT, grabs the substring representing the inside expression, recursively calls itself with the new expression
        if (expression.startsWith("not(")) {
            int closingIndex = findClosingParenthesis(expression, 3);
            String subExpression = expression.substring(4, closingIndex);
            return !evaluateExpression(subExpression, values);
        }
        
        // checks for AND, grabs all expressions inside
        if (expression.startsWith("and(")) {
            String content = expression.substring(4, expression.length() - 1);
            // need to split between valid and unvalid commas, so the entire remaining string is needed.
            // only commas outside parenthesis are valid, so we need a proper split function.
            String[] operands = splitExpressions(content);
            
            boolean result = true;
            for (String operand : operands) {
                result = result && evaluateExpression(operand, values);
                // short-circuit evaluation, kinda important to reduce overhead, but can be removed safely.
                if (!result) break;
            }
            return result;
        }
        
        // checks for OR, grabs all expressions inside
        if (expression.startsWith("or(")) {
            String content = expression.substring(3, expression.length() - 1);
            // need to split between valid and unvalid commas, so the entire remaining string is needed.
            // only commas outside parenthesis are valid, so we need a proper split function.
            String[] operands = splitExpressions(content);
            
            boolean result = false;
            for (String operand : operands) {
                result = result || evaluateExpression(operand, values);
                // short-circuit evaluation, kinda important to reduce overhead, but can be removed safely.
                if (result) break;
            }
            return result;
        }
        
        // evaluate a single variable
        if (expression.length() == 1 && expression.charAt(0) >= 'A' && expression.charAt(0) <= 'Z') {
            int index = expression.charAt(0) - 'A';
            if (index < values.length) {
                return values[index];
            }
        }
        
        // shouldnt reach here.
        return false;
    }

    private static int findClosingParenthesis(String expression, int start) {
        int openCount = 1;
        // we assume we already have a open pararenthesis when we call this function
        // since the call is from " EXPR( "  
        for (int i = start + 1; i < expression.length(); i++) {
            if (expression.charAt(i) == '(') {
                openCount++;
            } else if (expression.charAt(i) == ')') {
                openCount--;
                if (openCount == 0) {
                    return i;
                }
            }
        }
        return expression.length() - 1;
    }

    private static String[] splitExpressions(String content) {
        // stack because its easy to add remove the last element, for the purpose of finding the matching ()
        Stack<Character> stack = new Stack<>();
        StringBuilder currentExpression = new StringBuilder();
        List<String> expressions = new ArrayList<>();
        
        for (int i = 0; i < content.length(); i++) {
            char c = content.charAt(i);
            
            if (c == '(') {
                stack.push(c);
                currentExpression.append(c);
            } else if (c == ')') {
                stack.pop();
                currentExpression.append(c);
            } else if (c == ',' && stack.isEmpty()) {
                // only care for commas that are outside parenthesis, because those mean new expressions to evaluate
                // the stack guarantes that.
                expressions.add(currentExpression.toString().trim());
                currentExpression = new StringBuilder();
            } else {
                currentExpression.append(c);
            }
        }
        
        // guarantee that the last found expr is added properly.
        if (currentExpression.length() > 0) {
            expressions.add(currentExpression.toString().trim());
        }
        
        // this is needed to return a String[], rather than 'Object'[]
        // expression is a list of Strings, not a String itself.
        return expressions.toArray(new String[0]);
    }
}
