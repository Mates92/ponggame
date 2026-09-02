#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>

#define Max_main_menu 5
#define ballSpeed 0.5

sf::Event event;
sf::Texture texture;
sf::Sprite sprite;
sf::RectangleShape Lwall(sf::Vector2f(20.f, 200.f));
sf::RectangleShape Rwall(sf::Vector2f(20.f, 200.f));
sf::RectangleShape middleWall(sf::Vector2f(10.f, 2000.f));
sf::CircleShape ball;
sf::CircleShape blackScreen;

// MAIN MENU
sf::RectangleShape n0(sf::Vector2f(300.f, 50.f));
sf::RectangleShape n1(sf::Vector2f(300.f, 50.f));
sf::RectangleShape n2(sf::Vector2f(300.f, 50.f));
sf::RectangleShape n3(sf::Vector2f(300.f, 50.f));

sf::Text t0, t1, t2, t3, MainTitle, sub,ScoreL,ScoreR,GameOver,Settings,OverText;

sf::Vector2f LwallPos;
sf::Vector2f ballPos;
sf::Vector2f RwallPos;

bool aimingPlayer;
bool Bupmove;
bool Bdownmove;
bool Pupmove;
bool Pdownmove;
bool PHIT;
bool gameEnded;
bool MenuPressed;
bool fontTrue;
bool allowedToScore = false;
int menuHover = 0;
int LwallCenter;
int scoreL, scoreR;
int pole[50];
int i;
int n;
int j;

std::string strL = std::to_string(scoreL);
std::string strR = std::to_string(scoreR);


sf::Font font;

void player_move() {
    switch (event.key.code) {
    case(sf::Keyboard::W):
        Lwall.move(0.f, -40.f);
        Pupmove = true;
        Pdownmove = false;
        break;
    case(sf::Keyboard::S):
        Lwall.move(0.f, +40.f);
        Pdownmove = true;
        Pupmove = false;
        break;
    }
}

void P2_move() {
    switch (event.key.code) {
    case(sf::Keyboard::Up):
        Rwall.move(0.f, -40.f);
        break;
    case(sf::Keyboard::Down):
        Rwall.move(0.f, +40.f);
        break;
    }
}

void ballMovement() {
    switch (aimingPlayer) {
    case true:
        ballPos.x -= ballSpeed;
        break;
    case false:
        ballPos.x += ballSpeed;
        break;
    }
}

void getLwallCenter() {
    LwallPos = Lwall.getPosition();
    LwallCenter = LwallPos.y - (200 / 2);
}

void hitConditions() {
    int L = 0, R = 0;
    if (ballPos.y - LwallPos.y >= 0 && (LwallPos.y + 200) >= ballPos.y) L = 1;
    if (ballPos.y - RwallPos.y >= 0 && (RwallPos.y + 200) >= ballPos.y) R = 1;

    if (ballPos.x >= RwallPos.x && R == 1) {
        aimingPlayer = !aimingPlayer;
        allowedToScore = true;
        PHIT = false;
    }
    if (ballPos.x <= LwallPos.x && L == 1) {
        aimingPlayer = !aimingPlayer;
        allowedToScore = true;
        PHIT = true;
    }
}

void UDmovement() {
    if (Pupmove == true) Bupmove = true;
    if (Pdownmove == true) Bdownmove = true;
    if (Pupmove == true && PHIT == true) ballPos.y -= 0.1;
    if (Pdownmove == true && PHIT == true) ballPos.y += 0.1;
}

void EnemyAI() {
    if (RwallPos.y < ballPos.y - 20) Rwall.move(0.0f, 1.0f);
    if (RwallPos.y > ballPos.y - 20) Rwall.move(0.0f, -1.0f);
}

void GameEnding() {
    if ((ballPos.x + 1000) < LwallPos.x) {
    if(allowedToScore) scoreR++;
    allowedToScore = false;
    ballPos.x = 1000;
    ballPos.y = 400;
    Lwall.setPosition(500, 400);
    Rwall.setPosition(1300, 400);
    middleWall.setPosition(900, 0);
    Pupmove = false;
    Pdownmove = false;
    }
    if (scoreL == 10 || scoreR == 10) gameEnded = true;  //ZMENIT NA 10
    if ((ballPos.x - 1000) > RwallPos.x) {
    if(allowedToScore) scoreL++;
    allowedToScore = false;
    ballPos.x = 1000;
    ballPos.y = 400;
    Lwall.setPosition(500, 400);
    Rwall.setPosition(1300, 400);
    middleWall.setPosition(900, 0);
    Pupmove = false;
    Pdownmove = false;
    }

    std::string strL = std::to_string(scoreL);
    std::string strR = std::to_string(scoreR);

    ScoreL.setFont(font);
    ScoreL.setString(strL);
    ScoreL.setCharacterSize(50);
    ScoreL.setFillColor(sf::Color::White);
    ScoreL.setPosition(100, 100);

    ScoreR.setFont(font);
    ScoreR.setString(strR);
    ScoreR.setCharacterSize(50);
    ScoreR.setFillColor(sf::Color::White);
    ScoreR.setPosition(1500, 100);
}

void MenuSelection() {
    if (event.type == sf::Event::KeyPressed)
    switch (event.key.code) {
    case(sf::Keyboard::S):
        if(menuHover < 3)menuHover++;
        break;
    case(sf::Keyboard::W):
        if(menuHover > 0)menuHover--;
        break;
    case(sf::Keyboard::Enter):
        MenuPressed = !MenuPressed;
        break;
    }
    
    switch (menuHover) {
    case 0:
        t0.setFillColor(sf::Color::Red);
        break;
    case 1:
        t1.setFillColor(sf::Color::Red);
        break;
    case 2:
        t2.setFillColor(sf::Color::Red);
        break;
    case 3:
        t3.setFillColor(sf::Color::Red);
        break;
    }
}

void SetUpPole() {
    
    srand(time(0));
    for (int i = 0; i < 50; i++) {
        pole[i] = rand() % 49 + 1;

    }
}
void AI() {

    if (pole[i] == pole[j]) SetUpPole();

    if (pole[i] > 12 && n == 5) {
        if (RwallPos.y < 800 && RwallPos.y > 100) {
            if (ballPos.y > RwallPos.y) Rwall.move(0.f, 2.f);
            if (ballPos.y < RwallPos.y) Rwall.move(0.f, -2.f);
            if (ballPos.y == RwallPos.y) ball.move(0.f, 1.f);
            n = 0;
        }
        if (pole[i] < 12 && n == 5) {
            if (RwallPos.y < 800 && RwallPos.y > 100) {
                if (ballPos.y > RwallPos.y) Rwall.move(0.f, -2.f);
                if (ballPos.y < RwallPos.y) Rwall.move(0.f, 2.f);
                if (ballPos.y == RwallPos.y) ball.move(0.f, 1.f);
                n = 0;
            }
        }
    }
        n = n + 1;
        j = i;
        if (n % 11 == 0) n = 0;
        srand(time(0));
        i = rand() % 100; 
        
}

void FileSave() {
    if (event.key.code == sf::Keyboard::O) {
        std::ofstream Save("gamefile.txt");
        Save << scoreL << " " << scoreR <<std::endl;
        for (int i = 0; i < 50; i++) {
            Save << pole[i] << " ";
        }
        Save << std::endl;
        Save << menuHover;
    }
    if (event.key.code == sf::Keyboard::P) {
        std::ifstream Save("gamefile.txt");
        Save >> scoreL >> scoreR;
        Save.close();
        std::cout << scoreL << scoreR << std::endl;
        for (int i = 0; i < 50; i++) {
            std::cout << pole[i] << " ";
        }       std::cout << std::endl;
        std::cout << menuHover;
        Save.close();
    }
}

void BackToMenu() {
    if (event.key.code == sf::Keyboard::U) {
        MenuPressed = false;
        gameEnded = false;
        if (scoreL || scoreR == 10) {
            scoreL = 0;
            scoreR = 0;
        }
    }
}

void GameSetUp() {
    fontTrue = false;
    gameEnded = false;
    ballPos.x = 1000;
    ballPos.y = 400;
    ball.setRadius(15);
    aimingPlayer = false;
    Lwall.setPosition(500, 400);
    Rwall.setPosition(1300, 400);
    blackScreen.setPosition(-1800, -300);
    blackScreen.setRadius(3000);
    middleWall.setPosition(900, 0);
    middleWall.setFillColor(sf::Color(255, 255, 255, 80));
    Lwall.setFillColor(sf::Color::Green);
    Rwall.setFillColor(sf::Color::Red);
    ball.setFillColor(sf::Color::White);
    blackScreen.setFillColor(sf::Color::Black);



    n0.setFillColor(sf::Color::White);
    n1.setFillColor(sf::Color::White);
    n2.setFillColor(sf::Color::White);
    n3.setFillColor(sf::Color::White);

    n0.setPosition(800, 300);
    n1.setPosition(800, 400);
    n2.setPosition(800, 500);
    n3.setPosition(800, 600);

    t0.setFont(font);
    t0.setString("Player vs AI");
    t0.setCharacterSize(24);
    t0.setFillColor(sf::Color::Black);
    t0.setPosition(n0.getPosition().x + (n0.getSize().x - t0.getLocalBounds().width) / 3.5,
        n0.getPosition().y + (n0.getSize().y - t0.getLocalBounds().height) / 4);

    t1.setFont(font);
    t1.setString("Player vs Player");
    t1.setCharacterSize(24);
    t1.setFillColor(sf::Color::Black);
    t1.setPosition(n1.getPosition().x + (n1.getSize().x - t1.getLocalBounds().width) / 4.5,
        n1.getPosition().y + (n1.getSize().y - t1.getLocalBounds().height) / 4);

    t2.setFont(font);
    t2.setString("Settings");
    t2.setCharacterSize(24);
    t2.setFillColor(sf::Color::Black);
    t2.setPosition(n2.getPosition().x + (n2.getSize().x - t2.getLocalBounds().width) / 3,
        n2.getPosition().y + (n2.getSize().y - t2.getLocalBounds().height) / 4);

    t3.setFont(font);
    t3.setString("Quit");
    t3.setCharacterSize(24);
    t3.setFillColor(sf::Color::Black);
    t3.setPosition(n3.getPosition().x + (n3.getSize().x - t3.getLocalBounds().width) /2.5,
        n3.getPosition().y + (n3.getSize().y - t3.getLocalBounds().height) / 4);

    MainTitle.setFont(font);
    MainTitle.setString("PONG");
    MainTitle.setCharacterSize(100);
    MainTitle.setFillColor(sf::Color::White);
    MainTitle.setPosition(800, 50);

    sub.setFont(font);
    sub.setString("move up by W\nmove down by S");
    sub.setCharacterSize(15);
    sub.setFillColor(sf::Color::White);
    sub.setPosition(850, 150);

    ScoreL.setFont(font);
    ScoreL.setString(strL);
    ScoreL.setCharacterSize(50);
    ScoreL.setFillColor(sf::Color::White);
    ScoreL.setPosition(100, 100);

    ScoreR.setFont(font);
    ScoreR.setString(strR);
    ScoreR.setCharacterSize(50);
    ScoreR.setFillColor(sf::Color::White);
    ScoreR.setPosition(1500, 100);

    GameOver.setFont(font);
    GameOver.setString("GAME OVER");
    GameOver.setCharacterSize(100);
    GameOver.setFillColor(sf::Color::Red);
    GameOver.setPosition(600, 100);

    Settings.setFont(font);
    Settings.setString("Save button: O\nLoad button: P\nPress L to get out of this menu\nPress U to get into main menu during the game\nYou can Save/Load games only during gameplay");
    Settings.setCharacterSize(60);
    Settings.setFillColor(sf::Color::White);
    Settings.setPosition(400, 200);

    OverText.setFont(font);
    OverText.setString("Press U to get to main menu");
    OverText.setCharacterSize(20);
    OverText.setFillColor(sf::Color::White);
    OverText.setPosition(600, 300);

}

int main() {
    
    GameSetUp();

    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong Game");
    
    while (window.isOpen()) {
        while (MenuPressed == false) {
            t0.setFillColor(sf::Color::Black);
            t1.setFillColor(sf::Color::Black);
            t2.setFillColor(sf::Color::Black);
            t3.setFillColor(sf::Color::Black);
            switch (menuHover) {
            case 0:
                t0.setFillColor(sf::Color::Red);
                break;
            case 1:
                t1.setFillColor(sf::Color::Red);
                break;
            case 2:
                t2.setFillColor(sf::Color::Red);
                break;
            case 3:
                t3.setFillColor(sf::Color::Red);
                break;
            }
            window.clear();
            window.draw(blackScreen);
            window.draw(n0);
            window.draw(n1);
            window.draw(n2);
            window.draw(n3);
            window.draw(t0);
            window.draw(t1);
            window.draw(t2);
            window.draw(t3);
            window.draw(MainTitle);
            window.draw(sub);
            window.display();
             MenuSelection();
             while (window.pollEvent(event)) {
                 if (event.type == sf::Event::KeyPressed) MenuSelection();
             }
        }
       switch (menuHover) {
       case 0:
           ball.setPosition(ballPos);
           AI();
           RwallPos = Rwall.getPosition();
           hitConditions();
           while (window.pollEvent(event)) {
               if (event.type == sf::Event::KeyPressed) {
                   player_move();
                   FileSave();
                   BackToMenu();
               }
               if (event.type == sf::Event::Closed) window.close();
           }
           GameEnding();
           while (gameEnded) {
               window.draw(blackScreen);
               while (window.pollEvent(event)) {
                   if (event.type == sf::Event::KeyPressed) {
                       BackToMenu();
                   }
               }
               window.draw(GameOver);
               window.draw(OverText);
               window.display();
           }
           getLwallCenter();
           ballMovement();
           UDmovement();
           window.clear();
           window.draw(Lwall);
           window.draw(Rwall);
           window.draw(ball);
           window.draw(middleWall);
           window.draw(ScoreL);
           window.draw(ScoreR);
           window.display();
           break;
       case 1:
           ball.setPosition(ballPos);
           RwallPos = Rwall.getPosition();
           hitConditions();
           while (window.pollEvent(event)) {
               if (event.type == sf::Event::KeyPressed) {
                   player_move();
                   P2_move();
                   BackToMenu();
                   FileSave();
               }
               if (event.type == sf::Event::Closed) window.close();
           }
           GameEnding();
           while (gameEnded) {
               window.draw(blackScreen);
               while (window.pollEvent(event)) {
                   if (event.type == sf::Event::KeyPressed) {
                       BackToMenu();
                   }
               }
               window.draw(GameOver);
               window.draw(OverText);
               window.display();
           }
           getLwallCenter();
           ballMovement();
           UDmovement();
           window.clear();
           window.draw(Lwall);
           window.draw(Rwall);
           window.draw(ball);
           window.draw(middleWall);
           window.draw(ScoreL);
           window.draw(ScoreR);
           window.display();
           break;
        case 2:
            while (MenuPressed == true) {
                while (window.pollEvent(event)) {
                      if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::L) {
                            MenuPressed = !MenuPressed;
                        }
                    }
                }
                window.clear();
                window.draw(Settings);
                window.display();
               
            }
            break;
        case 3:
            window.close();
            break;
        default:
            menuHover = 0;
            MenuPressed = false;
            break;
       }  
       
     }

    return 0;
}