#ifndef __NAVIGATION_H__
#define __NAVIGATION_H__


struct Point {
    float lat;
    float lon;
};

struct Fix {
    Point closest;
    float bearing;
    float distance;
    float closest_approach_distance;
    float distance_to_closest_approach;
    float time_to_closest_approach;
};

float distance(Point &a, Point &b);
Fix   build_fix(Point &vehicle, Point &target, float course, float speed);
void  print_point(Point &p);
void  print_fix(Fix &fix);
float deg_to_rad(float val);
#endif
