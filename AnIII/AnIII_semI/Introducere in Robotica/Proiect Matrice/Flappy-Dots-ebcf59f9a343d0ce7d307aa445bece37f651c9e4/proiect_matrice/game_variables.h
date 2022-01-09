// General game variables
bool gameStarted = false;
bool gameFinished = false;

int previousLevel = 1;
int level = 1;
int previousScore = 0;
int score = 0;

// at the begining the bird is formed by 1 dot
int birdSize = 1;

// the bird can be max 3 dots
/*int currentBirdPosition[3][2] = {{4, 0}, {-1, -1}, {-1, -1}}; 
int lastBirdPosition[3][2];*/

// the bird is always on the first column, only the row changes 
int xPos = 3;
int yPos = 0;

int xLastPos;
int yLastPos; 

// number of cols between the walls (will decrease at a higher level) 
int wallSpacing = 4;

// if during this interval the player hasn't moved the bird, it will decrease on position
const int decreaseInterval = 2000;

// variables for the obstacles
// shape of the obstacle
int obstacle[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//position of the obstacle
int obstacleColumn = 7;
unsigned long lastMovedObstacle = 0;
int moveObstacleInterval = 1000;
int generated = 0;


// variables for the player name
int playerName[] = {0, 0, 0};

const int alphabetLength = 26;
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool enterName = false;
bool changedName = true;

int currentLetterColumn = 0;
int currentLetterRow = 0;

// i lock the letter i'm currently writting on
bool lockedLetter = false;
