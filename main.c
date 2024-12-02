//
//
//  MMP""MM""YMM              `7MM"""Mq.                        `7MM"""Mq.
//  P'   MM   `7                MM   `MM.                         MM   `MM.
//       MM  .gP"Ya   ,6"Yb.    MM   ,M9  .gP"Ya `7M'   `MF'      MM   ,M9 `7Mb,od8 ,pW"Wq.   .P"Ybmmm `7Mb,od8 ,6"Yb.  `7MMpMMMb.pMMMb.  ,pP"Ybd
//       MM ,M'   Yb 8)   MM    MMmmdM9  ,M'   Yb  `VA ,V'        MMmmdM9    MM' "'6W'   `Wb :MI  I8     MM' "'8)   MM    MM    MM    MM  8I   `"
//       MM 8M""""""  ,pm9MM    MM  YM.  8M""""""    XMX          MM         MM    8M     M8  WmmmP"     MM     ,pm9MM    MM    MM    MM  `YMMMa.
//       MM YM.    , 8M   MM    MM   `Mb.YM.    ,  ,V' VA.        MM         MM    YA.   ,A9 8M          MM    8M   MM    MM    MM    MM  L.   I8
//     .JMML.`Mbmmd' `Moo9^Yo..JMML. .JMM.`Mbmmd'.AM.   .MA.    .JMML.     .JMML.   `Ybmd9'   YMMMMMb  .JMML.  `Moo9^Yo..JMML  JMML  JMML.M9mmmP'
//                                                                                           6'     dP
//                                                                                           Ybmmmd'
//
//
// Created by: Trey Adams

// referenced code examples from RayLib library of examples, found here at https://www.raylib.com/examples.html

#include <stdio.h>
#include <string.h>
#include <raylib.h>


// init games screens
typedef enum GameScreen
{
    SplashScreen = 0,
    StartScreen,
    PlayScreen
} GameScreen;

int main(void)
{
    float screenWidth = 2000;
    float screenHeight = 1200;
    
     //init window
    InitWindow(screenWidth, screenHeight, "Game");
    // get screen size
       

    printf("\nscreenWidth: %f\n", screenWidth);    
    printf("\nscreenHeight: %f\n\n", screenHeight);   

    // init mouse
    Vector2 mousePoint = {0.0f, 0.0f};
    // mouse position

    // init audio device
    InitAudioDevice();
    GameScreen currentScreen = SplashScreen;

    bool isGameOver = false;

    // -------SplashScreen--------
    Image TREX_image = LoadImage("images/TREX.png");
    Texture2D TREX_texture = LoadTextureFromImage(TREX_image);
    UnloadImage(TREX_image);
    // init top and bottom text position
    int topText_yaxis = -50;
    int bottomText_yaxis = screenHeight;

    // ------StartScreen--------
    Color startscreen_color = {251, 72, 72, 255};
    // ball size init
    int ballRadius = 50;
    // init alpha levels
    float imageTREX_alpha = 0.0f;
    float spaceText_alpha = 0.0f;
    float top_botText_alpha = 1.0f;
    
    // pingpong_image init
    Image pingPong_image = LoadImage("images/pingpongping.png");
    Texture2D pingpong_text = LoadTextureFromImage(pingPong_image);
    // free memory from Image)
    UnloadImage(pingPong_image);
    

    int fontSize = 100;
    int textWidth = MeasureText("Click to Start ", fontSize);

    // init button
    Rectangle startbutton = {((screenWidth / 2) - (textWidth / 2)-10), ((screenHeight / 2) + 350), textWidth+10, fontSize};

    // button bounds
    Rectangle startbtnbounds = {startbutton.x, startbutton.y, startbutton.width, startbutton.height};   

    // pingpongBW init
    Image pongballBW = LoadImage("images/pingpongBW.png");
    ImageResize(&pongballBW, 100, 100);
    Image startballTrans = GenImageColor(pongballBW.width, pongballBW.height, BLANK);
    Vector2 pongBallimageCenter = {pongballBW.width / 2.0f, pongballBW.height / 2.0f};
    ImageDrawCircleV(&startballTrans, pongBallimageCenter, ballRadius, WHITE);
    ImageAlphaMask(&pongballBW, startballTrans);
    Texture2D pongballBW_text = LoadTextureFromImage(pongballBW);
    UnloadImage(startballTrans);
    UnloadImage(pongballBW); 

    // ----PlayScreen------
    // init sound files
    Music startSound = LoadMusicStream("sounds/tokyo-cafe.wav");
    PlayMusicStream(startSound);
    Music playSound = LoadMusicStream("sounds/bop1.wav");
    PlayMusicStream(startSound);
    Sound ballbouncefx = LoadSound("sounds/whatever.wav");

    // adjust sound volume level
    SetSoundVolume(ballbouncefx, 0.4);
    int leftplayerscore = 0;
    int rightplayerscore = 0;
    

    // exit button
    Rectangle exit_button = {0, 0, 100, 100};
    Rectangle exit_button_bounds = {(screenWidth / 2), 30, exit_button.width, exit_button.height};

    // init bouncing ball
    Vector2 ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    Vector2 ballSpeed = {GetRandomValue(7.0f, 7.0f), GetRandomValue(7.0f, 7.0f)};
    

    // exit.png init
    Image exit_image = LoadImage("images/exitdoor.png");
    ImageResize(&exit_image, 50, 50);
    Texture2D exit_texture = LoadTextureFromImage(exit_image);
    UnloadImage(exit_image);

    // trollface.png init
    Image trollface = LoadImage("images/pingpongball.png");    
    Image circleTrans = GenImageColor(trollface.width, trollface.height, BLANK);
    Vector2 imageCenter = {trollface.width / 2.0f, trollface.height / 2.0f};
    ImageDrawCircleV(&circleTrans, imageCenter, ballRadius, WHITE);
    ImageAlphaMask(&trollface, circleTrans);    
    Texture2D troll_texture = LoadTextureFromImage(trollface);
    UnloadImage(circleTrans);
    UnloadImage(trollface);
    // ball sides for collision
    Vector2 leftsideTop = {0, 0};
    Vector2 leftsideBottom = {0, screenHeight};
    Vector2 rightsideTop = {screenWidth, 0};
    Vector2 rightsideBottom = {screenWidth, screenHeight};
    // pause menu init
    bool pause = 0;
    // init state
    int state = 0;

    // frame counter
    int framesCounter = 0;
    

    // init paddles
    Rectangle paddleLeft = {(screenWidth - (screenWidth / 16) * 15), (screenHeight / 2), 25, 100};
    Rectangle paddleRight = {(screenWidth - (screenWidth / 16) * 1), (screenHeight / 2), 25, 100};

    

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // mouse point
        mousePoint = GetMousePosition();

        // update music stream
        
        
        // splashscreen

        if (currentScreen == SplashScreen && IsKeyDown(KEY_SPACE))
        {
            // Transition to PlayScreen
            currentScreen = StartScreen;
            // Reset flags for the new screen
            
        }
        // startscreem
        if (currentScreen == StartScreen && CheckCollisionPointRec(mousePoint, startbtnbounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Transition to PlayScreen
            currentScreen = PlayScreen;
            // Reset flags for the new screen
            
        }

        // playscreen
        if (currentScreen == PlayScreen && CheckCollisionPointRec(mousePoint, exit_button_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Transition to PlayScreen
            currentScreen = StartScreen;
            // Reset flags for the new screen
            
        }

        switch (currentScreen)
        {
        // case SplashScreen
        case SplashScreen:
        {
            if (!IsMusicStreamPlaying(startSound))
            {
                PlayMusicStream(startSound);
                
            }
            UpdateMusicStream(startSound);

            if (state == 0)
            {
                topText_yaxis += 0.6f;
                if(topText_yaxis == 3)
                {
                    topText_yaxis = 3;
                }
                bottomText_yaxis -= 0.6f;
                if(bottomText_yaxis <= (screenHeight-fontSize))
                {
                    bottomText_yaxis = (screenHeight-fontSize);
                    state = 1;
                }               
            }
            else if (state == 1)
            {
                
                imageTREX_alpha += 0.007f;                
                if(imageTREX_alpha >= 1.0f)
                {
                    imageTREX_alpha = 1.0f;
                    state = 2;
                }
                
            }
            else if (state == 2)
            {
                spaceText_alpha += 0.007f;
                if (spaceText_alpha >= 1.0f)
                {
                    spaceText_alpha = 1.0f;
                        
                }
            }
                       
            break;
        }
        // case StartScreen
        case StartScreen:
        {
            UpdateMusicStream(startSound);
            // ball position
            // ball moving
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;
            // Check walls collision for bouncing
            if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius))
                ballSpeed.x *= -1.0f;
            if ((ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius))
                ballSpeed.y *= -1.0f;
            // paddle collision
            if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleLeft))
                {
                    ballSpeed.x *= -1.0f;
                    ballSpeed.y *= 1.1f;
                    ballPosition.x = paddleLeft.x + paddleLeft.width + ballRadius;
                    
                }
                // Right paddle
                if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleRight))
                {
                    ballSpeed.x *= -1.0f;
                    ballSpeed.y *= 0.8f;
                    ballPosition.x = paddleRight.x - ballRadius;
                    
                }
                // right paddle movment
                if (ballPosition.y < (paddleRight.y + paddleRight.height / 2))
                {
                    paddleRight.y -= 5.5f;
                }
                else if (ballPosition.y > (paddleRight.y + paddleRight.height / 2))
                {
                    paddleRight.y += 5.5f;
                }
                // left paddle movment
                if (ballPosition.y < (paddleLeft.y + paddleLeft.height / 2))
                {
                    paddleLeft.y -= 5.5f;
                }
                else if (ballPosition.y > (paddleLeft.y + paddleLeft.height / 2))
                {
                    paddleLeft.y += 5.5f;
                }
            break;
        }
        // case PlayScreen
        case PlayScreen:
        {
            if (IsKeyPressed(KEY_SPACE))
                pause = !pause;

            if(!isGameOver)
            {
                if (!pause)
                {
                    if (!IsMusicStreamPlaying(playSound))
                    {
                    
                        PlayMusicStream(playSound);                   
                    
                    }                
                    UpdateMusicStream(playSound);
                    // ball moving
                    ballPosition.x += ballSpeed.x;
                    ballPosition.y += ballSpeed.y;
                    // Check walls collision for bouncing
                    if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius))
                    {    
                        ballSpeed.x *= -1.0f;
                        
                        isGameOver = true;
                    }
                    if ((ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius))
                    {    
                        ballSpeed.y *= -1.0f;
                        
                    }
                    
                    // check paddles for collision
                    // ChatGPT used to adjust ball so sticking to paddle is avoided
                    // Left paddle
                    if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleLeft))
                    {
                        ballSpeed.x *= -1.0f;
                        ballSpeed.y *= 1.0f;
                        ballPosition.x = paddleLeft.x + paddleLeft.width + ballRadius;
                        PlaySound(ballbouncefx);
                    }
                    // Right paddle
                    if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleRight))
                    {
                        ballSpeed.x *= -1.0f;
                        ballSpeed.y *= 1.0f;
                        ballPosition.x = paddleRight.x - ballRadius;
                        PlaySound(ballbouncefx);
                    }
                    // Left paddle controls init
                    // Up key function
                    if (IsKeyDown(KEY_W))
                    {
                        if (paddleLeft.y >= 0)
                        {
                            paddleLeft.y -= 15.0f;
                        }
                    }
                    // Down key function
                    if (IsKeyDown(KEY_S))
                    {
                        if (paddleLeft.y + paddleLeft.height < screenHeight)
                        {
                            paddleLeft.y += 15.0f;
                        }
                    }
                    // right paddle moving
                    if (ballPosition.y < (paddleRight.y + paddleRight.height / 2))
                    {
                        paddleRight.y -= 5.5f;
                    }
                    else if (ballPosition.y > (paddleRight.y + paddleRight.height / 2))
                    {
                        paddleRight.y += 5.5f;
                    }
                    // scoreboard init
                    // left side scoreboard
                    if(CheckCollisionCircleLine(ballPosition, ballRadius, leftsideTop, leftsideBottom))
                    {
                        leftplayerscore += 1;
                    }
                    if(CheckCollisionCircleLine(ballPosition, ballRadius, rightsideTop, rightsideBottom))
                    {
                        rightplayerscore += 1;
                    }
                }
            }
            if (CheckCollisionPointRec(mousePoint, exit_button_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {    
                currentScreen = StartScreen;
                               
            }
            if(isGameOver == true)
            {              
                ballPosition = (Vector2){screenWidth/2, screenHeight/2};
                ballSpeed = ballSpeed;
                isGameOver = false;
            }
            if(IsKeyPressed(KEY_R))
            {
                isGameOver = true;
                leftplayerscore = 0;
                rightplayerscore = 0;
            }
            else
                framesCounter++;
            break;
        }
        }
        BeginDrawing();

        ClearBackground(WHITE);

        switch (currentScreen)
        {
        case SplashScreen:
        {
            // Top Text render
            DrawText("TREX Programs presents.....", 5, topText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            // TREX image render
            DrawTexture(TREX_texture, (screenWidth/2)-(TREX_texture.width/2), (screenHeight/2) - (TREX_texture.height/2), ColorAlpha(WHITE, imageTREX_alpha));
            // press space text render
            DrawText("Press SPACE to continue", 5, (screenHeight/2), 30, ColorAlpha(BLACK, spaceText_alpha));
            // bottom text render
            int productionLength = MeasureText(".....A TREX Programs production", 50);                
            DrawText(".....A TREX Programs production", screenWidth-(productionLength+5), bottomText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            
            break;
        }
        case StartScreen:
        {
            // render background color
            ClearBackground(startscreen_color);
            
            // render Ping Pong Ping logo
            DrawTexture(pingpong_text, ((screenWidth/2)-(pingpong_text.width/2)), ((screenHeight/2)-(pingpong_text.height/2)), WHITE);
            // render start button            
            bool startbutton_collision = CheckCollisionPointRec(mousePoint, startbtnbounds);
            // I used ChatGPT.com to figure out how to center the image
            // Click to Start rectangle render
            if(startbutton_collision)
            {
                DrawRectangle(startbtnbounds.x, startbtnbounds.y, startbtnbounds.width, startbtnbounds.height, BLACK);
            }
            else
            {
                DrawRectangle(startbtnbounds.x, startbtnbounds.y, startbtnbounds.width, startbtnbounds.height, startscreen_color);
            }
            // Click to Start button color render           
            if(startbutton_collision)
            {
                DrawText("Click To Start", startbtnbounds.x+10, startbtnbounds.y, startbtnbounds.height, startscreen_color);
            }
            else
            {
                DrawText("Click To Start", startbtnbounds.x+10, startbtnbounds.y, startbtnbounds.height, BLACK);
            }        
            // draw background paddles
            DrawRectangle(paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height, BLACK);
            DrawRectangle(paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height, BLACK);
            // draw ball
            DrawTexture(pongballBW_text, ballPosition.x - (pongballBW_text.width / 2), ballPosition.y - (pongballBW_text.height / 2), WHITE);
            if (pongballBW_text.id == 0)
            {
                printf("Failed to load texture.\n");
            }
            break;
        }
        case PlayScreen:
        {
            // Draw Exit Sign
            DrawText("Click to Exit", (screenWidth / 2), 0, 20, BLACK);
            DrawTexture(exit_texture, (screenWidth / 2), 30, WHITE);
            // draw score board
            DrawText(TextFormat("TEAM\nLEFT\n  %i", leftplayerscore), (((screenWidth/2)/2)/8), (screenHeight/2), 200, LIGHTGRAY);
            DrawText(TextFormat("TEAM\nRIGHT\n  %i", rightplayerscore), ((screenWidth/2)+(screenWidth/10)), screenHeight/2, 200, LIGHTGRAY);
            // Draw ball
            DrawTexture(troll_texture, ballPosition.x - (troll_texture.width / 2), ballPosition.y - (troll_texture.height / 2), WHITE);
            if (troll_texture.id == 0)
            {
                printf("Failed to load texture.\n");
            }
            // Draw Paddles
            DrawRectangle(paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height, BLACK);
            DrawRectangle(paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height, BLACK);
            // press space text
            
            
            DrawText("Controls -- | W: Up S: Down SPACE: Pause | Press R to Reset  |  Press SPACE to pause", ((screenWidth/2)/2), screenHeight-30, 20, BLACK);
            
            break;
        }
    }
    EndDrawing();
    }
    UnloadSound(ballbouncefx);
    UnloadMusicStream(startSound);
    UnloadMusicStream(playSound);
    UnloadTexture(troll_texture);
    UnloadTexture(pingpong_text);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

