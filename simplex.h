#pragma once

#include <vector>


class Point
{
    unsigned M; //S2 - method
public:
    bool inc_M(unsigned M_max); //increments M, returns true if M <= M_max
    const unsigned get_M() {return M;}
    void set_M(unsigned new_M) {M = new_M;}
    Point();
    static unsigned n;
    std::vector<double> coord;
    const Point operator+ (const Point& a) const;
    const Point operator/ (const double d) const;
//    Point operator+ (Point& a);
    const Point operator- (const Point& a) const;
    const Point operator* (double d) const;
    double operator[] (unsigned i) {return coord[i];}
    Point& operator+=(const Point& b);
    Point& operator/=(const double b);
};



class Simplex
{
public:
    Simplex();
    Simplex(Point a, double t);
    Simplex(const std::vector<Point> &vertex);
    void reduction();
    void reflect();
    Point& get_reflected() {return reflected;}
    const Point& get_c() {return p_c;}
    const Point& get_l() {return p_l;}
    const Point& get_g() {return p_g;}
    const Point& get_h() {return p_h;}
    void set_reflected(Point a) {reflected = a;}
    void set_c(Point c) {p_c = c;}
    void set_l(Point l) {p_l = l;}
    void set_g(Point g) {p_g = g;}
    void set_h(Point h) {p_h = h;}
    bool QuitCase(Simplex& simplex, double eps);
    void set_vertex(Point a, unsigned i) {m_array[i] = a;}
    const Point get_vertex(unsigned i) {return m_array[i];}
    const unsigned get_number_of_vertexes() {return m_array.size();}
    void set_vertex_h(Point new_h) {new_h.set_M(0); m_array[m_array.size() - 1] = new_h;}
    bool inc_allvertex_M(unsigned M_max); //true if reduction is needed
    std::vector<Point> m_array;
private:
    double distance(Point a, Point b);
    Point reflected;
    Point p_c, p_l, p_g, p_h; //h - point at which function has the biggesst value; g - -||- second biggest value; l - -||- lowest value
};
