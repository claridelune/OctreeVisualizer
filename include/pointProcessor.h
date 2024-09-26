#ifndef POINT_PROCESSOR
#define POINT_PROCESSOR

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

#include "point.h"

class PointProcessor {
    public:
      PointProcessor(std::string _filename)
          : filename(_filename), 
            min(std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()),
            max(std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min()) {}

      bool processFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "File could not open: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            Point point = parseLine(line);
            updateMinMax(point);
            points.push_back(point);
        }

        file.close();
        h = std::max({max.x - min.x, max.y - min.y, max.z - min.z});
        return true;
    }

      Point getBottomLeft()          const {return min;}
      int getH()             const {return h;}
      std::vector<Point> getPoints() const {return points;}

      void printBounds() const {
        std::cout << "bottom left: (" << min.x << ", " << min.y << ", " << min.z << ") " 
            << "height: " << h << std::endl;
    }

    private:
        Point min, max;
        std::string filename;
        int h;
        std::vector<Point> points;

        Point parseLine(std::string line) {
            double x, y, z;
            std::string token;
            std::istringstream ss;
            ss.str(line);

            std::getline(ss, token, ',');
            x = std::stod(token);
            std::getline(ss, token, ',');
            y = std::stod(token);
            std::getline(ss, token, ',');
            z = std::stod(token);

            return Point(x, y, z);
        }

        void updateMinMax(Point point) {
            if (point.x < min.x) min.x = point.x ; 
            if (point.x > max.x) max.x = point.x ;
            if (point.y < min.y) min.y = point.y ; 
            if (point.y > max.y) max.y = point.y ;
            if (point.z < min.z) min.z = point.z ; 
            if (point.z > max.z) max.z = point.z ;
        }
};

#endif
