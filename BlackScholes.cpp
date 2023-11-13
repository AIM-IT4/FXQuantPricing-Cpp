#include <iostream>
#include <cmath>
#include <algorithm>

// Function to calculate the cumulative normal distribution
double norm_cdf(const double& x) {
    return 0.5 * erfc(-x / sqrt(2));
}

// Function to calculate the normal probability density function
double norm_pdf(const double& x) {
    return (1.0/(pow(2*M_PI, 0.5)))*exp(-0.5*x*x);
}

// Function to calculate d1 in the Black-Scholes formula
double calculate_d1(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time) {
    return (log(S/K) + (r - q + sigma*sigma*0.5) * time) / (sigma * sqrt(time));
}

// Function to calculate d2 in the Black-Scholes formula
double calculate_d2(const double& d1, const double& sigma, const double& time) {
    return d1 - sigma * sqrt(time);
}

// Function to calculate the Black-Scholes price of a European call option
double call_option_price(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time) {
    double d1 = calculate_d1(S, K, r, q, sigma, time);
    double d2 = calculate_d2(d1, sigma, time);

    return S * exp(-q * time) * norm_cdf(d1) - K * exp(-r * time) * norm_cdf(d2);
}

// Function to calculate the Black-Scholes Delta of a European call option
double call_delta(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time) {
    double d1 = calculate_d1(S, K, r, q, sigma, time);
    return exp(-q * time) * norm_cdf(d1);
}

// Function to calculate the Black-Scholes Vega of a European call option
double call_vega(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time) {
    double d1 = calculate_d1(S, K, r, q, sigma, time);
    return S * exp(-q * time) * norm_pdf(d1) * sqrt(time);
}

int main() {
    // Input parameters
    double S = 1.20;    // Current FX rate (e.g., USD/EUR)
    double K = 1.30;    // Strike price
    double r = 0.05;     // Risk-free rate (domestic)
    double q = 0.02;     // Foreign risk-free rate
    double sigma = 0.20; // Volatility of the underlying FX rate
    double time = 1.0;   // Time to expiration in years

    // Calculate and output the Black-Scholes price and Greeks for the call option
    double price = call_option_price(S, K, r, q, sigma, time);
    double delta = call_delta(S, K, r, q, sigma, time);
    double vega = call_vega(S, K, r, q, sigma, time);

    std::cout << "The Black-Scholes price of the European call option is: " << price << std::endl;
    std::cout << "The Delta of the option is: " << delta << std::endl;
    std::cout << "The Vega of the option is: " << vega << std::endl;

    return 0;
}
