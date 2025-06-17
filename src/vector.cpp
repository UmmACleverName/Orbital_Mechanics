//A-Z
#include"hdr/vector.hpp"
#include<math.h>


namespace maths{

    /*-------------------------------------------------------------------*/
    vector::vector(DIM dim) : _dim(dim), _data_ptr(new double[dim]) 
    {}
   
    /*-------------------------------------------------------------------*/
    vector::vector(DIM dim, double value) : _dim(dim), _data_ptr(new double[dim]) 
    {
        for(size_t idx = 0; idx < dim; ++idx)
            _data_ptr[idx] = value; 
    }
    
    /*-------------------------------------------------------------------*/
    vector::vector(const vector& vec)
    {
        _dim = vec._dim;
        _data_ptr.reset(new double[_dim]);

        for(size_t idx = 0; idx < _dim; ++idx)
            _data_ptr[idx] = vec._data_ptr[idx]; 
    }

    /*-------------------------------------------------------------------*/
    vector::vector(vector&& vec)
    {
        _dim = vec._dim;
        _data_ptr = std::move(vec._data_ptr); 
    }
   
    /*-------------------------------------------------------------------*/
    vector& vector::operator=(const vector& vec)
    {
        _dim = vec._dim;
        _data_ptr.reset(new double[_dim]);

        for(size_t idx = 0; idx < _dim; ++idx)
            _data_ptr[idx] = vec._data_ptr[idx];

        return *this;
    }

    /*-------------------------------------------------------------------*/
    vector& vector::operator=(vector&& vec)
    {
        _dim = vec._dim;
        _data_ptr = std::move(vec._data_ptr); 
        
        return *this;
    }

    /*-------------------------------------------------------------------*/
    double& vector::operator[](unsigned int index)
    {
        //TODO: add check guards. 
        return _data_ptr[index]; 
    }

    /*-------------------------------------------------------------------*/
    DIM vector::get_dim(void) const 
    {
        return _dim; 
    }
    
    /*-------------------------------------------------------------------*/
    std::ostream& operator<<(std::ostream& stream, maths::vector& vec)
    {
        maths::DIM dim = vec.get_dim();
        stream << '['; 
        for(size_t idx = 0; idx < dim - 1 ; ++idx)
            stream << vec[idx] << ',';
        stream << vec[dim - 1] << "]\n"; 

        return stream; 
    }

    /*-------------------------------------------------------------------*/
    vector operator+(vector& vec_a, vector& vec_b)
    {
        //TODO: add dim check.
        DIM dim = vec_a.get_dim();
        vector return_vec(dim);

        for(size_t idx = 0; idx < dim; ++idx)
            return_vec[idx] = vec_a[idx] + vec_b[idx];

        return return_vec;
    }

    /*-------------------------------------------------------------------*/
    vector operator-(vector& vec_a, vector& vec_b)
    {
        //TODO: add dim check.
        DIM dim = vec_a.get_dim();
        vector return_vec(dim);

        for(size_t idx = 0; idx < dim; ++idx)
            return_vec[idx] = vec_a[idx] - vec_b[idx];

        return return_vec;
    }

    /*-------------------------------------------------------------------*/
    vector operator*(double scalar, vector& vec)
    {
        DIM dim = vec.get_dim();
        vector return_vec(dim);
        
        for(size_t idx = 0; idx < dim; ++idx)
            return_vec[idx] = scalar * vec[idx];

        return return_vec;
    }
    

    double dot(vector& vec_a, vector& vec_b)
    {
        //TODO: check for dim 
        DIM dim = vec_a.get_dim(); 
        double sum = 0.0;
        for(size_t idx = 0; idx < dim; ++idx)
            sum += vec_a[idx] * vec_b[idx];

        return sum; 
    }

    double norm(vector& vec, double power)
    {
        DIM dim = vec.get_dim();
        double sum = 0.0;
        for(size_t idx = 0; idx < dim; ++idx)
            sum += pow(abs(vec[idx]),power);
        sum = pow(sum, (1.0/power)); 
        return sum;
    }

}//EOF maths namespace.




