#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // For max function

// Helper function for the cumulative normal distribution function
double norm_cdf(const double& x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

// Black-Scholes call price function
double black_scholes_call(const double& S, const double& K, const double& r, 
                          const double& v, const double& T) {
    double d1 = (log(S / K) + (r + 0.5 * v * v) * T) / (v * sqrt(T));
    double d2 = d1 - v * sqrt(T);

    return S * norm_cdf(d1) - K * exp(-r * T) * norm_cdf(d2);
}

// SABR volatility function using Hagan's approximation
double sabr_volatility(double K, double F, double T, double alpha, 
                       double beta, double rho, double nu) {
    if (F == K) { // ATM formula
        double term1 = alpha / pow(F, 1 - beta);
        double term2 = (1 + (pow(1 - beta, 2) * alpha * alpha / (24 * pow(F, 2 - 2 * beta)) 
                    + rho * beta * nu * alpha / (4 * pow(F, 1 - beta)) 
                    + (2 - 3 * rho * rho) * nu * nu / 24) * T);
        return term1 * term2;
    }

    // For non-ATM options
    double z = nu / alpha * pow(F * K, (1 - beta) / 2) * log(F / K);
    double x = log((sqrt(1 - 2 * rho * z + z * z) + z - rho) / (1 - rho));
    double A = pow(F * K, (1 - beta) / 2) * (1 + pow(1 - beta, 2) / 24 * pow(log(F / K), 2)
                    + pow(1 - beta, 4) / 1920 * pow(log(F / K), 4));
    double B = 1 + (pow(1 - beta, 2) / 24 * alpha * alpha / A 
                    + 0.25 * rho * beta * nu * alpha / pow(A, 0.5) 
                    + (2 - 3 * rho * rho) / 24 * nu * nu) * T;
    double sigma = (alpha / A) * (z / x) * B;
    return sigma;
}

int main() {
    // Example market data
    std::vector<double> strikes{0.95, 1.00, 1.05}; // Strike prices
    double forward = 1.30; // Current forward FX rate
    double expiry = 1; // Time to expiry in years
    double riskFreeRate = 0.05; // Risk-free interest rate
    double alpha = 0.2; // SABR alpha parameter
    double beta = 0.5; // SABR beta parameter
    double rho = -0.3; // SABR rho parameter
    double nu = 0.4; // SABR nu parameter

    // Print headers
    std::cout << "Strike\tBS Call Price\tImplied Volatility" << std::endl;

    // Calculate prices
    for (double strike : strikes) {
        double impliedVol = sabr_volatility(strike, forward, expiry, alpha, beta, rho, nu);
        double bsPrice = black_scholes_call(forward, strike, riskFreeRate, impliedVol, expiry);
        std::cout << strike << "\t" << bsPrice << "\t\t" << impliedVol << std::endl;
    }

    return 0;
}
