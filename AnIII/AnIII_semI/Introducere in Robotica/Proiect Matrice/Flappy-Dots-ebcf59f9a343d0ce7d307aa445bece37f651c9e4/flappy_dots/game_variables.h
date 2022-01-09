int previousLevel = 1;
int level = 1;
int changeLevelScore = 0;
int previousScore = 0;
int score = 0;

const int maxBirdSize = 2;

int birdMoved = 0;

// the bird can be max 3 dots
int currentBirdPosition[2][2] = {{3, 0}, {2, 1}}; 
int lastBirdPosition[2][2];

// if during this interval the player hasn't moved the bird, it will decrease on position
#define decreaseInterval 500

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
String newName = "";

const int alphabetLength = 26;
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool enterName = true;
bool changedName = false;

int currentLetterPosition = 0;
int currentLetter = 0;

// i lock the letter i'm currently writting on
bool lockedLetter = false;
