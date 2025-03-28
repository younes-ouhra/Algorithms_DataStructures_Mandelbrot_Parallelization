#include "WinAdapt.h"
#include "Mandelbrot.h"
#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <ctime>



#define PARALLEL
#include <omp.h>

Mandelbrot::Mandelbrot(int xsize, int ysize, Komplex LowerLeft, Komplex UpperRight)
:xsize(xsize), ysize(ysize), Limit(0), numthreads(16), MaxCycles(1000), LowerLeft(LowerLeft), UpperRight(UpperRight), delayvalue(5)
{
    IterValues = new long[xsize*ysize];
    for (int y=0; y<ysize; y++)
    {
        for (int x=0; x<xsize; x++)         {IterValues[x*ysize+y]=2048;}
    }
}

long Mandelbrot::getCyclesDirect(const Komplex& where, double Limit, long Maxcycles) const
{
    long Cyclecounter=0;
    Komplex IterateValue(0.0, 0.0);

    while (abs(IterateValue)<abs(Komplex(Limit,0.0)) && Cyclecounter<Maxcycles) //Komplex(Limit,0.0))
    {
        IterateValue = pow(IterateValue, 2) + where;
        Cyclecounter++;
    }
    return Cyclecounter;
}

/*
//1.7
void Mandelbrot::calc(double Limit, long MaxCycles)
{
    Mandelbrot::MaxCycles=MaxCycles;
    Mandelbrot::Limit=Limit;

    double xscale=(UpperRight.real()-LowerLeft.real())/xsize;
    double yscale=(UpperRight.imag()-LowerLeft.imag())/ysize;

    double time1=0.0, tstart;
    tstart = clock();              // start

    for (int y=0; y<ysize; y++)
    {
        for (int x=0; x<xsize; x++)
        {
            IterValues[x*ysize+y] = getCyclesDirect(LowerLeft+Komplex(x*xscale, y*yscale), Limit, MaxCycles);
            //to keep even the lightning fast machines busy for a while:
            //std::this_thread::sleep_for(std::chrono::microseconds(delayvalue));
        }
    }

    time1 = clock() - tstart;     // end
    time1 = time1/CLOCKS_PER_SEC;

    std::cout << "Die Ausfuehrung der Funktion-calc dauerte " << time1 << " sec." << std::endl;
}
*/


/*
//1.7.1. Vorbereitung der Parallelisierung
void Mandelbrot::calc(double Limit, long MaxCycles)
{
    Mandelbrot::MaxCycles=MaxCycles;
    Mandelbrot::Limit=Limit;
    Mandelbrot::numthreads = ysize;

    double time1=0.0, tstart;
    tstart = clock();              // start 

    #pragma omp parallel for
    for (int j = 0; j < numthreads; j++)
    {
        calcinthread(j);
        //to keep even the lightning fast machines busy for a while:
        //std::this_thread::sleep_for(std::chrono::microseconds(delayvalue));
    }

    time1 = clock() - tstart;     // end
    time1 = time1/CLOCKS_PER_SEC;

    std::cout << "Die parallele Ausfuehrung mit der Funktion calcinthread dauerte " << time1 << " sec." << std::endl;
}
*/


///*
//1.7.2. Parallele Threads
void Mandelbrot::calc(double Limit, long MaxCycles)
{
    Mandelbrot::MaxCycles=MaxCycles;
    Mandelbrot::Limit=Limit;
    Mandelbrot::numthreads = ysize;

    double time1=0.0, tstart;
    tstart = clock();              // start

    
   	#pragma omp parallel for
	for (int j = 0; j < numthreads; j++)
    {
        std::thread* obj = new std::thread(&calcinthread, this, j);
        obj->join();
        delete obj;
        //to keep even the lightning fast machines busy for a while:
        //std::this_thread::sleep_for(std::chrono::microseconds(delayvalue));
    }

    time1 = clock() - tstart;     // end
    time1 = time1/CLOCKS_PER_SEC;

    std::cout << "Die parallele Ausfuehrung mit Objekt der Klasse thread dauerte " << time1 << " sec." << std::endl;
}
//*/

void Mandelbrot::calcinthread(int ThreadPhase)
{
    double xscale = (UpperRight.real() - LowerLeft.real()) / xsize;
    double yscale = (UpperRight.imag() - LowerLeft.imag()) / ysize;

    for (int i = 0; i < xsize; i++)
        {IterValues[(i * numthreads) + ThreadPhase] = getCyclesDirect(LowerLeft+Komplex(i * xscale, ThreadPhase * yscale), Limit, MaxCycles);}
}

void Mandelbrot::paint()
{
    for (int y=0; y<ysize; y++)
    {
        for (int x=0; x<xsize; x++)
        {
            if (IterValues[x*ysize+y] == MaxCycles)
            {
            PutPixel(x, ysize-y, RGB(0,0,0));
            }
            else
            {
            PutPixel(x, ysize-y, RGB(255-char(IterValues[x*ysize+y]*256/MaxCycles/2)-50,
                        255-char(IterValues[x*ysize+y]*256/MaxCycles),
                        255-char(IterValues[x*ysize+y]*256/MaxCycles/2)-50)
                        );
            }
        }
    }
}