import java.util.ArrayList;

public class EarleyParser {
    Grammar grammar;
    ArrayList<State> states;

    public EarleyParser(Grammar grammar) {
        this.grammar = grammar;
        this.states = new ArrayList<>();
    }
}
