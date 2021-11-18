/* This file should contain your struct definitions for Circle, Triangle, and Rectangle */
#ifndef my_struct_H_
#define my_struct_H_

struct Shape;

typedef struct
{
    double radius;
    double originX;
    double originY;
} Circle;

typedef struct
{
    double pt1X;
    double pt2X;
    double minY;
    double maxY;
} Triangle;

typedef struct
{
    double minX;
    double maxX;
    double minY;
    double maxY;
} Rectangle;

typedef union
{
    Circle circle;
    Triangle triangle;
    Rectangle rectangle;
} ShapeUnion;

typedef struct
{
    double(*GetArea)(struct Shape*);
    void (*GetBoundingBox)(struct Shape*, double*);
} FunctionTable;

typedef enum
{
    CIRCLE,
    TRIANGLE,
    RECTANGLE
} ShapeType;

struct Shape
{
    ShapeType st;
    ShapeUnion su;
    FunctionTable ft;
};

#endif
