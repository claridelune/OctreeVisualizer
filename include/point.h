#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;
    double z;

    Point(double a, double b, double c) : x(a), y(b), z(c) {}
    Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}

    Point operator+(const Point& p) {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    Point operator-(const Point& p) {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    Point operator*(const Point& p) {
        return Point(x * p.x, y * p.y, z * p.z);
    }
    Point operator/(const Point& p) {
        return Point(x / p.x, y / p.y, z / p.z);
    }
    bool operator<(const Point& p) {
        return x < p.x && y < p.y && z < p.z;
    }
    bool operator>(const Point& p) {
        return x > p.x && y > p.y && z > p.z;
    }
    bool operator<=(const Point& p) {
        return x <= p.x && y <= p.y && z <= p.z;
    }
    bool operator>=(const Point& p) {
        return x >= p.x && y >= p.y && z >= p.z;
    }
    bool operator==(const Point& p) {
        return x == p.x && y == p.y && z == p.z;
    }
    bool operator!=(const Point& p) {
        return x != p.x || y != p.y || z != p.z;
    }
};

#endif
