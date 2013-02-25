#include "simplex.h"
#include <cmath>

Simplex::Simplex()
{
}

void Simplex::sort()
{
    unsigned ar_size = m_array.size();   //sort
    for (unsigned j=0; j<ar_size-1; j++)
        for (unsigned i=0; i<ar_size-j; i++)
            if (func(m_array[i]) > func(m_array[i+1]))
                std::swap(m_array[i], m_array[i+1]);
    set_h(m_array[ar_size]);   //set h,g,l
    set_g(m_array[ar_size-1]);
    set_l(m_array[0]);
    Point c;     //calculate center of mass
    for (unsigned i=0; i<ar_size-1; i++)
        c += m_array[i];
    c /= ar_size-1;
    set_c(c);
}

double Simplex::distance(Point &a, Point &b)
{
    double result = 0;
    for (unsigned i=0; i<m_array.size(); i++)
    {
        result += (a.coord[i] - b.coord[i])*(a.coord[i] - b.coord[i]);
    }
    return sqrt(result);
}

bool Simplex::QuitCase(Simplex& s, double eps)
{
    if (distance(s.m_array[0],s.m_array[1])<eps)
        return true;
    else
        return false;
}

double Simplex::func(Point a)   //TODO: function generator
{
    return (a.coord[0] + a.coord[2]);
}

void Simplex::reflect()
{
    //TODO
}

//TODO: implement operators
unsigned Point::n;
Point Point::operator +=(Point& a)
{
    Point* b = new Point();
    for (unsigned i=0; i<n; i++)
        b->coord[i] = this->coord[i] + a.coord[i];
    return *b;
}

Point Point::operator /=(double d)
{
    Point* b = new Point();
    for (unsigned i=0; i<n; i++)
        b->coord[i] = this->coord[i]/d;
    return *b;
}

Point Point::operator +(Point& a, Point& b)
{
    Point* c = new Point();
    for (unsigned i=0; i<n; i++)
        c->coord[i] = a[i] + b[i];
    return *c;
}

Point Point::operator -(Point& a, Point& b)
{
    Point* c = new Point();
    for (unsigned i=0; i<n; i++)
        c->coord[i] = a[i] - b[i];
    return *c;
}

Point Point::operator *(Point& a, double d)
{
    Point* c = new Point();
    for (unsigned i=0; i<n; i++)
        c->coord[i] = a[i]*d;
    return *c;
}
