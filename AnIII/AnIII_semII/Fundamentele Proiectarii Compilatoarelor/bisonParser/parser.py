class EarleyParser:
    def __init__(self, grammar):
        self.grammar = grammar
        self.states = []

    def parse(self, text):
        self.states = [set() for _ in range(len(text) + 1)]
        self.states[0].add(State(*grammar.start))
        for k, token in enumerate(text + '\u0000'):
            extension = list(self.states[k])
            self.states[k].clear()
            while extension:
                state = extension.pop()
                if state in self.states[k]:
                    continue
                self.states[k].add(state)
                if state.finished:
                    self._completer(state, extension)
                elif state.symbol_is_nonterminal:
                    self._predictor(state, k, extension)
                else:
                    self._scanner(state, k, token)
        self._print(text)

    def _predictor(self, state, origin, extension):
        for rule in self.grammar[state.symbol]:
            extension.append(State(*rule, origin=origin))

    def _scanner(self, state, origin, token):
        if state.symbol == token:
            self.states[origin + 1].add(state.shift)

    def _completer(self, state, extension):
        for reduce in self.states[state.origin]:
            if state.nonterminal == reduce.symbol:
                extension.append(reduce.shift)

    def _print(self, text):
        for k, state in enumerate(self.states):
            accepts = any(s.nonterminal == '^' and
                          s.finished for s in state)
            print('(%d)' % k, end=' ')
            print('"%s.%s"' % (text[:k], text[k:]), end=' ')
            print(accepts and 'ACCEPTS' or '')
            for i in state:
                print('\t', i)


class State:
    def __init__(self, nonterminal, expression, dot=0, origin=0):
        self.nonterminal = nonterminal
        self.expression = expression
        self.dot = dot
        self.origin = origin

    @property
    def finished(self):
        return self.dot >= len(self.expression)

    @property
    def symbol(self):
        return None if self.finished else self.expression[self.dot]

    @property
    def symbol_is_nonterminal(self):
        return self.symbol and \
               self.symbol.isalpha() and \
               self.symbol.isupper()

    @property
    def shift(self):
        return State(self.nonterminal,
                     self.expression,
                     self.dot + 1,
                     self.origin)

    @property
    def tuple(self):
        return (self.nonterminal,
                self.expression,
                self.dot,
                self.origin)

    def __hash__(self):
        return hash(self.tuple)

    def __eq__(self, other):
        return self.tuple == other.tuple

    def __str__(self):
        n, e, d, o = self.tuple
        return '[%d] %s -> %s.%s' % (o, n, e[:d], e[d:])


class Grammar:
    def __init__(self, *rules):
        self.rules = tuple(self._parse(rule) for rule in rules)

    def _parse(self, rule):
        return tuple(rule.replace(' ', '').split('::='))

    @property
    def start(self):
        return next(self['^'])

    def __getitem__(self, nonterminal):
        yield from [
            rule
            for rule in self.rules
            if rule[0] == nonterminal
        ]

grammar = Grammar(
    '^ ::= E',
    'E ::= E + T',
    'E ::= E - T',
    'E ::= T',
    'T ::= T * F',
    'T ::= T / F',
    'T ::= F',
    'F ::= ( E )',
    'F ::= - F',
    'F ::= x',
    'F ::= y',
    'F ::= z',
)

if __name__ == "__main__":
    text = input("Sir: ")
    while len(text) > 0:
        EarleyParser(grammar).parse(text)
        text = input("Sir: ")