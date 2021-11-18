/* This file should contain the 9 functions defined in prototypes.h */
#include "prototypes.h"
/*
double GetArea(struct Shape *s)
{
    double area;
    if (s->st == CIRCLE)
        GetCircleArea(s);
    return area;    
}

void GetBoundBox
*/
void InitializeCircle(struct Shape *c, double radius, double originX, double originY)
{
    c->st = CIRCLE;
    c->su.circle.radius = radius;
    c->su.circle.originX = originX;
    c->su.circle.originY = originY;
    c->ft.GetArea = GetCircleArea;
    c->ft.GetBoundingBox = GetCircleBoundingBox;
}

void InitializeRectangle(struct Shape *r, double minX, double maxX, double minY, double maxY)
{
    r->st = RECTANGLE;
    r->su.rectangle.minX = minX;
    r->su.rectangle.maxX = maxX;
    r->su.rectangle.minY = minY;
    r->su.rectangle.maxY = maxY;
    r->ft.GetArea = GetRectangleArea;
    r->ft.GetBoundingBox = GetRectangleBoundingBox;
}

void InitializeTriangle(struct Shape *t, double pt1X, double pt2X, double minY, double maxY)
{
    t->st = TRIANGLE;
    t->su.triangle.pt1X = pt1X;
    t->su.triangle.pt2X = pt2X;
    t->su.triangle.minY = minY;
    t->su.triangle.maxY = maxY;
    t->ft.GetArea = GetTriangleArea;
    t->ft.GetBoundingBox = GetTriangleBoundingBox;
}

double GetCircleArea(struct Shape *c)
{
    double area;
    area = 3.14159 * c->su.circle.radius * c->su.circle.radius;
    return area;
}

double GetRectangleArea(struct Shape *r)
{
    double area;
    area = (r->su.rectangle.maxX - r->su.rectangle.minX) * (r->su.rectangle.maxY - r->su.rectangle.minY);
    return area;
}

double GetTriangleArea(struct Shape *t)
{
    double area;
    area = (t->su.triangle.pt2X - t->su.triangle.pt1X)*(t->su.triangle.maxY - t->su.triangle.minY) / 2;
    return area;
}

void GetCircleBoundingBox(struct Shape *c, double *bbox)
{
    bbox[0] = c->su.circle.originX - c->su.circle.radius;
    bbox[1] = c->su.circle.originX + c->su.circle.radius;
    bbox[2] = c->su.circle.originY - c->su.circle.radius;
    bbox[3] = c->su.circle.originY + c->su.circle.radius;
}

void GetRectangleBoundingBox(struct Shape *r, double *bbox)
{
    bbox[0] = r->su.rectangle.minX;
    bbox[1] = r->su.rectangle.maxX;
    bbox[2] = r->su.rectangle.minY;
    bbox[3] = r->su.rectangle.maxY;
}

void GetTriangleBoundingBox(struct Shape *t, double *bbox)
{
    bbox[0] = t->su.triangle.pt1X;
    bbox[1] = t->su.triangle.pt2X;
    bbox[2] = t->su.triangle.minY;
    bbox[3] = t->su.triangle.maxY;
}

