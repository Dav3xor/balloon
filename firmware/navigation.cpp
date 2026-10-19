#include <Arduino.h>
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

float deg_to_rad(float val) {
  return val*3.14159/180.0;
}



Fix build_fix(Point &vehicle, Point &target, float course, float speed) {
  float vy = vehicle.lat;
  float adjust = cos(vy);

  float vx = adjust * (vehicle.lon);
  //Serial.print("adj="); Serial.println(adjust);

  float ty = target.lat;
  float tx = adjust * (target.lon);

  float bearing = atan2(vy-ty,vx-tx);

  float a_slope = tan(course);
  if (a_slope == 0.0) {
    a_slope = 0.000000000001;
  }
  float b_slope = -1.0/a_slope;
  //Serial.print("as=");Serial.print(a_slope);Serial.print(" bs=");Serial.println(b_slope);

  float target_y_int  = ty - (b_slope*tx);   // b[1] - (b_slope*b[0])
  float vehicle_y_int = vy - (a_slope*vx);  // a[1] - (a_slope*a[0])

  float x = (vehicle_y_int-target_y_int) / (b_slope - a_slope);
  float y = (a_slope*x) + vehicle_y_int;

  //Serial.print("x="); Serial.print(x,5); Serial.print(" y="); Serial.println(y,5);

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

void print_point(Point &p){
  Serial.print("lat: ");
  Serial.print(p.lat*180.0/3.14159,4);
  Serial.print(" lon: ");
  Serial.println(p.lon*180.0/3.14159,4);

}

void print_fix(Fix &fix) {
  Serial.print("bearing: ");
  Serial.print(fix.bearing,4);
  Serial.print(" distance: ");
  Serial.print(fix.distance,4);
  Serial.print(" cad: ");
  Serial.print(fix.closest_approach_distance,4);
  Serial.print(" dtca: ");
  Serial.print(fix.distance_to_closest_approach,4);
  Serial.print(" ttca: ");
  Serial.println(fix.time_to_closest_approach,4);
}