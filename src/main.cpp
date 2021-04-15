#include "PixelRay.h"
#include <iostream>
#include <vector>

//#define M_PI           3.14159265358979323846
//float it = 0;
class Vector
{
public:
    float x;
    float y;

    void addVector(Vector v)
    {
        x += v.x;
        y += v.y;
    }
};

class Boid
{
public:
    Vector position;
    Vector velocity;

    void Update()
    {
        position.addVector(velocity);
    }
};

std::vector<Boid> flock;

int init()
{
    Boid b;
    b.position.x = 0;
    b.position.y = 0;
    b.velocity.x = 0.1f;
    b.velocity.y = 0.1f;

    flock.push_back(b);

	return 1;
}

void Edges(Boid& b)
{
    if (b.position.x > 320) b.position.x = 0;
    else if (b.position.x < 0) b.position.x = 320;
    if (b.position.y > 200) b.position.y = 0;
    else if (b.position.y < 0) b.position.y = 200;
}

void step()
{
	canvas_clear(0);

    flock[0].Update();

    Edges(flock[0]);
    pixel_draw(flock[0].position.x, flock[0].position.y, 3);

/*    for (int i = 0; i < 300; i++)
    {
        float dst = (i / (300 - 1.0f)) * 90;
        float angle = 2 * M_PI * it * i;

        float x = dst * std::cos(angle);
        float y = dst * std::sin(angle);

        pixel_draw(x + 150, y + 100, 3);
    }

    it = it + 0.00001;*/
}