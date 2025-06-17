#ifndef COMPUTATIONAL_MATHS_HPP
#define COMPUTATIONAL_MATHS_HPP
//A-Z
#include"hdr/object_state.hpp" 
#include"hdr/utilities.hpp" 
#include"hdr/vector.hpp"
#include"hdr/wgs84.hpp" 
#include"vector" 

namespace maths
{
    maths::vector vector_linear_interpolation(double time_a, double time_b, double time,
                                              maths::vector& node_a, maths::vector& node_b); 

    //TODO: Update std::vector<CSV_ROW> -> some typedef.
    // Older version. 
    void get_estimated_velocities(const std::vector<CSV_ROW>& csv_data, 
                                  std::vector<maths::vector>& velocities, 
                                  std::vector<wgs84::TIME>&   times); 

    //TODO: Update std::vector<CSV_ROW> -> some typedef 
    void get_state(const std::vector<CSV_ROW>& csv_data,
                   std::vector<wgs84::object_state>& node_state_list); 


}//EOF namespace maths










#endif 
