#include <math.h>
#include "navigation.h"

// distance between two points on a sphere, units are in radians...
float distance(Point &a, Point &b) {
  double result = (acos(sin(a.lat)*sin(b.lat)+cos(a.lat)*cos(b.lat)*cos(a.lon-b.lon)) * 180.0 * 60.0);
  if (result < 20.0) {
    result = (2*asin(sqrt(pow(sin((a.lat-b.lat)/2),2.0) + 
              cos(a.lat)*cos(b.lat)*pow((sin((a.lon-b.lon)/2)),2.0)))) * 180.0 * 60.0; // convert to nautical miles
  }
  return result;
}

Fix build_fix(Point &vehicle, Point &target, float course, float speed) {
  float vy = vehicle.lat*3.14159/180.0;
  float adjust = cos(vy);
  float vx = adjust * (vehicle.lon*3.14159/180.0);
  
  float ty = target.lat*3.14159/180.0;
  float tx = adjust * (target.lon*3.14159/180.0);

  float bearing = atan2(vy-ty,vx-tx);

  float a_slope = tan(course);
  float b_slope = -1.0/a_slope;

  float target_y_int =  ty  - (b_slope*tx);   // b[1] - (b_slope*b[0])
  float vehicle_y_int = vy -  (a_slope*vx);  // a[1] - (a_slope*a[0])

  float x = (vehicle_y_int-target_y_int) / ((b_slope*vx) - (a_slope*vx));
  float y = (a_slope*x) + vehicle_y_int;

  float distance                     = sqrt(((vx-tx)*(vx-tx)) + ((vy-ty)*(vy-ty))); 
  float distance_to_closest_approach = sqrt(((vx-x)*(vx-x))   + ((vy-y)*(vy-y)));
  float closest_approach_distance    = sqrt(((tx-x)*(tx-x))   + ((ty-y)*(ty-y)));
  float time_to_closest_approach     = distance_to_closest_approach/speed;

  return Fix  {.closest = {.lat = y, .lon = x/adjust}, 
               .bearing = bearing, 
               .distance = distance,
               .closest_approach_distance = closest_approach_distance,
               .distance_to_closest_approach = distance_to_closest_approach,
               .time_to_closest_approach = time_to_closest_approach};
}

