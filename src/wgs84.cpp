//A-Z
#include"hdr/wgs84.hpp"

namespace wgs84{


    //TODO: use basic maths to simplify this work. 
	maths::vector lla_to_ecef(DEGREES lat, DEGREES lon, METERS alt)
	{
        maths::vector ecef_vector(3);
        RADIANS radian_lat = degrees_to_radians(lat); 
        RADIANS radian_lon = degrees_to_radians(lon);
        double sin_sq      = pow(sin(radian_lat),2.0); //Unitless.
        double first_eccentricity_sq = pow(first_eccentricity,2.0); //Unitless
        double semi_axis_ratio = semi_minor_axis_sq / semi_major_axis_sq; 

        METERS radius_of_curvature   = 
            semi_major_axis / sqrt( 1.0 - (first_eccentricity_sq * sin_sq) ); //Unit(Meters)

        METERS x = (radius_of_curvature + alt) * cos(radian_lat) * cos(radian_lon);
        METERS y = (radius_of_curvature + alt) * cos(radian_lat) * sin(radian_lon);
        METERS z = (semi_axis_ratio * radius_of_curvature + alt) * sin(radian_lat);

        ecef_vector[0] = x;
        ecef_vector[1] = y;
        ecef_vector[2] = z;
        return ecef_vector;
	}

    maths::vector estimate_ecef_velocity(TIME delta_time,
                                         maths::vector& ecef_position_prev, 
                                         maths::vector& ecef_position_next)
    {
        maths::vector ecef_velocity = ecef_position_next - ecef_position_prev;
        ecef_velocity = delta_time * ecef_velocity;

        return ecef_velocity; 

    }

}//EOF wgs84 namespace. 
