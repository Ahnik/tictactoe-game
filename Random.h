#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <chrono>       // For accessing the high-res clock
#include <random>       // For std::random_device and std::mt19937

class Random
{
public:

    using RandomNumber = int;
    using MersenneTwister = std::mt19937;

    // Generate a random int between [min, max](inclusive)
    static RandomNumber Range(int min, int max)
    {
        return std::uniform_int_distribution{min, max}(mt);
    }

private:
    using ClockSeed = long long;
    using DeviceSeed = std::random_device;
    using SeedSequence = std::seed_seq;
    using RandomSeed = SeedSequence::result_type;

    using SystemClock = std::chrono::steady_clock;

    static MersenneTwister generateTwister()
    {   
        const ClockSeed cs{SystemClock::now().time_since_epoch().count()};  
        DeviceSeed ds{};

        // Create a seed sequence with the high-res clock and 7 random numbers from std::random_device
        SeedSequence ss{
            static_cast<RandomSeed>(cs), ds(), ds(), ds(), ds(),ds(), ds(), ds()
        };

        return MersenneTwister{ss};
    }

    static inline MersenneTwister mt{generateTwister()};    // generates a seeded std::mt19937 and copies it into our global object

    // Returns a seeded std::mt19937 object
    const static MersenneTwister getMersenneTwister(){ return mt;}
};

#endif