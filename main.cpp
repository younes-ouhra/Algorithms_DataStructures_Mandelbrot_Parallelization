#include <iostream>
#include "WinAdapt.h"
#include "Mandelbrot.h"
#include <time.h>

using namespace std;

//Mandelbrot mab(800, 800);
Mandelbrot mab(1000, 1000, Komplex(-0.74877, 0.065053), Komplex(-0.74872, 0.065103));

void VtlZyk(void)
{

}

void VtlMouse(__attribute__((unused))int X, __attribute__((unused))int Y)
{

}

void VtlKeyHit(__attribute__((unused))int key)
{

}

void VtlInit(void)
{
    mab.calc(100000,2048);
}

void VtlPaint(__attribute__((unused))int xl, __attribute__((unused))int yo, __attribute__((unused))int xr, __attribute__((unused))int yu)
{
    mab.paint();
}
