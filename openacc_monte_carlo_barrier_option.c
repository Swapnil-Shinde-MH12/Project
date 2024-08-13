#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  // Include the time header for timing functions
#include <openacc.h>

#define NUM_SIMULATIONS 1000000
#define NUM_STEPS 100

// Function to generate Gaussian random numbers
double rand_gaussian() {
    // Box-Muller transform
    double u = rand() / (RAND_MAX + 1.0);
    double v = rand() / (RAND_MAX + 1.0);
    return sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
}

// Monte Carlo Simulation for Barrier Option Pricing
double monte_carlo_barrier_option(double S0, double K, double r, double sigma, double T, double B, int num_simulations, int num_steps) {
    double dt = T / num_steps;
    double payoff_sum = 0.0;
    
    #pragma acc data copyin(S0, K, r, sigma, T, B) copyout(payoff_sum)
    {
        #pragma acc parallel loop reduction(+:payoff_sum)
        for (int i = 0; i < num_simulations; i++) {
            double S = S0;
            int breached = 0;
            
            for (int j = 0; j < num_steps; j++) {
                double dW = sqrt(dt) * rand_gaussian();
                S *= exp((r - 0.5 * sigma * sigma) * dt + sigma * dW);
                
                if (S <= B) {
                    breached = 1;
                    break;
                }
            }
            
            if (!breached) {
                double payoff = fmax(S - K, 0.0);
                payoff_sum += payoff;
            }
        }
    }
    
    return exp(-r * T) * (payoff_sum / num_simulations);
}

int main() {
    double S0 = 100.0;   // Initial stock price
    double K = 100.0;    // Strike price
    double r = 0.05;     // Risk-free rate
    double sigma = 0.2;  // Volatility
    double T = 1.0;      // Time to maturity (in years)
    double B = 90.0;     // Barrier level

    clock_t start_time, end_time;
    double cpu_time_used;
    
    start_time = clock();  // Start timing
    
    double option_price = monte_carlo_barrier_option(S0, K, r, sigma, T, B, NUM_SIMULATIONS, NUM_STEPS);
    
    end_time = clock();  // End timing
    
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC * 1000;  // Convert to milliseconds
    
    printf("Barrier Option Price: %f\n", option_price);
    printf("Time taken: %.2f milliseconds\n", cpu_time_used);
    
    return 0;
}
