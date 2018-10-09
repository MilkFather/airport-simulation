#include "random.hpp"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <climits>

int Random::reseed() {
    seed = seed * multiplier + add_on;
    return seed;
}

Random::Random(bool pseudo) {
    if (pseudo)
        seed = 1;
    else
        seed = time(NULL) % INT_MAX;
    multiplier = 2743;
    add_on = 5923;
}

double Random::random_real() {
    /* generates a random real in range [0, 1), distributed linearly. */
    double max = INT_MAX + 1.0;
    double temp = reseed();
    if (temp < 0)
        temp += max;
    return temp / max;
}

int Random::random_integer(int low, int high) {
    /* generates a random integer in range [low, high], distributed linearly */
    if (low > high)
        return random_integer(high, low);
    else
        return ((int) ((high - low + 1) * random_real())) + low;
}

int Random::poisson(double mean) {
    /* generates a random integer, reflecting the Poisson distribution with parameter mean */
    double limit = exp(-mean);
    double product = random_real();
    int count = 0;
    while (product > limit) {
        count++;
        product *= random_real();
    }
    return count;
}
