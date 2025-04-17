#include <iostream>
#include <limits>
#include <cmath>
#include "random_shuffle.hpp"

class IStatistics {
public:
    virtual ~IStatistics() = default;

    virtual void update(double next) = 0;

    virtual double eval() const = 0;

    virtual const char *name() const = 0;
};

class Min : public IStatistics {
public:
    Min() : m_min{std::numeric_limits<double>::max()} {
    }

    void update(const double next) override {
        // std::cout << ", " << next << std::endl;
        if (next < m_min) {
            m_min = next;
        }
    }

    double eval() const override {
        return m_min;
    }

    const char *name() const override {
        return "Min";
    }

private:
    double m_min;
};

class Max : public IStatistics {
public:
    Max() : m_max{std::numeric_limits<double>::min()} {
    }

    void update(const double next) override {
        if (next > m_max) {
            m_max = next;
        }
    }

    double eval() const override {
        return m_max;
    }

    const char *name() const override {
        return "Max";
    }

private:
    double m_max;
};

class Mean : public IStatistics {
public:
    Mean() : m_sum(0.0), m_count(0) {
    }

    void update(const double next) override {
        m_sum += next;
        m_count++;
    }

    double eval() const override {
        return m_sum / static_cast<double>(m_count);
    }

    const char *name() const override {
        return "Mean";
    }

private:
    double m_sum;
    size_t m_count;
};

class StdDev : public IStatistics {
    /* Welford’s method for computing variance:
     * variance(samples):
     *   M := 0
     *   S := 0
     *   for k from 1 to N:
     *     x := samples[k]
     *     oldM := M
     *     M := M + (x-M)/k
     *     S := S + (x-M)*(x-oldM)
     *   return S/(N-1)
     *
     * If Standard Deviation is square root of variance, then:
     *   ...
     *   return sqrt(S/(N-1))
     */
public:
    StdDev() : m_count{0}, m_m{0.0}, m_s{0.0} {
    }

    void update(const double next) override {
        m_count++;
        double old_m = m_m;
        m_m += (next - old_m) / static_cast<double>(m_count);
        m_s += (next - m_m) * (next - old_m);
    }

    double eval() const override {
        // Handle the case of 0 or 1 samples
        if (m_count < 2) {
            return 0.0;
        }
        return std::sqrt(m_s / static_cast<double>(m_count - 1));
    }

    const char *name() const override {
        return "StdDev";
    }

private:
    size_t m_count; // Number of values
    double m_m; // Running mean
    double m_s; // Sum of squared differences
};
#include <vector>
#include <algorithm> // For std::sort

class Percentile90 : public IStatistics {
public:
    Percentile90() {
    }

    void update(const double next) override {
        // Store the new value
        m_values.push_back(next);
    }

    double eval() const override {
        if (m_values.empty()) {
            return 0.0;
        }

        // Make a copy to avoid modifying the original data during sort
        std::vector<double> sorted_values = m_values;
        std::sort(sorted_values.begin(), sorted_values.end());

        // Calculate the position for 90th percentile
        // For 90th percentile, we need the value at position: (n * 0.9)
        double position = sorted_values.size() * 0.9;

        // If position is an integer, take average of this and next value
        if (position == static_cast<int>(position)) {
            int idx = static_cast<int>(position);
            // Handle edge case where idx is the last element
            if (idx == sorted_values.size() - 1) {
                return sorted_values[idx];
            }
            return (sorted_values[idx] + sorted_values[idx + 1]) / 2.0;
        }

        // Otherwise, round up to next integer position
        return sorted_values[static_cast<int>(std::ceil(position)) - 1];
    }

    const char *name() const override {
        return "percentile_90";
    }

private:
    std::vector<double> m_values;
};

class FeedNext {
private:
    enum class InputMode {
        MANUAL, VECTOR
    };

    InputMode m_mode;
    std::vector<double> m_values;
    size_t m_index = 0;

public:
    FeedNext() : m_mode(InputMode::MANUAL) {}

    FeedNext(const std::vector<double> &values) : m_mode(InputMode::VECTOR), m_values(values) {}

    bool next(double& val) {
        if (m_mode == InputMode::MANUAL) {
            // double val;
            if (std::cin >> val) {
                return true;
            } else {
                return false;
            }
        }
        else {
            if (m_index >= m_values.size()) {
                return false;
            } else {
                val = m_values[m_index++];
                return true;
            }
        }
    }

    const std::vector<double> &values() const {
        return m_values;
    }
};

std::vector<double> random_val_generator(double min_val, double max_val, size_t val_count) {
    std::vector<double> m_values;

    // Pre-generate random values
    m_values.reserve(val_count);

    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_val, max_val);

    // Generate values
    for (int i = 0; i < val_count; ++i) {
        m_values.push_back(dis(gen));
    }
    return m_values;
}

int main(int argc, char* argv[]) {
    FeedNext* feeder;

    if (argc == 4) {
        double min_val = std::stod(argv[1]);
        double max_val = std::stod(argv[2]);
        int val_count = std::stoi(argv[3]);

        // Check if parameters are valid
        if (min_val >= max_val) {
            std::cerr << "Error: min_val must be less than max_val\n";
            return 1;
        }

        if (val_count <= 0) {
            std::cerr << "Error: val_count must be positive\n";
            return 1;
        }

        std::vector<double> values = random_val_generator(min_val, max_val, val_count);

        // Create feeder with the provided parameters
        feeder = new FeedNext(values);

    }
    else if (argc == 1) {
        feeder = new FeedNext();
        std::cout << "Enter values (Ctrl+D/Z to end):" << std::endl;
    }
    else {
        std::cerr << "Usage: " << argv[0] << " [<min_val> <max_val> <val_count>]\n";
        std::cerr << "  - With arguments: generates random values in the given range\n";
        std::cerr << "  - Without arguments: reads values from standard input\n";
        return 1;
    }

    const size_t statistics_count = 4;
    IStatistics *statistics[statistics_count];

    statistics[0] = new Min{};
    statistics[1] = new Max{};
    statistics[2] = new Mean{};
    statistics[3] = new StdDev{};

    double val = 0;
    while (feeder->next(val)) {
        std::cout << "(" << val << ")";
        for (size_t i = 0; i < statistics_count; ++i) {
            statistics[i]->update(val);
        }
    }

    // Handle invalid input data
    // if (!std::cin.eof() && !std::cin.good()) {
    //     std::cerr << "Invalid input data\n";
    //     return 1;
    // }

    // Print results if any
    for (size_t i = 0; i < statistics_count; ++i) {
        std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (size_t i = 0; i < statistics_count; ++i) {
        delete statistics[i];
    }

    return 0;
}
