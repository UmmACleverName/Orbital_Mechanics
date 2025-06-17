//A-Z
#include<exception>
#include<fstream> 
#include"hdr/computational_maths.hpp" 
#include"hdr/object_state.hpp" 
#include"hdr/utilities.hpp" 
#include"hdr/vector.hpp"
#include"hdr/wgs84.hpp" 
#include<iostream>
#include<string>
#include<vector>


void usage(std::string); 

int main(int argc, char* argv[])
{
    try{

        if(argc != 2) usage(argv[0]); 

        std::vector<CSV_ROW>       csv_data;                   //TODO: Can update this data structure to probably a linked list if
                                                               //      addition data wants to be added.
        
        std::vector<wgs84::object_state> node_state_list;      //A node state is a state that is given based on data given.  
        std::string                      file_string(argv[1]); //Read in the csv data file.  
        std::vector<wgs84::TIME>         test_times = {1532334000.0, 1532335268.0};


        read_scitec_data(file_string, csv_data);    //Read in the csv file and populate with row data. 
        maths::get_state(csv_data,node_state_list); //Will populate with object states at each node (Time_i).

        #if DEBUG == 1 
        
        std::ofstream logger_file;
        logger_file.open("./object_state_logging.txt");

        if(logger_file.is_open())
        {
            for(auto& state : node_state_list)
            {
                logger_file << std::fixed << "Time: " << state.time << '\n' 
                            << "Position: " << state.ecef_position 
                            << "Velocity: " << state.ecef_velocity
                            << "l2 position norm value: " << maths::norm(state.ecef_position) << std::endl
                            << "l2 velocity norm value: " << maths::norm(state.ecef_velocity) << std::endl << std::endl;
            }

            logger_file.close(); 
        }
        else //No need to throw exceptions since we just want to compute the interpolated data. 
            std::cerr << "\nobject_state_list.txt file can not be opened.\n\n"; 

        #endif 


        //Testing Test points from pdf. 
        for(const auto& time_time : test_times)
            interpolate_scitec_object_state(node_state_list,time_time); 


        return EXIT_SUCCESS;
    }
    catch(std::exception & other)
    {
        std::cout << other.what() << " exception occurred\n";
        return EXIT_FAILURE; 
    }
}


void usage(std::string executable_name)
{
    std::cout << "Usage: " << executable_name << " [PATH TO CSV FILE]\n"; 
    exit(EXIT_FAILURE); 
}



