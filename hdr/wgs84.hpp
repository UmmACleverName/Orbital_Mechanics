#ifndef WGS84_HPP
#define WGS84_HPP

//A-Z
#include"hdr/vector.hpp"
#include<math.h>


namespace wgs84{

	//WGS84 Parameters
	constexpr double semi_major_axis      = 6'378'137;                 //Eigen value of the ellipse. Unit(meters)
	constexpr double semi_minor_axis      = 6'356'752.31424518;        //Eigen value of the ellipse. Unit(meters)
	
	constexpr double semi_major_axis_sq   = pow(semi_major_axis,2.0);  //Units(meters^2) 
	constexpr double semi_minor_axis_sq   = pow(semi_minor_axis,2.0);  //Units(meters^2)

	constexpr double first_eccentricity   = 
		sqrt( (semi_major_axis_sq - semi_minor_axis_sq) / semi_major_axis_sq); //Unitless
	
	constexpr double second_eccentricity  = 
		sqrt( (semi_major_axis_sq - semi_minor_axis_sq) / semi_minor_axis_sq); //Unitless

    //Keep track of the units instead of just having a double.
	typedef double KILOMETERS; 
	typedef double METERS; 
    typedef double DEGREES;
    typedef double RADIANS;
    typedef double TIME; 

    //For utilities functions.  
    enum WHAT_TYPE { is_time = 0x01, is_lat, is_lon, is_alt };
    
    //Main functions. 
	maths::vector lla_to_ecef(DEGREES, DEGREES, METERS);
	//TODO: add ecef to lla.
    maths::vector estimate_ecef_velocity(TIME delta_time,
                                         maths::vector& ecef_position_prev, 
                                         maths::vector& ecef_position_next); 

    //Helper functions. 
	inline METERS     kilometers_to_meters(KILOMETERS kilometer) { return 1.0e+3 * kilometer; }
	inline KILOMETERS meters_to_kilometers(METERS meter)         { return 1.0e-3 * meter; }
	inline RADIANS    degrees_to_radians(DEGREES degrees)        { return ( M_PI  / 180.0) * degrees; }
	inline DEGREES    radians_to_degrees(RADIANS radians)        { return ( 180.0 / M_PI ) * radians; }

}//EOF wgs84 namespace. 





#endif 
