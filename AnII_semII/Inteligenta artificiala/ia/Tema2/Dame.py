import sys
import time
import pygame
from copy import deepcopy

# setez valorile pentru numarul de coloane, randuri, inaltimea si latimea tablei de joc
WIDTH, HEIGHT = 800, 800
ROWS, COLS = 8, 8
SQUARE_SIZE = WIDTH // COLS

# setez valorile pentru culorile pe care le folosesc
RED = (255, 0, 0)       #pentru a ilustra o piesa rege
WHITE = (255, 255, 255)     #piesa si patratel
BLACK = (0, 0, 0)       #piesa si patratel
BLUE = (0, 0, 255)      #pentru a ilustra user ului posibilele mutari
GREY = (128, 128, 128)      #pentru a putea distinge piesele negre pe patratele negre


WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Carutasu Stefania: Dame')


class Piece:
    #Clasa care se ocupa de gestionarea pieselor

    PADDING = 15
    BORDER = 2

    def __init__(self, row, col, color):
        self.row = row
        self.col = col
        self.color = color
        self.king = False
        self.x = 0
        self.y = 0
        self.calc_position()

    def calc_position(self):
        """
        Calculez pozitia pe tabla a unei piese in functie de linia si coloana sa si de dimensiunea unei patratele
        """
        self.x = SQUARE_SIZE * self.col + SQUARE_SIZE // 2
        self.y = SQUARE_SIZE * self.row + SQUARE_SIZE // 2

    def make_king(self):
        #Fac o piesa sa fie rege prins schimbarea atributului king
        self.king = True

    def draw(self, window):
        #colorez piesele ca avand un un border gri pentru a putea distinge piesele negre pe patratele negre
        #o piesa considerata rege va avea un punct rosu pe ea
        radius = SQUARE_SIZE // 2 - self.PADDING
        pygame.draw.circle(window, GREY, (self.x, self.y), radius + self.BORDER)
        pygame.draw.circle(window, self.color, (self.x, self.y), radius)
        if self.king:
            pygame.draw.circle(window, RED, (self.x, self.y), radius // 3)

    def move(self, row, col):
        #schimb pozitia cand mi se da o linia si coloana la care vreau sa mut piesa
        self.row = row
        self.col = col
        self.calc_position()

    def __repr__(self):
        return str(self.color)


class Board:
    """
    Clasa care se ocupa de gestionarea tablei de joc
    """
    def __init__(self, color):
        if color == "BLACK":
            self.user_color = BLACK
            self.computer_color = WHITE
        else:
            self.user_color = WHITE
            self.computer_color = BLACK
        self.board = []
        self.black_left = self.white_left = 12  # cate piese mai are fiecare jucator
        self.black_kings = self.white_kings = 0
        self.create_board()

    # tabla initiala
    def draw_squares(self, window):
        """
        :param window: fereastra unde voi desena
        Desenez patratelele pe care vor fi pozitionate piesele de joc
        """
        # initial voi avea toate patratele negre
        window.fill(BLACK)
        # alternez patrate albe cu patrate negre
        for row in range(ROWS):
            for col in range(row % 2, COLS, 2):
                pygame.draw.rect(window, WHITE, (row * SQUARE_SIZE, col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def move(self, piece, row, col):
        """
        :param piece: piesa pe care vreau sa o mut
        :param row: linia pe care vreau sa o mut
        :param col: coloana pe care vreau sa o mut
        Verific daca piesa pe care am ajuns sa o mut a ajuns la stadiu de pisa rege sau nu
        """
        self.board[piece.row][piece.col], self.board[row][col] = self.board[row][col], self.board[piece.row][piece.col]
        piece.move(row, col)

        if row == ROWS - 1 or row == 0:
            if piece.king is False:
                piece.make_king()
                if piece.color == WHITE:
                    self.white_kings += 1
                else:
                    self.black_kings += 1

    def get_piece(self, row, col):
        """
        :param row: linia pe care se afla piesa
        :param col: coloana pe care se afla piesa
        :return: piesa de la linia si coloana date ca parametru
        """
        return self.board[row][col]

    def create_board(self):
        """
        Creez tabla de joc initiala cu toate piesele in pozitiile initiale
        """
        for row in range(ROWS):
            self.board.append([])
            for col in range(COLS):
                if col % 2 == ((row + 1) % 2):
                    if row < 3:
                        self.board[row].append(Piece(row, col, self.computer_color))
                    elif row > 4:
                        self.board[row].append(Piece(row, col, self.user_color))
                    else:
                        self.board[row].append(0)
                else:
                    self.board[row].append(0)

    def draw(self, window):
        """
        :param window: fereastra unde desenez
        Desenez fereastra si piesele
        """
        self.draw_squares(window)
        for row in range(ROWS):
            for col in range(COLS):
                piece = self.board[row][col]
                if piece != 0:
                    piece.draw(window)

    def get_valid_moves(self, piece):
        """
        :param piece: piesa pe care vreau sa o mut la un moment
        :return: returneaza un dictionar format din posibilele pozitii unde voi muta piesa
        Piesele rege se pot muta si in sus si in jos, de aceea iau in considerare in ambele cazuri
        Pasul cu care ma mut reprezinta directia (daca in sus sau in jos)

        """
        moves = {}
        left = piece.col - 1
        right = piece.col + 1
        row = piece.row
        if piece.color == self.user_color or piece.king:
            moves.update(self._look_left(row - 1, max(row - 3, -1), -1, piece.color, left))
            moves.update(self._look_right(row - 1, max(row - 3, -1), -1, piece.color, right))
        if piece.color == self.computer_color or piece.king:
            moves.update(self._look_left(row + 1, min(row + 3, ROWS), 1, piece.color, left))
            moves.update(self._look_right(row + 1, min(row + 3, ROWS), 1, piece.color, right))
        print( moves)
        return moves

    def _look_left(self, start, stop, step, color, left, skipped=[]):
        """
        :param start: locul de unde pornesc
        :param stop: locul unde ma opresc
        :param step: pasul cu care merg (in sus sau in jos)
        :param color: culoarea care muta acum
        :param left: directia in care caut (stanga sau dreapta)
        :param skipped: lista ce contine piesele peste care am sarit
        :return: dictionar ce contine locurile unde pot muta piesa selectata inspre stanga
        Cheia dictionarului va fi pozitia la care vreau sa ma mut formata din tuplu (linie, coloana)
        Fiecare pozitie ce reprezinta o cheie contine un dictionar care contine pozitiile unde pot ajunge de acolo
        (Daca sar peste o piesa vreau sa vad daca mai am cum sa sar)
        (Daca am doar loc liber in casuta respectiva atunci nu mai pot sari mai departe)
        (Verific doar pentru maxim 3 randuri mai departe adica verific daca am saritura dubla)
        """
        moves = {}
        last = []
        for r in range(start, stop, step):
            if left < 0:
                break

            current = self.board[r][left]
            if current == 0:
                if skipped and not last:
                    break
                elif skipped:
                    moves[(r, left)] = last + skipped
                else:
                    moves[(r, left)] = last

                if last:
                    if step == -1:
                        row = max(r - 3, 0)
                    else:
                        row = min(r + 3, ROWS)
                    moves.update(self._look_left(r + step, row, step, color, left - 1, skipped=last))
                    moves.update(self._look_right(r + step, row, step, color, left + 1, skipped=last))
                break
            elif current.color == color:
                break
            else:
                last = [current]

            left -= 1

        return moves

    def _look_right(self, start, stop, step, color, right, skipped=[]):
        """
        :param start: locul de unde pornesc
        :param stop: locul unde ma opresc
        :param step: pasul cu care merg
        :param color: culoarea care muta acum
        :param right: directia in care caut
        :param skipped: lista ce contine piesele peste care am sarit
        :return: dictionar ce contine locurile unde pot muta piesa selectata inspre dreapta
        Cheia dictionarului va fi pozitia la care vreau sa ma mut formata din tuplu (linie, coloana)
        Fiecare pozitie ce reprezinta o cheie contine un dictionar care contine pozitiile unde pot ajunge de acolo
        (Daca sar peste o piesa vreau sa vad daca mai am cum sa sar)
        (Daca am doar loc liber in casuta respectiva atunci nu mai pot sari mai departe)
        (Verific doar pentru maxim 3 randuri mai departe adica verific daca am saritura dubla)
        """
        moves = {}
        last = []
        for r in range(start, stop, step):
            if right >= COLS:
                break

            current = self.board[r][right]
            if current == 0:
                if skipped and not last:
                    break
                elif skipped:
                    moves[(r, right)] = last + skipped
                else:
                    moves[(r, right)] = last

                if last:
                    if step == -1:
                        row = max(r - 3, 0)
                    else:
                        row = min(r + 3, ROWS)
                    moves.update(self._look_left(r + step, row, step, color, right - 1, skipped=last))
                    moves.update(self._look_right(r + step, row, step, color, right + 1, skipped=last))
                break
            elif current.color == color:
                break
            else:
                last = [current]

            right += 1

        return moves

    def remove(self, pieces):
        #Sterg o piesa de pe tabla
        for piece in pieces:
            self.board[piece.row][piece.col] = 0
            if piece != 0:
                if piece.color == WHITE:
                    self.white_left -= 1
                else:
                    self.black_left -= 1

    def winner(self):
        #Daca alb a ramas fara piese atunci a castigat negru
        #Daca negru a ramas fara piese atunci a castigat alb
        if self.white_left <= 0:
            return BLACK
        elif self.black_left <= 0:
            return WHITE
        return None

    #Estimari ale scorului
    def evaluateScore1(self):
        if self.computer_color == BLACK:
            return self.black_left - self.white_left + (self.black_kings * 0.5 - self.white_kings * 0.5)
        else:
            return self.white_left - self.black_left + (self.white_kings * 0.5 - self.black_kings * 0.5)

    def evaluateScore2(self):
        if self.computer_color == BLACK:
            return self.black_left - self.white_left
        else:
            return self.white_left - self.black_left

    def getAllPieces(self, color):
        """
        :param color: culoarea dorita (alb sau negru)
        :return: o lista formata din toate piesele de culoarea data ca parametru
        """
        pieces = []
        for r in self.board:
            for p in r:
                if p != 0 and p.color == color:
                    pieces.append(p)
        return pieces


class Game:
    #Clasa care se ocupa de gestionarea jocului
    def __init__(self, window, user_color):
        self.selected = None
        self.board = Board(user_color)
        self.turn = BLACK       #negrul muta primul asa ca initializez jocul cu negru
        self.valid_moves = {}
        self.window = window

    def DrawConsoleBoard(self):
        #Afisez in consola configuratia curenta a tablei de joc si cine muta
        if self.turn == self.board.computer_color:
            print("Computer moves")
        else: print("Player moves")

        for r in range(ROWS):
            for c in range(COLS):
                if self.board.board[r][c] == 0:
                    print('#', end=" ")
                elif self.board.board[r][c].color == BLACK:
                    print('B', end=" ")
                else:
                    print("W", end=" ")
            print()
        print('\n')

    def update(self):
        #actualizez jocul in interfata grafica
        self.board.draw(self.window)
        self.draw_valid_moves(self.valid_moves)
        pygame.display.update()

    def _init(self, color):
        #initializez iar jocul
        self.selected = None
        self.board = Board(color)
        self.turn = BLACK
        self.valid_moves = {}

    def reset(self, color):
        #resetez jocul
        self.DrawConsoleBoard()
        self._init(color)

    def select(self, row, col):

        """
        :param row: linia de pe care vreau sa selectez o piesa
        :param col: coloana de pe care vreau sa selectez piesa
        :return: True daca s-a putut face selectia, False altfel
        """
        if self.selected:
            result = self._move(row, col)
            if not result:
                self.selected = None
                self.select(row, col)

        piece = self.board.get_piece(row, col)
        if piece != 0 and piece.color == self.turn:
            self.selected = piece
            self.valid_moves = self.board.get_valid_moves(piece)

            return True
        return False

    def _move(self, row, col):
        """
        :param row: linia pe care doresc sa mut
        :param col: coloana pe care doresc sa mut
        Verific daca mutarea pe care vreau sa o fac este valida
        Daca dupa efectuarea mutarii am sarit peste piese ale adversarului atunci le sterg de pe tabla
        Schimb randul (daca tocmai a mutat alb atunci va fi randul lui negru si invers)
        """
        piece = self.board.get_piece(row, col)
        if self.selected and piece == 0 and (row, col) in self.valid_moves:
            self.board.move(self.selected, row, col)
            skipped = self.valid_moves[(row, col)]
            if skipped:
                self.board.remove(skipped)
            self.change_turn()

        else:
            return False
        return True

    def change_turn(self):
        # Daca tocmai a mutat alb atunci va fi randul lui negru si invers
        self.valid_moves = {}
        if self.turn == self.board.user_color:
            self.turn = self.board.computer_color
        else:
            self.turn = self.board.user_color
        self.DrawConsoleBoard()

    def draw_valid_moves(self, moves):
        """
        :param moves: Mutarile valide pentru piesa selectata
        Ii afisez utilizatorului unde se poate misca piesa pe care a selectat-o
        """
        for move in moves:
            row, col = move
            pygame.draw.circle(self.window, BLUE,
                               (col * SQUARE_SIZE + SQUARE_SIZE // 2, row * SQUARE_SIZE + SQUARE_SIZE // 2), 15)

    def winner(self):
        """
        :return: cine a castigat (alb sau negru)
        """
        return self.board.winner()

    def getBoard(self):
        """
        :return: configuratia actuala a tablei de joc
        """
        return self.board

    def computerMove(self, board):
        """
        :param board: configuratia actuala a tablei
        Schimb randul dupa ce a mutat calculatorul
        """
        self.board = board
        self.change_turn()

def MiniMax(board, depth, JMAX, game, noOfNodes):
    """
    :param board: configuratia actuala
    :param depth: adancimea pana a care vreau sa merg
    :param JMAX: verific daca este jucatorul care incearca sa maximizeze
    :param game: jocul curent
    :return: Evaluarea mutarii si tabla
    Primeste tabla cu toate piese la momentul curent, cate mutari vreau sa consider, daca vreau sa maximizez scorul sau sa il minimizez

    """
    if depth == 0 or board.winner() != None:        #daca am ajuns la adancimea maxima sau daca am gasit un castigator
        return board.evaluateScore1(), board      #evaluez configuratia curenta si o returnez
    if JMAX:    #evaluez pentru jucatorul care incearca sa maximizeze scorul
        maxEval = float('-inf')
        bestMove = None
        for move in GetAllMoves(board, game.getBoard().computer_color, game):        #parcurg toate mutarile posibile pentru jucatorul JMAX
            noOfNodes += 1
            evaluation = MiniMax(move, depth - 1, False, game, noOfNodes)[0]
            maxEval = max(maxEval, evaluation)

            if maxEval == evaluation:
                bestMove = move
        return maxEval, bestMove, noOfNodes

    else:       #evaluez pentru jucatorul care incearca sa minimizeze scorul
        minEval = float('inf')
        bestMove = None
        for move in GetAllMoves(board, game.getBoard().user_color, game):        #parcurg toate mutarile posibile pentru jucatorul JMIN
            noOfNodes += 1
            evaluation = MiniMax(move, depth - 1, True, game, noOfNodes)[0]
            minEval = min(minEval, evaluation)

            if minEval == evaluation:
                bestMove = move
        return minEval, bestMove

def AlphaBeta(alpha, beta, board, depth, JMAX, game, noOfNodes):
    """
    :param alpha: valoarea lui alpha
    :param beta: valoarea lui beta
    :param board: configuratia actuala
    :param depth: adancimea pana a care vreau sa merg
    :param JMAX: verific daca este jucatorul care incearca sa maximizeze
    :param game: jocul curent
    :return: Evaluarea mutarii si tabla
    Primeste tabla cu toate piese la momentul curent, cate mutari vreau sa consider, daca vreau sa maximizez scorul sau sa il minimizez

    """
    if depth == 0 or board.winner() != None:        #daca am ajuns la adancimea maxima sau daca am gasit un castigator
        return board.evaluateScore1(), board      #evaluez configuratia curenta si o returnez
    if alpha > beta:
        return board.evaluateScore1(), board
    if JMAX:    #evaluez pentru jucatorul care incearca sa maximizeze scorul
        maxEval = float('-inf')
        bestMove = None
        for move in GetAllMoves(board, game.getBoard().computer_color, game):        #parcurg toate mutarile posibile pentru jucatorul JMAX
            noOfNodes += 1
            evaluation = MiniMax(move, depth - 1, False, game, noOfNodes)[0]
            maxEval = max(maxEval, evaluation)
            if alpha < evaluation:
                alpha = evaluation
                if alpha >= beta:
                    break
            if maxEval == evaluation:
                bestMove = move
        return maxEval, bestMove, noOfNodes

    else:       #evaluez pentru jucatorul care incearca sa minimizeze scorul
        minEval = float('inf')
        bestMove = None
        for move in GetAllMoves(board, game.getBoard().user_color, game):        #parcurg toate mutarile posibile pentru jucatorul JMIN
            noOfNodes += 1
            evaluation = MiniMax(move, depth - 1, True, game, noOfNodes)[0]
            minEval = min(minEval, evaluation)
            if beta > evaluation:
                beta = evaluation
                if alpha >= beta:
                    break
            if minEval == evaluation:
                bestMove = move
        return minEval, bestMove, noOfNodes

def SimulateMove(piece, move, board, game, skip):
    """
    :param piece: piesa pe care vreau sa o mut
    :param move: linia si coloana pe care vreau sa o mut
    :param board: configuratia actuala a tablei
    :param game: jocul actual
    :param skip: daca am sarit peste vreo piesa
    :return: configuratia tablei dupa ce mut piesa
    Simulez mutarea unei anumite piese
    """
    board.move(piece, move[0], move[1])
    if skip:
        board.remove(skip)

    return board

def GetAllMoves(board, color, game):
    """
    :param position: pozitia piesei pe care vreau sa o mut
    :param color: culoarea piesei
    :param game: jocul actual
    :return: lista formata din configuratiile posibile ale tablei dupa ce se pot efectua mutarile posibile
    """
    moves = []
    for p in board.getAllPieces(color):
        valid_moves = board.get_valid_moves(p)
        for move, skip in valid_moves.items():
            temp_board = deepcopy(board)
            temp_piece = temp_board.get_piece(p.row, p.col)
            new_board = SimulateMove(temp_piece, move, temp_board, game, skip)
            moves.append(new_board)

    return moves


class Buton:
    def __init__(
            self,
            display=None,
            left=0,
            top=0,
            w=0,
            h=0,
            culoareFundal=(53, 80, 115),
            culoareFundalSel=(89, 134, 194),
            text="",
            font="arial",
            fontDimensiune=16,
            culoareText=(255, 255, 255),
            valoare="",
    ):
        self.display = display
        self.culoareFundal = culoareFundal
        self.culoareFundalSel = culoareFundalSel
        self.text = text
        self.font = font
        self.w = w
        self.h = h
        self.selectat = False
        self.fontDimensiune = fontDimensiune
        self.culoareText = culoareText
        fontObj = pygame.font.SysFont(self.font, self.fontDimensiune)
        self.textRandat = fontObj.render(self.text, True, self.culoareText)
        self.dreptunghi = pygame.Rect(left, top, w, h)
        self.dreptunghiText = self.textRandat.get_rect(center=self.dreptunghi.center)
        self.valoare = valoare

    def selecteaza(self, sel):
        self.selectat = sel
        self.deseneaza()

    def selecteazaDupacoord(self, coord):
        if self.dreptunghi.collidepoint(coord):
            self.selecteaza(True)
            return True
        return False

    def updateDreptunghi(self):
        self.dreptunghi.left = self.left
        self.dreptunghi.top = self.top
        self.dreptunghiText = self.textRandat.get_rect(center=self.dreptunghi.center)

    def deseneaza(self):
        culoareF = self.culoareFundalSel if self.selectat else self.culoareFundal
        pygame.draw.rect(self.display, culoareF, self.dreptunghi)
        self.display.blit(self.textRandat, self.dreptunghiText)


class GrupButoane:
    def __init__(
            self, listaButoane=[], indiceSelectat=0, spatiuButoane=10, left=0, top=0
    ):
        self.listaButoane = listaButoane
        self.indiceSelectat = indiceSelectat
        self.listaButoane[self.indiceSelectat].selectat = True
        self.top = top
        self.left = left
        leftCurent = self.left
        for b in self.listaButoane:
            b.top = self.top
            b.left = leftCurent
            b.updateDreptunghi()
            leftCurent += spatiuButoane + b.w

    def selecteazaDupacoord(self, coord):
        for ib, b in enumerate(self.listaButoane):
            if b.selecteazaDupacoord(coord):
                self.listaButoane[self.indiceSelectat].selecteaza(False)
                self.indiceSelectat = ib
                return True
        return False

    def deseneaza(self):
        # atentie, nu face wrap
        for b in self.listaButoane:
            b.deseneaza()

    def getValoare(self):
        return self.listaButoane[self.indiceSelectat].valoare

############# ecran initial ########################
def deseneaza_alegeri(display, tabla_curenta):
    btn_alg = GrupButoane(
        top=30,
        left=30,
        listaButoane=[
            Buton(display=display, w=80, h=30, text="minimax", valoare="minimax"),
            Buton(display=display, w=80, h=30, text="alphabeta", valoare="alphabeta"),
        ],
        indiceSelectat=0,
    )
    btn_juc = GrupButoane(
        top=100,
        left=30,
        listaButoane=[
            Buton(display=display, w=80, h=30, text="BLACK", valoare="BLACK"),
            Buton(display=display, w=80, h=30, text="WHITE", valoare="WHITE"),
        ],
        indiceSelectat=1,
    )
    btn_dificultate = GrupButoane(
        top=170,
        left=30,
        listaButoane=[
            Buton(display=display, w=180, h=30, text="BEGINNER", valoare="2"),
            Buton(display=display, w=180, h=30, text="INTERMEDIATE", valoare="4"),
            Buton(display=display, w=180, h=30, text="ADVANCED", valoare="6"),
        ],
        indiceSelectat=0,
    )

    btn_tip_joc = GrupButoane(
        top=240,
        left=30,
        listaButoane=[
            Buton(display=display, w=180, h=30, text="Player vs Computer", valoare="cp"),
            Buton(display=display, w=180, h=30, text="Player vs Player", valoare="pp"),
            Buton(display=display, w=180, h=30, text="Computer vs Computer", valoare="cc"),
        ],
        indiceSelectat=0,
    )

    ok = Buton(
        display=display,
        top=310,
        left=30,
        w=40,
        h=30,
        text="ok",
        culoareFundal=(155, 0, 55),
    )
    btn_dificultate.deseneaza()
    btn_alg.deseneaza()
    btn_juc.deseneaza()
    btn_tip_joc.deseneaza()
    ok.deseneaza()
    while True:
        for ev in pygame.event.get():
            if ev.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif ev.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                if not btn_alg.selecteazaDupacoord(pos):
                    if not btn_juc.selecteazaDupacoord(pos):
                        if not btn_dificultate.selecteazaDupacoord(pos):
                            if not btn_tip_joc.selecteazaDupacoord(pos):
                                if ok.selecteazaDupacoord(pos):
                                    tabla_curenta.reset(btn_juc.getValoare())
                                    return btn_juc.getValoare(), btn_alg.getValoare(), btn_dificultate.getValoare(), btn_tip_joc.getValoare()
        pygame.display.update()


def get_with_mouse(pos):
    x, y = pos
    row = y // SQUARE_SIZE
    col = x // SQUARE_SIZE

    return row, col


def main():
    pygame.init()
    run = True
    game = Game(WINDOW, "WHITE")
    color, algorithm, depth, game_type = deseneaza_alegeri(WINDOW, game)
    if color == "BLACK":
        user_color = BLACK
        computer_color = WHITE
    else:
        user_color = WHITE
        computer_color = BLACK
    #am jocul computer vs player
    if game_type == "cp":
        initial_time_game = int(round(time.time() * 1000))
        #initializez pentru a putea afisa la final statisticile
        min_nodes = float('inf')
        max_nodes = float('-inf')
        media_nodes = 0
        min_time = float('inf')
        max_time = float('-inf')
        media_time = 0
        nr_runde = 0

        while run:
            if game.turn == computer_color:
                t_inainte = int(round(time.time() * 1000))
                if algorithm == "alphabeta":
                    value, new_board, nodes = AlphaBeta(-500, 500, game.getBoard(), int(depth), computer_color, game, 0)
                    game.computerMove(new_board)
                else:
                    value, new_board, nodes = MiniMax(game.getBoard(), int(depth), computer_color, game, 0)
                    game.computerMove(new_board)

                t_dupa = int(round(time.time() * 1000))
                print(
                    'Calculatorul a "gandit" timp de '
                    + str(t_dupa - t_inainte)
                    + " milisecunde."
                )
                nr_runde += 1

                print("Numarul de noduri: ", nodes)
                if nodes < min_nodes:
                    min_nodes = nodes
                elif nodes > max_nodes:
                    max_nodes = nodes
                media_nodes += nodes

                media_time += (t_dupa - t_inainte)
                if t_dupa - t_inainte > max_time:
                    max_time = t_dupa - t_inainte
                elif t_dupa - t_inainte < min_time:
                    min_time = t_dupa - t_inainte

            if game.winner() != None:
                if game.winner() == game.getBoard().computer_color:
                    print("Computer won")
                else: print("Player won")
                run = False

            if game.turn == user_color:
                t_inainte = int(round(time.time() * 1000))
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        run = False
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        pos = pygame.mouse.get_pos()
                        row, col = get_with_mouse(pos)
                        game.select(row, col)
                        t_dupa = int(round(time.time() * 1000))
                        if t_dupa - t_inainte != 0:
                            print(
                                'Player-ul a "gandit" timp de '
                                + str(t_dupa - t_inainte)
                                + " milisecunde."
                            )

            game.update()
        print("\nStatistici pentru calculator")
        print("Timpul minim al calculatorului: " + str(min_time) + " milisecunde" )
        print("Timpul maxim al calculatorului: " +  str(max_time) + " milisecunde")
        print("Media de timp: " + str(media_time / nr_runde) + " milisecunde" )
        print("Numarul minim de noduri: ", min_nodes)
        print("Numarul maxim de noduri: ", max_nodes)
        print("Media de noduri: ", media_nodes / nr_runde)
        final_time_game = int(round(time.time() * 1000))
        print("\nTimpul total de joc:", final_time_game - initial_time_game, "milisecunde")
        pygame.quit()
    #am jocul player vs player
    elif game_type == "pp":
        while run:

            if game.winner() != None:
                if game.winner() == game.getBoard().computer_color:
                    print("Computer won")
                else:
                    print("Player won")
                run = False

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                if event.type == pygame.MOUSEBUTTONDOWN:
                    pos = pygame.mouse.get_pos()
                    row, col = get_with_mouse(pos)
                    game.select(row, col)
            game.update()
        pygame.quit()
    #am jocul computer vs computer
    else:
        while run:
            if game.winner() != None:
                if game.winner() == game.getBoard().computer_color:
                    print("Computer won")
                else:
                    print("Player won")
                run = False

            if game.turn == computer_color:
                if algorithm == "alphabeta":
                    value, new_board = AlphaBeta(-500, 500, game.getBoard(), int(depth), computer_color, game)
                    game.computerMove(new_board)
                else:
                    value, new_board = MiniMax(game.getBoard(), int(depth), computer_color, game)
                    game.computerMove(new_board)
            else:
                if algorithm == "alphabeta":
                    value, new_board = AlphaBeta(-500, 500, game.getBoard(), int(depth), user_color, game)
                    game.computerMove(new_board)
                else:
                    value, new_board = MiniMax(game.getBoard(), int(depth), user_color, game)
                    game.computerMove(new_board)

            game.update()

        pygame.quit()

main()