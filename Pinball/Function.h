#pragma once
#include "Library.h"
using namespace sf;

//Функция проверки столкновений объектов
bool TouchSprites(Sprite ball, Sprite platform) {
    return ball.getGlobalBounds().intersects(platform.getGlobalBounds());
}


//Функция которая рандомно выбирает куда в начальный момент времени полетит мяч
void StartMove(float& dx, float& dy) {
    float px = rand() % 10 / 10 + 0.1;
    float py = rand() % 10 / 10 + 0.1;
    dx += px; dy += py;
    int move = rand() % 2;
    switch (move)
    {
    case 1:
        dx = -dx;
        break;
    }
    move = rand() % 2;
    switch (move)
    {
    case 1:
        dy = -dy;
        break;
    }
}

//Функция которая меняет текстуры двух спрайтов
void SwapSpritesTexture(Sprite& one, Sprite& two) {
    const Texture *t1  = one.getTexture();
    const Texture *t2 = two.getTexture();
    one.setTexture(*t2);
    two.setTexture(*t1);
}

//Функция движения
void MovePlatform(int& ChoosePlatform, Sprite& sPlatform_1, int l_plat, int SpeedPlatform1, float& time, Sprite& sBall1, Vector2f& p1_cord) {

    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
        if (!ball_stan) {
            if (p1_cord.x + SpeedPlatform1 * time <= width - l_plat) { sPlatform_1.move(SpeedPlatform1 * time, 0); }
            else { sPlatform_1.move(width - p1_cord.x - l_plat, 0); }
        }
        else {
            if (number_platform_ball_stan != ChoosePlatform) {
                if (p1_cord.x + SpeedPlatform1 * time <= width - l_plat) { sPlatform_1.move(SpeedPlatform1 * time, 0); }
                else { sPlatform_1.move(width - p1_cord.x - l_plat, 0); }
            }
            else {
                if (p1_cord.x + SpeedPlatform1 * time <= width - l_plat) { sPlatform_1.move(SpeedPlatform1 * time, 0); sBall1.move(SpeedPlatform1 * time, 0); }
                else { sPlatform_1.move(width - p1_cord.x - l_plat, 0); sBall1.move(width - p1_cord.x - l_plat, 0); }
            }
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
        if (!ball_stan) {
            if (p1_cord.x - SpeedPlatform1 * time >= 0) { sPlatform_1.move(-SpeedPlatform1 * time, 0); }
            else { sPlatform_1.move(-p1_cord.x, 0); }
        }
        else {
            if (number_platform_ball_stan != ChoosePlatform) {
                if (p1_cord.x - SpeedPlatform1 * time >= 0) { sPlatform_1.move(-SpeedPlatform1 * time, 0); }
                else { sPlatform_1.move(-p1_cord.x, 0); }
            }
            else {
                if (p1_cord.x - SpeedPlatform1 * time >= 0) { sPlatform_1.move(-SpeedPlatform1 * time, 0); sBall1.move(-SpeedPlatform1 * time, 0); }
                else { sPlatform_1.move(-p1_cord.x, 0);  sBall1.move(-p1_cord.x, 0); }
            }
        }
    }
}

void Move2Platform(Vector2f& p2_cord, int l_plat, float& x2, int SpeedPlatform2, Sprite& sPlatform_2, float& time) {
    int tale_p2 = p2_cord.x;
    int beg_p2 = tale_p2 - l_plat;
    if (beg_p2 > x2) {
        if (beg_p2 - SpeedPlatform2 * time >= 0) {
            if (beg_p2 - SpeedPlatform2 < x2) {
                sPlatform_2.move((x2 - beg_p2 - l_plat) * time / 2, 0);
            }
            else {

                sPlatform_2.move(-SpeedPlatform2 * time, 0);
            }
        }
        else {
            sPlatform_2.move(-beg_p2, 0);
        }

    }
    if (tale_p2 < x2) {
        if (tale_p2 + SpeedPlatform2 * time <= width - l_plat) {
            if (tale_p2 + SpeedPlatform2 > x2) {
                sPlatform_2.move((x2 - tale_p2 + l_plat) * time / 2, 0);
            }
            else {
                sPlatform_2.move(SpeedPlatform2 * time, 0);
            }
        }
        else {
            sPlatform_2.move(width - tale_p2, 0);
        }
    }
}

//Функция стана шарика
void StanBall(Vector2f& b1_cord, Vector2f& p3_cord, int l_plat, float& dx1, float& dy1, int lenght_ball_stan,int& ChoosePlatform) {
    if (!ball_stan && !time_stan && !time_acceleration) {
        if ((Keyboard::isKeyPressed(Keyboard::LShift)) || (Keyboard::isKeyPressed(Keyboard::RShift))) {
            if ((b1_cord.x >= p3_cord.x) && (b1_cord.x <= p3_cord.x + l_plat) && (b1_cord.y + lenght_ball_stan >= p3_cord.y) && !ball_stan && (dy1 >= 0)) {
                ball_stan = true;
                ball_stan_was = true;
                number_platform_ball_stan = ChoosePlatform;
                dx1 = dy1 = 0;
            }
        }
    }
}

//Функция стана времени
void StanTime(float& dx1, float& dy1, Sprite& sBackground, Texture& t) {
    if (!time_stan && !time_acceleration && !ball_stan_was) {
        if (count_stan_time != 0) {
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                touch_was = false;
                time_stan = true;
                dx1 /= 3;
                dy1 /= 3;
                sBackground.setTexture(t);
                count_stan_time--;
            }
        }
    }
}

//Функция ускорения времени
void AccelerateTime(int& SpeedPlatform1, Sprite& sBackground, Texture& t) {
    if (!time_acceleration && !time_stan && !ball_stan_was) {
        if (count_accelerate_time != 0) {
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                touch_was = false;
                time_acceleration = true;
                SpeedPlatform1 *= 2;
                sBackground.setTexture(t);
                count_accelerate_time--;
            }
        }
    }
}