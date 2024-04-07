// Copyright 2024 Khodyrev Fedor

#include "include/point_hits_a_triangle.h"

#include <cmath>
#include <stdexcept>

Point::Point(double x_coord, double y_coord) : x(x_coord), y(y_coord) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

double Triangle::distance(const Point& p1, const Point& p2) {
    double dx = p2.getX() - p1.getX();
    double dy = p2.getY() - p1.getY();
    return std::sqrt(dx * dx + dy * dy);
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3)
    : v1(v1), v2(v2), v3(v3) {}

bool Triangle::isValid() const {
    double side1 = Triangle::distance(v1, v2);
    double side2 = Triangle::distance(v1, v3);
    double side3 = Triangle::distance(v2, v3);

    if (!(side1 + side2 > side3) || !(side1 + side3 > side2) ||
    !(side2 + side3 > side1)) {
        throw std::invalid_argument("Triangle with given vertices
        does not exist.");
    }

    return true;
}

double triangleArea(const Point& a, const Point& b, const Point& c) {
    return fabs((a.getX() * (b.getY() - c.getY()) + b.getX()
    * (c.getY() - a.getY())
    + c.getX()*(a.getY()-b.getY())) / 2);
}

bool Triangle::isInside(const Point& p) const {
    double totalArea = triangleArea(v1, v2, v3);
    double subArea1 = triangleArea(v1, v2, p);
    double subArea2 = triangleArea(v2, v3, p);
    double subArea3 = triangleArea(v3, v1, p);

    return (totalArea == subArea1 + subArea2 + subArea3);
}