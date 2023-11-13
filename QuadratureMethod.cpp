#include <iostream>
#include <cmath>
#include <functional>

// Function to calculate the payoff of a European call option
double call_payoff(double S, double K) {
    return std::max(S - K, 0.0);
}

// Function to calculate the Black-Scholes analytical price of a European call option
double black_scholes_call_price(double S0, double K, double r, double sigma, double T) {
    double d1 = (std::log(S0 / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return S0 * 0.5 * std::erfc(-d1 / std::sqrt(2)) - K * exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
}

// Function to perform numerical integration using Simpson's Rule
double simpsons_rule(std::function<double(double)> func, double a, double b, int n) {
    double h = (b - a) / n;
    double k = 0.0;
    double x = a + h;
    
    for (int i = 1; i < n / 2; ++i) {
        k += 4 * func(x);
        x += 2 * h;
    }

    x = a + 2 * h;

    for (int i = 1; i < n / 2 - 1; ++i) {
        k += 2 * func(x);
        x += 2 * h;
    }

    return (h / 3) * (func(a) + func(b) + k);
}

int main() {
    double S0 = 1.0; // Spot price of the underlying FX rate
    double K = 1.1; // Strike price
    double r = 0.05; // Risk-free interest rate
    double sigma = 0.2; // Volatility of the underlying FX rate
    double T = 1.0; // Time to maturity in years
    int n = 10000; // Number of subintervals for Simpson's Rule

    // Define the range for integration - for numerical purposes, it's finite and typically a few standard deviations out
    double s_min = K / 3; // Arbitrarily chosen lower bound for integration
    double s_max = K * 3; // Arbitrarily chosen upper bound for integration

    // Define the integrand function using the risk-neutral valuation formula
    auto integrand = [S0, K, r, sigma, T](double S) {
        double d1 = (log(S0 / S) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
        double d2 = d1 - sigma * sqrt(T);
        double pdf = exp(-0.5 * d1 * d1) / (sigma * sqrt(2 * M_PI * T));
        return call_payoff(S, K) * pdf * exp(-r * T);
    };

    // Estimate the option price using Simpson's Rule quadrature
    double option_price = simpsons_rule(integrand, s_min, s_max, n);

    std::cout << "The estimated price of the FX option using quadrature is " << option_price << std::endl;
    std::cout << "The Black-Scholes analytical price is " << black_scholes_call_price(S0, K, r, sigma, T) << std::endl;

    return 0;
}
