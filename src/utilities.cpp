//A-Z
#include<fstream>
#include"hdr/computational_maths.hpp" 
#include"hdr/object_state.hpp" 
#include"hdr/utilities.hpp"
#include"hdr/vector.hpp"
#include<sstream> 
#include<string>
#include<vector>

//TODO: maybe update the date structure to a linked list. 
void read_scitec_data(std::string file_string, std::vector<CSV_ROW>& csv_data)
{
    std::ifstream  scitec_data_cvs(file_string); //TODO: Throw an exception if file can not be opened. 
    std::string    file_content;
    
    wgs84::WHAT_TYPE what_next = wgs84::is_time;
    wgs84::TIME      time      = 0.0; 
    wgs84::DEGREES   lat       = 0.0; 
    wgs84::DEGREES   lon       = 0.0; 
    wgs84::METERS    alt       = 0.0; 

    while(std::getline(scitec_data_cvs,file_content,' '))
    {
        std::istringstream ss(file_content);
        std::string token;
        while(std::getline(ss,token,','))
        {
            switch(what_next)
            {
                case wgs84::is_time:
                    time       = std::stod(token); //SECONDS
                    what_next  = wgs84::is_lat;
                    break; 
                case wgs84::is_lat:
                    lat        = std::stod(token);  //DEGREES 
                    what_next  = wgs84::is_lon;
                    break;
                case wgs84::is_lon: 
                    lon        = std::stod(token);  //DEGREES 
                    what_next  = wgs84::is_alt;
                    break;
                case wgs84::is_alt: 
                    alt       = std::stod(token);                 //KILOMETERS
                    alt       = wgs84::kilometers_to_meters(alt); //METERS 
                    what_next = wgs84::is_time;                   //Reset to time since the next row starts with time.
                    csv_data.push_back(std::make_tuple(time, lat, lon, alt)); 
                    continue;
            }//EOF switch case.
        }//EOF ss loop.
    }//EOF scitec_data_cvs loop.
}


//TODO: Computational complexity of this method is order O(N). Can probably get it 
//      down to O(log(n)) since the time data is in order (least to greatest). 
void interpolate_scitec_object_state(const std::vector<wgs84::object_state>& node_state_list,
                                     wgs84::TIME test_time)
{
    for(size_t idx = 1; idx < node_state_list.size(); ++idx)
    {
        wgs84::TIME time_a = node_state_list[idx - 1].time;
        wgs84::TIME time_b = node_state_list[idx].time;
        bool        inside = (time_a <= test_time) && (test_time < time_b); 

        if(inside)
        {
            wgs84::object_state interpolated_obj; 
            
            //To interpolate position.
            maths::vector ecef_position_a = node_state_list[idx - 1].ecef_position; 
            maths::vector ecef_position_b = node_state_list[idx].ecef_position; 
            
            //To interpolate velocity.
            maths::vector ecef_velocity_a = node_state_list[idx - 1].ecef_velocity; 
            maths::vector ecef_velocity_b = node_state_list[idx].ecef_velocity; 
            
            //Interpolating position. 
            interpolated_obj.ecef_position = maths::vector_linear_interpolation(time_a, 
                                                                                time_b, 
                                                                                test_time,
                                                                                ecef_position_a, 
                                                                                ecef_position_b);
            //Interpolating velocity. 
            interpolated_obj.ecef_velocity = maths::vector_linear_interpolation(time_a, 
                                                                                time_b, 
                                                                                test_time,
                                                                                ecef_velocity_a, 
                                                                                ecef_velocity_b);

            //TODO: If the data structure was something other than a std::vector (maybe linked list) then I could just add
            //      the interpolated object to that data structure.
            std::cout << "Interpolated Object\n"; 
            std::cout << std::fixed << "Time Point Given: " << test_time << std::endl 
                      << "Time interval found: " << "(" << time_a << ',' << time_b << "]\n" 
                      << "Interpolated ecef position(m): " << interpolated_obj.ecef_position
                      << "Interpolated ecef velocity(m): " << interpolated_obj.ecef_velocity
                      << "l2 position norm value(m): " << maths::norm(interpolated_obj.ecef_position) << std::endl
                      << "l2 velocity norm value(m): " << maths::norm(interpolated_obj.ecef_velocity) << std::endl << std::endl;

        }//EOF if statement. 
    }//EOF idx loop. 
}


