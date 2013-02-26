#include "simplex.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <QDebug>
Simplex::Simplex()
{
}

Simplex::Simplex(const std::vector<Point> &vertex)
{
    this->m_array = vertex;
}

Simplex::Simplex(Point a, double t)
{
    const unsigned N_DIM = Point::n;
    double d1, d2;
    d1 = t * (sqrt(N_DIM + 1) + N_DIM - 1) / (N_DIM * sqrt(N_DIM));
    d2 = t * (sqrt(N_DIM + 1) - 1) / (N_DIM * sqrt(N_DIM));
    qDebug()<<a.coord[0];
    m_array.push_back(a);
    for (unsigned i=1; i<N_DIM + 1; i++)
    {
        Point b;
        for (unsigned k=0; k<N_DIM; k++)
        {
            if (i - 1 == k)
                b.coord[k] = d1 + a.coord[k];
            else
                b.coord[k] = d2 + a.coord[k];
        }
        m_array.push_back(b);
    }
}

//namespace {
//bool comparator_by_f(const Point&a, const Point& b)
//{
//    return func(a) < func(b);
//}
//}
void Simplex::sort()
{
    unsigned ar_size = m_array.size();   //sort
    for (unsigned j=0; j<ar_size-1; j++)
        for (unsigned i=0; i<ar_size-1; i++)
            if (func(m_array[i]) > func(m_array[i+1]))
                std::swap(m_array[i], m_array[i+1]);
    set_h(m_array[ar_size-1]);   //set h,g,l
    set_g(m_array[ar_size-2]);
    set_l(m_array[0]);
    Point c;     //calculate center of mass
    for (unsigned i=0; i<ar_size-1; i++)
        c += m_array[i];
//    c = std::accumulate(m_array.begin(), m_array.end() - 1, 0) /(ar_size - 1);
    c /= ar_size-1;
    set_c(c);

//    std::sort(m_array.begin(), m_array.end(), comparator_by_f);
}

double Simplex::distance(Point a, Point b)
{
    double result = 0.0;
    for (unsigned i=0; i<m_array.size(); i++)
    {
        result += (a.coord[i] - b.coord[i])*(a.coord[i] - b.coord[i]);
    }
    return sqrt(result);
}

bool Simplex::QuitCase(Simplex& s, double eps)
{
    for (unsigned i=0; i<s.m_array.size(); i++)
        for (unsigned j=0; j<s.m_array.size(); j++)
            if (i!=j && distance(s.get_vertex(i), s.get_vertex(j))>eps)
                    return false;
    return true;
}

bool Simplex::point_satisfies_restriction(const Point &a)
{
    double d;

    return true;
}

double Simplex::func(Point a)   //TODO: function generator
{
    const unsigned N_DIM = Point::n;
    return (1 + pow(a.coord[0], 2.0) + pow(a.coord[1],2.0));
}

unsigned Point::n;

Point::Point()
{
    coord = std::vector<double>(n);
}

const Point operator+(Point& a, Point& b) //TODO: add operators
{
    return a + b;
}

const Point Point::operator +(const Point& a) const
{
    Point b;
    for (unsigned i=0; i<n; i++)
        b.coord[i] = this->coord[i] + a.coord[i];
    return b;
}

Point& Point::operator+=(const Point& b)
{
    *this = *this + b;
    return *this;
}

Point& Point::operator/=(const double b)
{
    *this = *this / b;
    return *this;
}

const Point operator /(Point &a, double d)
{
    return a / d;
}

const Point Point::operator /(const double d) const
{
    Point b;
    for (unsigned i=0; i<n; i++)
        b.coord[i] = this->coord[i]/d;
    return b;
}

const Point operator -(Point& a, Point& b)
{
    return a - b;
}

const Point Point::operator -(const Point& a) const
{
    Point c;
    for (unsigned i=0; i<n; i++)
        c.coord[i] = this->coord[i] - a.coord[i];
    return c;
}

const Point operator *(Point &a, double d)
{
    return a * d;
}

const Point Point::operator *(double d) const
{
    Point c;
    for (unsigned i=0; i<n; i++)
        c.coord[i] = this->coord[i]*d;
    return c;
}

