/*
  USE OLD BOOTLOADER ARDUINO NANO //SERIAL PRINTS IN ASCII
  GPS MODULE
*/
#include <math.h> // to use atan
double last_lat = 41.366433;
double last_long = -71.498595;
double curr_lat = 41.360724;
double curr_long = -71.481032;
double dest_lat = 18.448041;
double dest_long = -65.999568;
double des_bearing;
double distance;
double error;
double speed_boat;
unsigned long time_passed = 0;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  time_passed = millis();//store time passed
  calc_bear(curr_lat, curr_long, dest_lat, dest_long);
  calc_dist(curr_lat, curr_long, dest_lat, dest_long);
  calc_turn_error(360, des_bearing);
  calc_dist(last_lat, last_long, curr_lat, curr_long);

  if (time_passed - previousMillis >= interval) {
    det_speed(last_lat, last_long, curr_lat, curr_long);
    Serial.print("Bearing needed: ");//delete
    Serial.print(des_bearing); //delete
    Serial.println("");//delete

    Serial.print("Distance: ");//delete
    Serial.print(distance, 2); //delete
    Serial.print(" mi");//delete
    Serial.println("");//delete

    Serial.print("Turning to: ");//delete
    Serial.print(error); //delete
    Serial.println("");//delete

    Serial.print("Speed: ");//delete
    Serial.print(speed_boat, 2); //delete
    Serial.print(" mph");//delete
    Serial.println("");//delete
  }

}

double calc_bear(double lat_1, double long_1, double lat_2, double long_2) { // Determine the position we need to turn
  double arc_calc = atan2(long_2 - long_1, lat_2 - lat_1) * 180 / 3.14159;
  des_bearing = arc_calc;
  return des_bearing;
}
double calc_turn_error(double curr_bearing, double des_bearing) { // Determine turn error. + Right -Left
  error = des_bearing - curr_bearing;
  return error;
}
double calc_dist(double lat_1, double long_1, double lat_2, double long_2) { //Determine distance
  double R = 3958.8; //Radius of earth
  double dLat = 3.14159 * (lat_2 - lat_1) / 180;
  double dLon = 3.14159 * (long_2 - long_1) / 180;
  double lat1 = 3.14159 * (lat_1) / 180;
  double lat2 = 3.14159 * (lat_2) / 180;
  double a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * sin(lat1) * cos(lat2);
  double c = 2 * asin(sqrt(a));
  distance = (R * c);
  return distance;
}
double det_speed(double lat_1, double long_1, double lat_2, double long_2) { //Determine speed in mph FIX
  double R = 3958.8; //Radius of earth
  double dLat = 3.14159 * (lat_2 - lat_1) / 180;
  double dLon = 3.14159 * (long_2 - long_1) / 180;
  double lat1 = 3.14159 * (lat_1) / 180;
  double lat2 = 3.14159 * (lat_2) / 180;
  double a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * sin(lat1) * cos(lat2);
  double c = 2 * asin(sqrt(a));
  speed_boat = (R * c) * 360;//convert second to hour
  previousMillis = time_passed;
  return speed_boat;
}
