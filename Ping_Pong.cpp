#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

// Enumeration for ball direction
enum eDir {
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

// Class representing the Ball object
class cBall {
private:
    int x, y;            // Current position of the ball
    int originalX, originalY;    // Original position of the ball
    eDir direction;    // Current direction of the ball

public:
    // Constructor
    cBall(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    // Reset the ball to its original position and stop it
    void Reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }

    // Change the direction of the ball
    void changeDirection(eDir d) {
        direction = d;
    }

    // Set a random direction for the ball
    void randomDirection() {
        direction = static_cast<eDir>((rand() % 6) + 1);
    }

    // Getters for ball position and direction
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }

    // Move the ball according to its direction
    void Move() {
        switch (direction) {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }

    // Overload the << operator for printing the ball's information
    friend ostream& operator<<(ostream& o, cBall c) {
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

// Class representing the Paddle object
class cPaddle {
private:
    int x, y;            // Current position of the paddle
    int originalX, originalY;    // Original position of the paddle

public:
    // Default constructor
    cPaddle() {
        x = y = 0;
    }

    // Constructor with initial position
    cPaddle(int posX, int posY) : cPaddle() {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    // Reset the paddle to its original position
    inline void Reset() { x = originalX; y = originalY; }

    // Getters for paddle position
    inline int getX() { return x; }
    inline int getY() { return y; }

    // Move the paddle up and down
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    // Overload the << operator for printing the paddle's information
    friend ostream& operator<<(ostream& o, cPaddle c) {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

// Class representing the game manager
class cGameManager {
private:
    int width, height;        // Width and height of the game screen
    int score1, score2;        // Scores of player 1 and player 2
    char up1, down1, up2, down2;    // Controls for player 1 and player 2
    bool quit;            // Flag to quit the game
    cBall* ball;        // Pointer to the ball object
    cPaddle* player1;    // Pointer to player 1's paddle object
    cPaddle* player2;    // Pointer to player 2's paddle object

public:
    // Constructor
    cGameManager(int w, int h) {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }

    // Destructor
    ~cGameManager() {
        delete ball, player1, player2;
    }

    // Update the scores and reset the game state
    void ScoreUp(cPaddle* player) {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    // Draw the game screen
    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                    cout << "O"; // Ball
                else if (player1x == j && player1y == i)
                    cout << "\xDB"; // Player 1
                else if (player2x == j && player2y == i)
                    cout << "\xDB"; // Player 2
                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB"; // Player 1
                else if (player1x == j && player1y + 2 == i)
                    cout << "\xDB"; // Player 1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB"; // Player 1
                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB"; // Player 2
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB"; // Player 2
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB"; // Player 2
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;

        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
    }

    // Process user input
    void Input() {
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        if (_kbhit()) {
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == up2)
                if (player2y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1y + 4 < height)
                    player1->moveDown();
            if (current == down2)
                if (player2y + 4 < height)
                    player2->moveDown();

            if (ball->getDirection() == STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
    }

    // Perform game logic
    void Logic() {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        // Collision detection with left paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->changeDirection((eDir)((rand() % 3) + 4));

        // Collision detection with right paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1)
                if (bally == player2y + i)
                    ball->changeDirection((eDir)((rand() % 3) + 1));

        // Collision detection with bottom wall
        if (bally == height - 1)
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

        // Collision detection with top wall
        if (bally == 0)
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

        // Collision detection with right wall
        if (ballx == width - 1)
            ScoreUp(player1);

        // Collision detection with left wall
        if (ballx == 0)
            ScoreUp(player2);
    }

    // Run the game
    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
        }
    }
};

// Main function
int main() {
    cGameManager game(40, 20);
    game.Run();
    return 0;
}
