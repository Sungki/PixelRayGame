#include "PixelRay.h"
#include <iostream>
#include <thread>
#include <chrono>

#define M_PI           3.14159265358979323846

float it = 0;

int init()
{
	return 1;
}

void step()
{
	canvas_clear(1);

    for (int i = 0; i < 300; i++)
    {
        float dst = (i / (300 - 1.0f)) * 90;
        float angle = 2 * M_PI * it * i;

        float x = dst * std::cos(angle);
        float y = dst * std::sin(angle);

        pixel_draw(x + 150, y + 100, 3);
    }

    it = it + 0.00001;

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}