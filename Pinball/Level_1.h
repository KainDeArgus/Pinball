#pragma once
#include "Library.h"
#include "Function.h"
#include "constants.h"
#include "menu.h"
using namespace sf;

void menu(RenderWindow& window);

int Level_1(RenderWindow& window) {

    srand(time(NULL));

    const int l_plat = 160, h_plat = 22;
    const int Platform1PositionX = (width - l_plat) / 2, Platform1PositionY = height - 50;
    const int Platform2PositionX = (width - l_plat) / 2 + l_plat, Platform2PositionY = 50;
    int SpeedPlatform1 = 20;
    const int SpeedPlatform2 = 30;
    const int D_ball = 38;
    const int BallPositionX = (width - D_ball) / 2, BallPositionY = height / 2;
    const int count_frame_ball_stan = 30;
    const int lenght_ball_stan = 50;
    float BallSpeedX = 10, BallSpeedY = 6;
    number_platform_ball_stan = 1;
    int ChoosePlatform = 1;
    int time_cof = 100000;

    float dx1 = 10, dy1 = 6;
    StartMove(dx1, dy1);

    Texture time_stane, time_1, time_2, time_3, time_0, time_accelerate;

    time_stane.loadFromFile("Images/time.png");
    time_accelerate.loadFromFile("Images/Otime.png");
    time_1.loadFromFile("Images/1_time.png");
    time_2.loadFromFile("Images/2_time.png");
    time_3.loadFromFile("Images/3_time.png");
    time_0.loadFromFile("Images/0_time.png");

    Sprite sStaneTime(time_stane), sCountStaneTime(time_3), sCountAccelerateTime(time_3), sAccelerateTime(time_accelerate);

    sStaneTime.setPosition(0, height / 2 - 70);
    sCountStaneTime.setPosition(70, height / 2 - 70);
    sAccelerateTime.setPosition(width - 70 , height / 2 - 70);
    sCountAccelerateTime.setPosition(width - 140, height / 2 - 70);

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;
    t1.loadFromFile("Images/B_background.jpg");
    t8.loadFromFile("Images/Y_background.jpg");
    t2.loadFromFile("Images/ball.level1.png");
    t3.loadFromFile("Images/platform.level1.png");
    t4.loadFromFile("Images/GameOver.png");
    t5.loadFromFile("Images/G_background.jpg");
    t6.loadFromFile("Images/R_background.jpg");
    t7.loadFromFile("Images/win.png");
    t9.loadFromFile("Images/background1.jpg");
    t10.loadFromFile("Images/Blue_background.jpg");
    t11.loadFromFile("Images/O_background.jpg");

    Sprite sBackground(t9), sGameOver(t4), sBall1(t2), sPlatform_1(t3), sPlatform_2(t3), sWin(t7);

    sWin.setPosition((width - 650) / 2, (height - 600) / 2);
    sGameOver.setPosition((width - 542) / 2, (height - 60) / 2);

    sBall1.setPosition(BallPositionX, BallPositionY);

    sPlatform_1.setPosition(Platform1PositionX, Platform1PositionY);
    sPlatform_2.setPosition(Platform2PositionX, Platform2PositionY);
    sPlatform_2.setRotation(180);
    
    window.clear();

    window.draw(sBackground);
    window.draw(sStaneTime);
    window.draw(sCountStaneTime);
    window.draw(sAccelerateTime);
    window.draw(sCountAccelerateTime);
    window.draw(sBall1);
    window.draw(sPlatform_1);
    window.draw(sPlatform_2);

    window.display();

    cloc.restart();

    while (window.isOpen()) {

        if (count_stan_time == 1) {
            sCountStaneTime.setTexture(time_1);
        }
        if (count_stan_time == 2) {
            sCountStaneTime.setTexture(time_2);
        }
        if (count_stan_time == 0) {
            sCountStaneTime.setTexture(time_0);
        }
        if (count_accelerate_time == 1) {
            sCountAccelerateTime.setTexture(time_1);
        }
        if (count_accelerate_time == 2) {
            sCountAccelerateTime.setTexture(time_2);
        }
        if (count_accelerate_time == 0) {
            sCountAccelerateTime.setTexture(time_0);
        }

        float time = 1;

        if (FirstTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            FirstTime = 0;
        }
        else {
            float time = cloc.getElapsedTime().asMicroseconds();
            cloc.restart();
            time = time / time_cof;
        }
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
        if (dx1 != 0) {
            BallSpeedX = dx1;
            BallSpeedY = dy1;
        }
        //Движение шариков
        sBall1.move(dx1 * time, dy1 * time);

        Vector2f b1_cord = sBall1.getPosition();

        //Проверка на столкновение шарика 
        if (TouchSprites(sBall1, sPlatform_1)) {
            if (time_stan) { dx1 *= 3.5; dy1 *= 3.5; }
            if (time_acceleration) { SpeedPlatform1 /= 2.2; }
            if (time_stan || time_acceleration) { sBackground.setTexture(t5); }
            touch_was = true;
            dy1 = -dy1 - 0.5;
        }
        if (TouchSprites(sBall1, sPlatform_2)) {
            touch_was = false;
            dy1 = -dy1 + 0.5;
        }
        //Проверка на столкновение с границей карты мячиков
        if ((b1_cord.x < 0) || (b1_cord.x > width - D_ball)) { dx1 = -dx1; }
        if ((b1_cord.y < 0) || (b1_cord.y > height - D_ball)) {
            GameOver = true;
            if ((b1_cord.y < 0)) { win_you = true; }
        }
        //Game Over
        if (GameOver) {
            touch_was = false;
            time_acceleration = 0;
            time_stan = 0;
            ball_stan = 0;
            count_stan_time = 3;
            count_accelerate_time = 3;
            sBackground.setTexture(t1);
            window.clear();
            if (win_you) {
                sBackground.setTexture(t8);
            }
            else {
                sBackground.setTexture(t1);
            }
            window.draw(sBackground);
            if (win_you) {
                window.draw(sWin);
            }
            else {
                window.draw(sGameOver);
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            GameOver = win_you = false;
            FirstTime = 1;
            menu(window);
            return 0;
        }

        if (ball_stan) { frame_ball_stan++; }

        Vector2f p1_cord = sPlatform_1.getPosition();
        Vector2f p2_cord = sPlatform_2.getPosition();

        if (b1_cord.y >= height / 2) {
            if (!time_stan && !time_acceleration) {
                sBackground.setTexture(t5);
            }

            StanTime(dx1, dy1, sBackground, t10);
            AccelerateTime(SpeedPlatform1, sBackground, t11);

            //Обработка действий ПЕРВОЙ платформы
            StanBall(b1_cord, p1_cord, l_plat, dx1, dy1, lenght_ball_stan, ChoosePlatform);
            if (frame_ball_stan == count_frame_ball_stan) {
                frame_ball_stan = 0;
                ball_stan = false;
                dx1 = BallSpeedX;
                dy1 = BallSpeedY;
            }
            MovePlatform(ChoosePlatform, sPlatform_1, l_plat, SpeedPlatform1, time, sBall1, p1_cord);
        }
        else {
            if (ball_stan_was) { ball_stan_was = false; }
            if (!touch_was) {
                if (time_stan) {
                    dx1 *= 3.5;
                    dy1 *= 3.5;
                }
                if (time_acceleration) {
                    dx1 /= 3.5;
                    dy1 /= 3.5;
                }
            }
            if (!time_stan && !time_acceleration) {
                sBackground.setTexture(t6);
            }
            else {
                time_stan = false;
                time_acceleration = false;
            }

            //Обработка действий ВТОРОЙ платформы
            float x1 = dx1 * (Platform2PositionY - b1_cord.y) / dy1 + b1_cord.x;

            if (x1 < 0) { x1 = -x1; }
            if (x1 > width) { x1 = 2 * width - x1; }

            Move2Platform(p2_cord, l_plat, x1, SpeedPlatform2, sPlatform_2, time);
        }

        window.clear();

        window.draw(sBackground);
        window.draw(sAccelerateTime);
        window.draw(sCountAccelerateTime);
        window.draw(sBall1);
        window.draw(sStaneTime);
        window.draw(sCountStaneTime);
        window.draw(sPlatform_1);
        window.draw(sPlatform_2);

        window.display();
    }
    return 0;
}