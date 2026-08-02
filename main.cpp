/*This is a simple pong game made in C++ using the Raylib library. 
The game features a player-controlled paddle and a CPU-controlled paddle, 
with a ball that bounces between them. The player can move their paddle up and down using the arrow keys, 
while the CPU paddle automatically follows the ball's position. 
The game keeps track of the score for both the player and the CPU, and 
declares a winner when one of them reaches a predefined winning score. 
Additionally, hit effects are displayed when the ball collides with either paddle, enhancing the visual feedback of the game.
*/


#include <iostream>
#include <raylib.h>
#include <vector>
#include <cstdlib>

using namespace std;

//Background Color
Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{0, 128, 128, 255};
Color LightGreen = Color{0, 255, 128, 255};
Color Yellow = Color{255, 255, 0, 255};




//Score Variables
int player_scrore = 0;
int cpu_score = 0; 

//Win Condition
const int winningScore = 7;
bool gameOver = false;
int winningTeam = 0; // 1 = player, 2 = cpu

//Check for Winner
void CheckForWinner(){
    if(player_scrore >= winningScore)
    {
        gameOver = true;
        winningTeam = 1;
    }
    else if(cpu_score >= winningScore)
    {
        gameOver = true;
        winningTeam = 2;
    }
}

//Hit Effects
struct HitEffect {
    Vector2 position;
    float radius;
    float alpha;
    Color color;
};

//Vector to store active hit effects
vector<HitEffect> hitEffects;

//Function to spawn a new hit effect
void SpawnHitEffect(Vector2 pos, Color color){
    HitEffect effect;
    effect.position = pos;
    effect.radius = 10.0f;
    effect.alpha = 1.0f;
    effect.color = color;
    hitEffects.push_back(effect);
}

//Function to update and draw hit effects
void UpdateAndDrawHitEffects(){
    for(int i = 0; i < (int)hitEffects.size(); )
    {
        hitEffects[i].radius += 3.0f;
        hitEffects[i].alpha -= 0.06f;

        if(hitEffects[i].alpha <= 0.0f)
        {
            hitEffects.erase(hitEffects.begin() + i);
        }
        else
        {
            Color c = hitEffects[i].color;
            c.a = (unsigned char)(hitEffects[i].alpha * 255);
            DrawCircleLines(hitEffects[i].position.x, hitEffects[i].position.y, hitEffects[i].radius, c);
            i++;
        }
    }
}

//Ball Class
class Ball{

    public:
    float x, y;
    int speedX, speedY;
    int radius;
    int baseSpeed = 5;
    int maxSpeed = 16;

    //Draw Ball
    void Draw(){
        DrawCircle(x, y, radius, Yellow);
    }

    //Reset Ball Position and Speed
    void ResetBall(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1, 1};
        speedX = baseSpeed * speed_choices[GetRandomValue(0, 1)];
        speedY = baseSpeed * speed_choices[GetRandomValue(0, 1)]; 
    }

    //Increase Ball Speed
    void IncreaseSpeed(){
        if(abs(speedX) < maxSpeed) speedX += (speedX > 0) ? 1 : -1;
        if(abs(speedY) < maxSpeed) speedY += (speedY > 0) ? 1 : -1;
    }

    //Update Ball Position and Check for Collisions
    void Update(){
        x += speedX;
        y += speedY;

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
        
        if(x + radius >= GetScreenWidth()) //Cpu Wins
        {
            cpu_score++;
            ResetBall();
        }

        if(x - radius <= 0) //Player Wins
        {
            player_scrore++;
            ResetBall();
        }
    }
};

//Paddle Class
class Paddle{

    //Limit Paddle Movement
    protected:
    void LimitMovemnet(){
        if(y <= 0)
        {
            y = 0;
        }

        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

    //Paddle Properties
    public:
    float x,y;
    float width, height;
    int speed;

    //Draw Paddle
    void Draw(){
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    //Update Paddle Position based on Player Input
    void Update(){
        if(IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        
        if(IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        LimitMovemnet();
    }
};

//CPU Paddle Class
class cpuPaddle: public Paddle{
    public:

    //Update CPU Paddle Position based on Ball Position
    void Update(int ballY){
        if(y + height/2 > ballY)
        {
            y -= speed;
        }

        if(y + height/2 < ballY)
        {
            y += speed;
        }
        LimitMovemnet();

    }
};

//Global Objects
Ball ball;
Paddle player;
cpuPaddle cpu;

int main () 
{
    //Initialize Window and Game Properties
    cout << "Starting the game..." << endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "My Pong Game");
    SetTargetFPS(60);

    //Ball Properties
    ball.radius = 20;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speedX = 10;
    ball.speedY = 10;
    
    //Paddle Properties
    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 15;
    
    //cpu Paddle Properties
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight/2 - cpu.height/2;
    cpu.speed = 15;
    
    //Game Loop
    while(WindowShouldClose() == false) {
        BeginDrawing();

        if(!gameOver)
        {
            //Update Ball Position
            ball.Update();
            player.Update();
            cpu.Update(ball.y);

            //Checking for Player collisions
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.speedX *= -1;
                ball.IncreaseSpeed();
                SpawnHitEffect(Vector2{ball.x, ball.y}, Yellow);
            }

            //Checking for CPU collisions
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.speedX *= -1;
                ball.IncreaseSpeed();
                SpawnHitEffect(Vector2{ball.x, ball.y}, LightGreen);
            }

            CheckForWinner();
        }


        //Drawing Paddles and Ball
        ClearBackground(DarkGreen);
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        UpdateAndDrawHitEffects();
        
        //Drawing Scores and Winner Text
        const char* playerText = TextFormat("Player: %i", player_scrore);
        int playerTextWidth = MeasureText(playerText, 80);
        DrawText(playerText, screenWidth/4 - playerTextWidth/2, 20, 80, WHITE);

        const char* cpuText = TextFormat("CPU: %i", cpu_score);
        int cpuTextWidth = MeasureText(cpuText, 80);
        DrawText(cpuText, 3 * screenWidth/4 - cpuTextWidth/2, 20, 80, WHITE);

        if(gameOver)
        {
            const char* winText = (winningTeam == 1) ? "Player Wins!" : "CPU Wins!";
            int winTextWidth = MeasureText(winText, 80);
            DrawText(winText, screenWidth/2 - winTextWidth/2, screenHeight/2 - 40, 80, WHITE);
        }


        //End Drawing
        EndDrawing();
    }
    
    
    CloseWindow();
    return 0;
}