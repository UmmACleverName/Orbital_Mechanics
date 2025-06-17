#ifndef OBJECT_STATE_HPP
#define OBJECT_STATE_HPP
//A-Z
#include"hdr/vector.hpp"
#include"hdr/wgs84.hpp"

namespace wgs84{

    //TODO: Can make this a class then add setters, getters, and other fun stuff.
    struct object_state
    {
        maths::vector ecef_position;
        maths::vector ecef_velocity;
        wgs84::TIME   time;

        object_state(); 
        ~object_state(); 
    }; 

}



#endif 
