#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>
using std::complex;

typedef complex<double> Komplex;



class Mandelbrot
{
    public:
        Mandelbrot(int xsize=200, int ysize=200, Komplex LowerLeft=Komplex(-2.0,-1.25), Komplex UpperRight=Komplex(0.5, 1.25));
        void calc(double Limit=100000, long MaxCycles=2048);
        long getCyclesDirect(const Komplex& where, double Limit=100000, long Maxcycles=2048) const;
        void paint();
        void calcinthread(int ThreadPhase);

    protected:

    private:
        int xsize;
        int ysize;
        double Limit;
        int numthreads;
        long MaxCycles;
        Komplex LowerLeft;
        Komplex UpperRight;
        long *IterValues;
        unsigned delayvalue;
};

#endif // MANDELBROT_H
