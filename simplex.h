#pragma once

#include <vector>
//typedef Point std::vector<double>;


class Point
{
public:
    static unsigned n;
    std::vector<double> coord;
    Point operator+= (Point& a);
    Point operator/= (double d);
    Point operator+ (Point& a);
    Point operator- (Point& a);
    Point operator* (double d);
    double operator[] (unsigned i) {return coord[i];}
};



class Simplex
{
public:
    Simplex();
    Simplex(const std::vector<Point> &coord);
    double func(Point);
    void reduction();
    void reflect();
    Point& get_reflected() {return reflected;}
    Point& get_c() {return p_c;}
    Point& get_l() {return p_l;}
    Point& get_g() {return p_g;}
    Point& get_h() {return p_h;}
    void set_reflected(Point a) {reflected = a;}
    void set_c(Point c) {p_c = c;}
    void set_l(Point l) {p_l = l;}
    void set_g(Point g) {p_g = g;}
    void set_h(Point h) {p_h = h;}
    bool QuitCase(Simplex& simplex, double eps);
    void sort();
    Point get_vertex(unsigned i) {return m_array[i];}
    void set_vertex_h(Point new_h) {m_array[m_array.size()] = new_h;}
private:
    double distance(Point a, Point b);
    std::vector<Point> m_array;
    Point reflected;
    Point p_c, p_l, p_g, p_h; //h - point at which function has the biggesst value; g - -||- second biggest value; l - -||- lowest value
};
