#include"hdr/object_state.hpp"


namespace wgs84
{
    object_state::object_state() : ecef_position(3,0.0),
                                   ecef_velocity(3,0.0),
                                   time(0.0)
    {}

    object_state::~object_state() {}
}
