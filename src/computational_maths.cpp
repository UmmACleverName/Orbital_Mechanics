#include"hdr/computational_maths.hpp"
#include"hdr/wgs84.hpp" 



namespace maths
{
    maths::vector vector_linear_interpolation(double time_a, double time_b, double time,
                                              maths::vector& node_a, maths::vector& node_b)
    {
        /* Lagrange Cardinal Basis
         * ------------------------
         * Given t in [t_n, t_{n+1}] for f(t) : t -> reals.
         * The linear polynomial polynomial interpolates f(t_n) and f(t{n+1}).
         * 
         *      p(t) = ( (t_{n+1} - t) / (t_{n+1} - t_n) ) * f(t_n) + 
                       ( (t_n - t) / (t_n - t_{n+1}) ) * f(t_{n+1})
         *
         *
         *  Therefore, 
         *
         *      p(t_n)     = f(t_n)
         *      p(t_{n+1}) = f(t_{n+1})
         *
         *  Define: omega = 1 / ( t_{n+1} - t_n ) then 
         *
         *      p(t) = omega * (t_{n+1} - t) * f(t_n) - omega * (t_n - t) * f(t_{n+1})
         *  
         */

        double omega   = 1.0 / (time_b - time_a);
        double omega_a =  omega * (time_b - time);
        double omega_b =  omega * (time  - time_a);

        maths::vector vec_a = omega_a * node_a;
        maths::vector vec_b = omega_b * node_b; 
        maths::vector interpolation = vec_a + vec_b; 


        return interpolation; 
    }


    //TODO: Can add numerical check guards to make sure no division by zero or infinity and blah...  
    void get_state(const std::vector<CSV_ROW>& csv_data,
                   std::vector<wgs84::object_state>& node_state_list)
    {
        wgs84::TIME time_prev;
        wgs84::TIME time_current;
        wgs84::TIME delta_time;
        
        //Compute Velocities.
        for(size_t idx = 0; idx < csv_data.size();  ++idx)
        {
        
            wgs84::object_state object;
            CSV_ROW row_current                 = csv_data[idx]; 
            maths::vector ecef_position_current = wgs84::lla_to_ecef(std::get<1>(row_current),  //Lat (Radians)
                                                                     std::get<2>(row_current),  //Lon (Radians)
                                                                     std::get<3>(row_current)); //Alt (Meters)
        

            object.time          = std::get<0>(csv_data[idx]);
            object.ecef_position = ecef_position_current; 

            if( idx == 0 )  
            {
                object.ecef_velocity = maths::vector(3,0.0); 
                node_state_list.push_back(object);
                continue; 
            }// Initial velocity to be zero vector per request. 
        
            //csv_row = time, lat, lon, alt.
            CSV_ROW row_prev    = csv_data[idx-1];
            time_prev           = std::get<0>(row_prev);            //Time (Seconds)
            time_current        = std::get<0>(row_current);         //Time (Seconds)
            delta_time          = 1.0 / (time_current - time_prev); //Hz   (Time^{-1})  
            
            maths::vector ecef_position_prev = wgs84::lla_to_ecef(std::get<1>(row_prev),        //Lat (Radians)
                                                                  std::get<2>(row_prev),        //Lon (Radians)
                                                                  std::get<3>(row_prev));       //Alt (Meters)
        
            //Compute velocity by velocity{i} = ( x(t{i}) - x(t{i-1}) ) / ( t{i] - t{i-1} ) 
            object.ecef_velocity = wgs84::estimate_ecef_velocity(delta_time,
                                                                 ecef_position_prev,
                                                                 ecef_position_current);
        
            //Store data for search later.
            node_state_list.push_back(object); 
        }
        
    }


}//EOF namespace maths


