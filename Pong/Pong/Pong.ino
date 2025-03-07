#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Définition de l’écran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins pour capteurs ultrason Joueur 1
#define trigPin1 10
#define echoPin1 9

// Pins pour capteurs ultrason Joueur 2
#define trigPin2 8
#define echoPin2 7

// Positions et taille des palettes
float paddle1Y = 10;
float paddle2Y = 10;
const int paddleHeight = 10;

// Facteur de lissage pour mouvements fluides des palettes
const float smoothingFactor = 0.2;

// Position et vitesse de la balle
float ballX = SCREEN_WIDTH / 2;
float ballY = SCREEN_HEIGHT / 2;
float ballSpeedX = 1;
float ballSpeedY = 1;
float ballSpeedMultiplier = 1.0;  // Facteur d’accélération

// Scores
int score1 = 0;
int score2 = 0;

// Score pour gagner
#define WINNING_SCORE 7

// Affiche l'écran d'accueil au démarrage
void showWelcomeScreen() {
    display.clearDisplay();
    display.setTextSize(2); // Grand texte
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(32, 8);
    display.print("PONG");

    display.setTextSize(1); // Petit texte
    display.setCursor(70, 24);
    display.print("by Robin");

    display.display();
    delay(3000);
}

// Timer pour accélération de la balle
unsigned long lastSpeedIncrease = 0;

// Fonction pour lire la distance d’un capteur ultrason
int readUltrasonicDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;  // Convertir en cm
    return constrain(distance, 2, 30);    // Limiter pour éviter instabilité
}

// Affiche écran de victoire
void showVictoryScreen(int winner) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 5);
    display.print("PLAYER ");
    display.print(winner);
    display.setTextSize(2);
    display.setCursor(40, 15);
    display.print("WINS!");

    display.display();
    delay(5000);  // Affiche 5 secondes

    // Réinitialisation complète
    score1 = 0;
    score2 = 0;
    resetBall();
}

void setup() {
    Serial.begin(9600);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    // Affiche écran d’accueil au démarrage
    showWelcomeScreen();

    // Démarrer la partie
    resetBall();
}

void loop() {
    // Lire distances capteurs
    int distance1 = readUltrasonicDistance(trigPin1, echoPin1);
    int distance2 = readUltrasonicDistance(trigPin2, echoPin2);

    // Mapper distances en position sur écran
    int targetPaddle1Y = map(distance1, 2, 30, SCREEN_HEIGHT - paddleHeight, 0);
    int targetPaddle2Y = map(distance2, 2, 30, SCREEN_HEIGHT - paddleHeight, 0);

    // Lissage des mouvements
    paddle1Y += (targetPaddle1Y - paddle1Y) * smoothingFactor;
    paddle2Y += (targetPaddle2Y - paddle2Y) * smoothingFactor;

    // Mise à jour de la position de la balle avec vitesse accélérée
    ballX += ballSpeedX * ballSpeedMultiplier;
    ballY += ballSpeedY * ballSpeedMultiplier;

    // Rebondir sur les bords haut/bas
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - 1) {
        ballSpeedY *= -1;
    }

    // Rebondir sur les palettes ou marquer un point
    if (ballX <= 3 && ballY >= paddle1Y && ballY <= paddle1Y + paddleHeight) {
        ballSpeedX *= -1;
        accelerateBall();
    } 
    else if (ballX >= SCREEN_WIDTH - 4 && ballY >= paddle2Y && ballY <= paddle2Y + paddleHeight) {
        ballSpeedX *= -1;
        accelerateBall();
    } 
    else if (ballX < 0) {
        score2++;
        resetBall();
    } 
    else if (ballX > SCREEN_WIDTH) {
        score1++;
        resetBall();
    }

    // Vérification de la victoire
    if (score1 >= WINNING_SCORE) {
        showVictoryScreen(1);
    } 
    else if (score2 >= WINNING_SCORE) {
        showVictoryScreen(2);
    }

    // Affichage de l’état du jeu
    display.clearDisplay();
    display.drawRect(0, (int)paddle1Y, 2, paddleHeight, SSD1306_WHITE);
    display.drawRect(SCREEN_WIDTH - 2, (int)paddle2Y, 2, paddleHeight, SSD1306_WHITE);
    display.fillRect((int)ballX, (int)ballY, 2, 2, SSD1306_WHITE);

    // Affichage des scores
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 0);
    display.print("P1: ");
    display.print(score1);
    display.setCursor(80, 0);
    display.print("P2: ");
    display.print(score2);

    display.display();
    delay(30);
}

// Réinitialisation de la balle (après point ou reset complet)
void resetBall() {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballSpeedX = (random(0, 2) == 0) ? 1 : -1;  // Direction aléatoire
    ballSpeedY = (random(0, 2) == 0) ? 1 : -1;
    ballSpeedMultiplier = 1.0;  // Réinitialisation de la vitesse
    lastSpeedIncrease = millis();
}

// Accélère la balle à chaque rebond sur une palette
void accelerateBall() {
    ballSpeedMultiplier += 0.1;
}
