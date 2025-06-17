#ifndef VECTOR_HPP
#define VECTOR_HPP

//A-Z
#include<iostream>
#include<memory>



namespace maths{

typedef unsigned int DIM;

class vector
{
    public:
        vector()  = default;
        ~vector() = default;
        vector(const vector&);
        vector(vector&&);
        vector(DIM);
        vector(DIM,double);
        vector& operator=(const vector&); 
        vector& operator=(vector&&); 

        double& operator[](unsigned int);
        DIM get_dim(void) const;

        friend std::ostream& operator<<(std::ostream&, maths::vector&); 
    private:
        DIM _dim;
        std::unique_ptr<double[]> _data_ptr;
}; //EOF vector class.

vector operator+(vector&,vector&);
vector operator-(vector&,vector&);
vector operator*(double scalar,vector& vec_b);

double dot(vector&, vector&);
double norm(vector&, double power = 2.0);








}//EOF maths namespace.








#endif
