#ifndef OCTREE_H
#define OCTREE_H

#include "point.h"
#include <vector>

class Octree {
private:
    // Octree *children[8] = {nullptr};
    // Point *points;
    // std::vector<Point *> points;

    // bottomLeft y h definen el espacio(cubo más grande)
    Point bottomLeft;
    double h;
    int N;

public:
    Octree *children[8] = {nullptr};
    std::vector<Point *> points;
    int nPoints; // puntos ingresados.
    Octree( const Point& _bottomLeft, double _h, int N);
    bool exist(const Point &);
    bool insert(const Point &);
    Point find_closest(const Point &, int radio);

    int getOctantIndex(const Point& p) const;
    Point getBottomLeftPoint(int pos);
    bool verifyPointBounds(const Point &p);
    Point getBottomLeft() const;
    double getH() const;
};

#endif
