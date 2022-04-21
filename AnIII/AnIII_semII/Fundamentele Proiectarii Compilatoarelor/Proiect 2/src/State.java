import org.javatuples.Quartet;

public class State {
    String nonterminal;
    String expression;
    int dot;
    int origin;

    public State(String nonterminal, String expression) {
        this.nonterminal = nonterminal;
        this.expression = expression;
        this.dot = 0;
        this.origin = 0;
    }

    public State(String nonterminal, String expression, int dot, int origin) {
        this.nonterminal = nonterminal;
        this.expression = expression;
        this.dot = dot;
        this.origin = origin;
    }

    public boolean isFinished() {
        return this.dot >= this.expression.length();
    }

    public Character symbol() {
        if (this.isFinished()) {
            return this.expression.charAt(this.dot);
        }
        else {
            return null;
        }
    }

    public boolean symbolIsNonterminal() {
        return this.symbol() != null & Character.isLetter(this.symbol()) & Character.isUpperCase(this.symbol());
    }

    public State shift() {
        return new State(this.nonterminal, this.expression, this.dot + 1, this.origin);
    }

    public Quartet<String, String, Integer, Integer> tuple() {
        return new Quartet<>(this.nonterminal, this.expression, this.dot, this.origin);
    }

    public int hash() {
        return this.tuple().hashCode();
    }

    public boolean eq(Quartet<String, String, Integer, Integer> other) {
        return this.tuple().equals(other);
    }

    @Override
    public String toString() {
        String n = this.tuple().getValue0();
        String e = this.tuple().getValue1();
        Integer d = this.tuple().getValue2();
        Integer o = this.tuple().getValue3();

        return String.format("[%d] %s -> %s.%s", o, n, e.substring(0,d), e.substring(d));
    }
}
