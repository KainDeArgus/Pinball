#pragma once
#include "Library.h"
#include "Function.h"
#include "constants.h"
#include "menu.h"
using namespace sf;

void menu(RenderWindow& window);

int Level_2(RenderWindow& window) {

    srand(time(NULL));

    const int l_plat = 88, h_plat = 22;
    const int Platform1PositionX = (width - l_plat) / 2, Platform1PositionY = height - 50;
    const int Platform2PositionX = (width - l_plat) / 2 + l_plat, Platform2PositionY = 50;
    int SpeedPlatform1 = 20;
    const int SpeedPlatform2 = 30;
    const int D_ball = 25;
    const int BallPositionX = (width - D_ball) / 2, BallPositionY = height / 2;
    const int count_frame_ball_stan = 20;
    const int lenght_ball_stan = 35;
    float BallSpeedX = 10, BallSpeedY = 6;

    int ChoosePlatform = 1;

    float dx1 = 10, dy1 = 6;
    StartMove(dx1, dy1);

    Texture time, time_1, time_2, time_3, time_0, time_accelerate;

    time.loadFromFile("Images/time.png");
    time_accelerate.loadFromFile("Images/Otime.png");
    time_1.loadFromFile("Images/1_time.png");
    time_2.loadFromFile("Images/2_time.png");
    time_3.loadFromFile("Images/3_time.png");
    time_0.loadFromFile("Images/0_time.png");

    Sprite sStaneTime(time), sCountStaneTime(time_3), sCountAccelerateTime(time_3), sAccelerateTime(time_accelerate);

    sStaneTime.setPosition(0, height / 2 - 70);
    sCountStaneTime.setPosition(70, height / 2 - 70);
    sAccelerateTime.setPosition(width - 70 , height / 2 - 70);
    sCountAccelerateTime.setPosition(width - 140, height / 2 - 70);

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;
    t1.loadFromFile("Images/B_background.jpg");
    t2.loadFromFile("Images/ball.png");
    t3.loadFromFile("Images/platform.png");
    t4.loadFromFile("Images/GameOver.png");
    t5.loadFromFile("Images/nonactive_platform.png");
    t6.loadFromFile("Images/active_platform.png");
    t7.loadFromFile("Images/G_background.jpg");
    t8.loadFromFile("Images/R_background.jpg");
    t9.loadFromFile("Images/Y_background.jpg");
    t10.loadFromFile("Images/win.png");
    t11.loadFromFile("Images/background1.jpg");
    t12.loadFromFile("Images/Blue_background.jpg");
    t13.loadFromFile("Images/O_background.jpg");

    Sprite sBackground(t11), sGameOver(t4), sBall1(t2), sPlatform_1(t6), sPlatform_2(t3), sPlatform_3(t5), sPlatform_4(t3), sWin(t10);

    sWin.setPosition((width - 650) / 2, (height - 600) / 2);
    sGameOver.setPosition((width - 542) / 2, (height - 60) / 2);

    sBall1.setPosition(BallPositionX, BallPositionY);

    sPlatform_1.setPosition(Platform1PositionX, Platform1PositionY);
    sPlatform_2.setPosition(Platform2PositionX, Platform2PositionY);
    sPlatform_2.setRotation(180);

    sPlatform_3.setPosition(Platform1PositionX, Platform1PositionY - h_plat - 5);
    sPlatform_4.setPosition(Platform2PositionX, Platform2PositionY + h_plat + 5);
    sPlatform_4.setRotation(180);

    window.clear();

    window.draw(sBackground);
    window.draw(sStaneTime);
    window.draw(sCountStaneTime);
    window.draw(sAccelerateTime);
    window.draw(sCountAccelerateTime);
    window.draw(sBall1);
    window.draw(sPlatform_1);
    window.draw(sPlatform_2);
    window.draw(sPlatform_3);
    window.draw(sPlatform_4);

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
            time = time / 100000;
        }
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
        //Движение шариков
        if (dx1 != 0) {
            BallSpeedX = dx1;
            BallSpeedY = dy1;
        }
        sBall1.move(dx1 * time, dy1 * time);

        Vector2f b1_cord = sBall1.getPosition();

        //Проверка на столкновение шарика 1
        if (TouchSprites(sBall1, sPlatform_1)) {
            if (time_stan) { dx1 *= 3.5; dy1 *= 3.5; }
            if (time_acceleration) { SpeedPlatform1 /= 2.2; }
            if (time_stan || time_acceleration) { sBackground.setTexture(t7); }
            touch_was = true;
            dy1 = -dy1 - 0.5;
        }
        if (TouchSprites(sBall1, sPlatform_2)) {
            dy1 = -dy1 + 0.5;
        }
        if (TouchSprites(sBall1, sPlatform_3)) {
            if (time_stan) { dx1 *= 3.5; dy1 *= 3.5; }
            if (time_acceleration) { SpeedPlatform1 /= 2.2; }
            if (time_stan || time_acceleration) { sBackground.setTexture(t7); }
            touch_was = true;
            dy1 = -dy1 - 0.5;
        }
        if (TouchSprites(sBall1, sPlatform_4)) {
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
                sBackground.setTexture(t9);
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
        Vector2f p3_cord = sPlatform_3.getPosition();

        if (b1_cord.y >= height / 2) {

            if (!time_stan && !time_acceleration) {
                sBackground.setTexture(t7);
            }

            StanTime(dx1, dy1, sBackground, t12);
            AccelerateTime(SpeedPlatform1, sBackground, t13);

            //Обработка действий ПЕРВОЙ платформы
            if (ChoosePlatform == 1) {
                if (Keyboard::isKeyPressed(Keyboard::Num2)) { ChoosePlatform = 3; SwapSpritesTexture(sPlatform_1, sPlatform_3); }
                else {
                    //Стан шарика
                    StanBall(b1_cord, p1_cord, l_plat, dx1, dy1, lenght_ball_stan, ChoosePlatform);
                    if (frame_ball_stan == count_frame_ball_stan) {
                        frame_ball_stan = 0;
                        ball_stan = false;
                        dx1 = BallSpeedX;
                        dy1 = BallSpeedY;
                    }

                    MovePlatform(ChoosePlatform, sPlatform_1, l_plat, SpeedPlatform1, time, sBall1, p1_cord);
                }
            }
            //Обработка действий ТРЕТЬЕЙ платформы
            if (ChoosePlatform == 3) {
                if (Keyboard::isKeyPressed(Keyboard::Num1)) { ChoosePlatform = 1; SwapSpritesTexture(sPlatform_1, sPlatform_3); }
                else {
                    //Стан шарика
                    StanBall(b1_cord, p3_cord, l_plat, dx1, dy1, lenght_ball_stan, ChoosePlatform);
                    if (frame_ball_stan == count_frame_ball_stan) {
                        frame_ball_stan = 0;
                        ball_stan = false;
                        dx1 = BallSpeedX;
                        dy1 = BallSpeedY;
                    }

                    MovePlatform(ChoosePlatform, sPlatform_3, l_plat, SpeedPlatform1, time, sBall1, p3_cord);
                }
            }
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
                sBackground.setTexture(t8);
            }
            else {
                time_stan = false;
                time_acceleration = false;
            }

            //Обработка действий ВТОРОЙ платформы
            float x2 = dx1 * (Platform2PositionY - b1_cord.y) / dy1 + b1_cord.x;
            float x4 = dx1 * (Platform2PositionY + h_plat + 5 - b1_cord.y) / dy1 + b1_cord.x;

            if (x2 < 0) { x2 = -x2; }
            if (x2 > width) { x2 = 2 * width - x2; }
            if (x4 < 0) { x4 = -x4; }
            if (x4 > width) { x4 = 2 * width - x4; }

            Vector2f p2_cord = sPlatform_2.getPosition();
            Vector2f p4_cord = sPlatform_4.getPosition();

            if (abs(p2_cord.x - x2) < abs(p4_cord.x - x4)) {
                Move2Platform(p2_cord, l_plat, x2, SpeedPlatform2, sPlatform_2, time);
            }
            else {
                //Обработка действий ЧЕТВЁРТОЙ платформы
                Move2Platform(p4_cord, l_plat, x4, SpeedPlatform2, sPlatform_4, time);
            }
        }

        window.clear();

        window.draw(sBackground);
        window.draw(sAccelerateTime);
        window.draw(sCountAccelerateTime);
        window.draw(sStaneTime);
        window.draw(sCountStaneTime);
        window.draw(sBall1);
        window.draw(sPlatform_1);
        window.draw(sPlatform_2);
        window.draw(sPlatform_3);
        window.draw(sPlatform_4);

        window.display();
    }
    return 0;
}