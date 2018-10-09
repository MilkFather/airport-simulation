#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random {
public:
    Random(bool pseudo = true);
    // Declare random-number generation methods here
    double random_real(void);
    int random_integer(int low, int high);
    int poisson(double mean);
    
private:
    int reseed();
    int seed, multiplier, add_on;
};

#endif
