#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// Function to generate a random path for the underlying asset price
std::vector<double> generate_asset_price_path(double S0, double mu, double sigma, double T, int steps) {
    std::vector<double> asset_prices(steps + 1);
    double dt = T / steps;
    double drift = (mu - 0.5 * sigma * sigma) * dt;
    double vol = sigma * sqrt(dt);
    
    // Standard mersenne_twister_engine seeded with rd()
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    asset_prices[0] = S0;

    for (int i = 1; i <= steps; ++i) {
        double z = d(gen);
        asset_prices[i] = asset_prices[i - 1] * exp(drift + vol * z);
    }
    return asset_prices;
}

// Function to estimate the price of the FX derivative using Monte Carlo simulation
double monte_carlo_pricing(double S0, double K, double T, double mu, double sigma, int num_paths, int steps) {
    double payoff_sum = 0.0;

    for (int i = 0; i < num_paths; ++i) {
        std::vector<double> asset_path = generate_asset_price_path(S0, mu, sigma, T, steps);
        double payoff = std::max(asset_path.back() - K, 0.0); // European Call Option Payoff
        payoff_sum += payoff;
    }

    double discount_factor = exp(-mu * T); // Assuming risk-free rate = mu for simplicity
    return (payoff_sum / num_paths) * discount_factor;
}

int main() {
    double S0 = 1.0; // Initial FX rate, e.g., EUR/USD 1.0
    double K = 1.1; // Strike price
    double T = 1.0; // Time to maturity in years
    double mu = 0.05; // Drift rate
    double sigma = 0.2; // Volatility
    int num_paths = 10000; // Number of simulated paths
    int steps = 365; // Number of steps in the path

    double option_price = monte_carlo_pricing(S0, K, T, mu, sigma, num_paths, steps);
    std::cout << "The estimated price of the FX option is " << option_price << std::endl;

    return 0;
}
