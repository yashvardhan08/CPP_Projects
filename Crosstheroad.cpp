#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>
using namespace std;

// Class representing the player
class cPlayer
{
public:
    int x, y;

    // Constructor to initialize the player's position
    cPlayer(int width)
    {
        x = width / 2;
        y = 0;
    }
};

// Class representing a lane with moving cars
class cLane
{
private:
    deque<bool> cars;
    bool right;

public:
    // Constructor to initialize the lane with cars
    cLane(int width)
    {
        for (int i = 0; i < width; i++)
            cars.push_front(true);
        right = rand() % 2;
    }

    // Move the cars in the lane
    void Move()
    {
        if (right)
        {
            if (rand() % 10 == 1)
                cars.push_front(true);
            else
                cars.push_front(false);
            cars.pop_back();
        }
        else
        {
            if (rand() % 10 == 1)
                cars.push_back(true);
            else
                cars.push_back(false);
            cars.pop_front();
        }
    }

    // Check if a car is present at the specified position in the lane
    bool CheckPos(int pos)
    {
        return cars[pos];
    }

    // Change the direction of car movement in the lane
    void ChangeDirection()
    {
        right = !right;
    }
};

// Class representing the game
class cGame
{
private:
    bool quit;
    int numberOfLanes;
    int width;
    int score;
    cPlayer *player;
    vector<cLane *> map;

public:
    // Constructor to initialize the game
    cGame(int w = 20, int h = 10)
    {
        numberOfLanes = h;
        width = w;
        quit = false;

        // Create lanes and add them to the game map
        for (int i = 0; i < numberOfLanes; i++)
            map.push_back(new cLane(width));

        // Create the player
        player = new cPlayer(width);
    }

    // Destructor to free the allocated memory
    ~cGame()
    {
        delete player;
        for (int i = 0; i < map.size(); i++)
        {
            cLane *current = map.back();
            map.pop_back();
            delete current;
        }
    }

    // Draw the game screen
    void Draw()
    {
        system("cls");
        for (int i = 0; i < numberOfLanes; i++)
        {
            for (int j = 0; j < width; j++)
            {
                // Draw start and finish lines
                if (i == 0 && (j == 0 || j == width - 1))
                    cout << "S";
                if (i == numberOfLanes - 1 && (j == 0 || j == width - 1))
                    cout << "F";

                // Draw cars and player
                if (map[i]->CheckPos(j) && i != 0 && i != numberOfLanes - 1)
                    cout << "#";
                else if (player->x == j && player->y == i)
                    cout << "V";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }

    // Handle user input
    void Input()
    {
        if (_kbhit())
        {
            char current = _getch();
            if (current == 'a')
                player->x--;
            if (current == 'd')
                player->x++;
            if (current == 'w')
                player->y--;
            if (current == 's')
                player->y++;
            if (current == 'q')
                quit = true;
        }
    }

    // Update the game logic
    void Logic()
    {
        // Move the cars and check for collisions
        for (int i = 1; i < numberOfLanes - 1; i++)
        {
            if (rand() % 10 == 1)
                map[i]->Move();
            if (map[i]->CheckPos(player->x) && player->y == i)
                quit = true;
        }

        // Increase the score and change the direction of a random lane
        if (player->y == numberOfLanes - 1)
        {
            score++;
            player->y = 0;
            cout << "\x07";
            map[rand() % numberOfLanes]->ChangeDirection();
        }
    }

    // Run the game loop
    void Run()
    {
        while (!quit)
        {
            Input();
            Draw();
            Logic();
        }
    }
};

int main()
{
    srand(time(NULL));

    // Create and run the game
    cGame game(30, 5);
    game.Run();

    cout << "Game over!" << endl;
    getchar();
    return 0;
}
