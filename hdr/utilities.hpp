#ifndef UTILITIES_HPP
#define UTILITIES_HPP
//A-Z
#include"hdr/wgs84.hpp" 
#include<string>
#include<tuple>
#include<vector> 

typedef std::tuple<double,double,double,double> CSV_ROW;  

void read_scitec_data(std::string file_string, std::vector<CSV_ROW>& csv_data); 

void interpolate_scitec_object_state(const std::vector<wgs84::object_state>&,
                                     wgs84::TIME);  


#endif 
