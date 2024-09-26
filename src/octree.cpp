#include "octree.h"
#include <cmath>
#include <csignal>
#include <tuple>
#include <queue>
#include <algorithm>

Octree::Octree( const Point& _bottomLeft, double _h, int _N ) : bottomLeft(_bottomLeft), h(_h) , N(_N){
    points.clear();
  // points = nullptr;
    nPoints = 0;
    for (int i = 0; i < 8; ++i) {
        children[i] = nullptr;
    }
}

Point Octree::getBottomLeft() const { return bottomLeft; }
double Octree::getH() const { return h; }

int Octree::getOctantIndex(const Point &p) const {
    int index = 0;
    if (p.x >= bottomLeft.x + h / 2) { index |= 1; }
    if (p.y >= bottomLeft.y + h / 2) { index |= 2; }
    if (p.z >= bottomLeft.z + h / 2) { index |= 4; }
    return index;
}

Point Octree::getBottomLeftPoint(int pos) {
    Point newBL = bottomLeft;
    if (pos & 1) newBL.x += h/2;
    if (pos & 2) newBL.y += h/2;
    if (pos & 4) newBL.z += h/2;
    return newBL;
}

bool Octree::exist(const Point &p) {
    if (!verifyPointBounds(p)) return false;

    Octree* node = this;
    int octant = getOctantIndex(p);

    while (node->children[octant]) {
        node = node->children[octant];
        octant = node->getOctantIndex(p);
    }
    for (auto v : node->points) {
        if (*v == p) {
            return true;
        }
    }
    return false;
}

bool Octree::verifyPointBounds(const Point &p) {
    return (p.x >= bottomLeft.x && p.x <= bottomLeft.x + h &&
            p.y >= bottomLeft.y && p.y <= bottomLeft.y + h &&
            p.z >= bottomLeft.z && p.z <= bottomLeft.z + h);
}

bool Octree::insert(const Point &p) {
    if (!verifyPointBounds(p)) return false;

    if (nPoints < N) {
        for (auto v : points) {
            if (*v == p) {
                return false;
            }
        }
        points.push_back(new Point(p));
        nPoints++;
        return true;
    }

    if (nPoints == N) {
        for (auto& v: points) {
            int pos1 = getOctantIndex(*v);
            if (!children[pos1]) {
                Point newBL = getBottomLeftPoint(pos1);
                children[pos1] = new Octree(newBL, h / 2, N);
            }

            children[pos1]->insert(*v);
        }
        points.clear();
        int pos2 = getOctantIndex(p);
        if (!children[pos2]) {
            Point newBL = getBottomLeftPoint(pos2);
            children[pos2] = new Octree(newBL, h / 2, N);
        }
        nPoints++;
        return children[pos2]->insert(p);
    }

    int pos = getOctantIndex(p);
    if (!children[pos]) {
        Point newBL = getBottomLeftPoint(pos);
        children[pos] = new Octree(newBL, h / 2, N);
    }
    bool inserted = children[pos]->insert(p);

    if (inserted) nPoints++;
    return inserted;
}

inline int calculateDistance(const Point &a, const Point &b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

int minDistanceToOctant(const Point& p, const Point& bottomLeft, double height) {
    int closestX = std::clamp(p.x, bottomLeft.x, bottomLeft.x + height);
    int closestY = std::clamp(p.y, bottomLeft.y, bottomLeft.y + height);
    int closestZ = std::clamp(p.z, bottomLeft.z, bottomLeft.z + height);
    Point closestPoint(closestX, closestY, closestZ);
    return calculateDistance(p, closestPoint);
}


using QueueNode = std::tuple<int, const Octree*, bool, Point>;

struct CompareQueueNode {
    bool operator()(const QueueNode& lhs, const QueueNode& rhs) const {
        return std::get<0>(lhs) > std::get<0>(rhs); // Comparar por el primer elemento del tuple (distancia)
    }
};

Point Octree::find_closest(const Point&p, int radio) {
    if (nPoints == 0) {
        return Point(0, 0, 0);
    }

    std::priority_queue<QueueNode, std::vector<QueueNode>, CompareQueueNode> pq;

    pq.emplace(minDistanceToOctant(p, bottomLeft, h), this, false, Point(0, 0, 0));
    Point bl(0,0,0);
    double current_h;

    Point closestPoint(0,0,0);
    int minDist = 0xFFFFFFF;

    while (!pq.empty()) {
        auto [dist, node, isLeaf, point] = pq.top();
        pq.pop();

        if (isLeaf) {
            if (dist < minDist) {
                minDist = dist;
                closestPoint = point;
                bl = node->bottomLeft;
                current_h = node->h;
            }
        } else { // nodo interno
            for (int i = 0; i < 8; i++) {
                if (node->children[i]) {
                    if (node->children[i]->nPoints <= N) { // el hijo es hoja
                        for (auto v : node->children[i]->points) {
                            // std::cout << "distancia: "<< calculateDistance(*v, p)<< "radio: " << radio << std::endl;
                            if (std::sqrt(calculateDistance(*v, p)) <= radio) {
                                pq.emplace(calculateDistance(*v,  p), node->children[i], true, *v);
                            }
                        }
                    } else {
                        int childDistSquared = minDistanceToOctant(p, node->children[i]->bottomLeft, node->children[i]->h);
                        if (childDistSquared < minDist) {
                            pq.emplace(childDistSquared, node->children[i], false, Point(0, 0, 0));
                        }
                      /* pq.emplace(minDistanceToOctant(p,
                                                     node->children[i]->bottomLeft,
                                                     node->children[i]->h),
                                 node->children[i], false, Point(0, 0, 0)); */
                    }
                }
            }
        }
    }
    // std::cout << "punto: " << bl.x << " " << bl.y << " " << bl.z << " " << current_h << std::endl;
    return closestPoint;
}
