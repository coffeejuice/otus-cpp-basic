#include <iostream>
#include <limits>
#include <cmath>
#include <map>
#include <random>
#include <vector>
#include <algorithm> // For std::sort

class IStatistics
{
public:
    virtual ~IStatistics() = default;

    virtual void update(double next) = 0;

    virtual double eval() const = 0;

    virtual const char* name() const = 0;
};

class Min : public IStatistics
{
public:
    Min() : m_min{std::numeric_limits<double>::max()}
    {
    }

    void update(const double next) override
    {
        // std::cout << ", " << next << std::endl;
        if (next < m_min)
        {
            m_min = next;
        }
    }

    double eval() const override
    {
        return m_min;
    }

    const char* name() const override
    {
        return "Min";
    }

private:
    double m_min;
};

class Max : public IStatistics
{
public:
    Max() : m_max{std::numeric_limits<double>::min()}
    {
    }

    void update(const double next) override
    {
        if (next > m_max)
        {
            m_max = next;
        }
    }

    double eval() const override
    {
        return m_max;
    }

    const char* name() const override
    {
        return "Max";
    }

private:
    double m_max;
};

class Mean : public IStatistics
{
public:
    Mean() : m_sum(0.0), m_count(0)
    {
    }

    void update(const double next) override
    {
        m_sum += next;
        m_count++;
    }

    double eval() const override
    {
        return m_sum / static_cast<double>(m_count);
    }

    const char* name() const override
    {
        return "Mean";
    }

private:
    double m_sum;
    size_t m_count;
};

class StdDev : public IStatistics
{
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
    enum class Type { Sample, Population };

    StdDev(Type type = Type::Sample) :
        m_count{0},
        m_m{0.0},
        m_s{0.0},
        m_type{type},
        m_name{type == Type::Sample ? "StdDev" : "StdDevPopulation"}
    {
    }

    void update(const double next) override
    {
        m_count++;
        double old_m = m_m;
        m_m += (next - old_m) / static_cast<double>(m_count);
        m_s += (next - m_m) * (next - old_m);
    }

    double eval() const override
    {
        // Handle the case of 0 or 1 samples
        if (m_count == 0)
        {
            return 0.0;
        }
        if (m_type == Type::Sample)
        {
            if (m_count == 1)
            {
                return 0.0;
            }
            return std::sqrt(m_s / static_cast<double>(m_count - 1));
        }
        else
        {
            return std::sqrt(m_s / static_cast<double>(m_count));
        }
    }

    const char* name() const override
    {
        return m_name.c_str();
    }

private:
    size_t m_count; // Number of values
    double m_m; // Running mean
    double m_s; // Sum of squared differences
    Type m_type; // Type of standard deviation to calculate
    std::string m_name; // Name of the statistic
};


class Percentile : public IStatistics
{
public:
    Percentile(int const percentile) :
        m_percentile(percentile),
        m_name("Percentile" + std::to_string(percentile)) // Initialize m_name in constructor
    {
    }

    void update(const double next) override
    {
        m_values.push_back(next);
    }

    double eval() const override
    {
        if (m_values.empty())
        {
            return 0.0;
        }
        std::vector<double> sorted_values = m_values;
        std::sort(sorted_values.begin(), sorted_values.end());
        const double position = sorted_values.size() * m_percentile / 100.0;
        return sorted_values[static_cast<int>(std::ceil(position)) - 1];
    }

    const char* name() const override
    {
        return m_name.c_str(); // Simply return the pre-calculated name
    }

private:
    std::vector<double> m_values;
    int m_percentile;
    std::string m_name; // New member variable to store the name
};

class FeedNext
{
private:
    enum class InputMode
    {
        MANUAL, VECTOR
    };

    InputMode m_mode;
    std::vector<double> m_values;
    size_t m_index = 0;

public:
    FeedNext() : m_mode(InputMode::MANUAL)
    {
    }

    FeedNext(const std::vector<double>& values) : m_mode(InputMode::VECTOR), m_values(values)
    {
    }

    bool next(double& val)
    {
        if (m_mode == InputMode::MANUAL)
        {
            // double val;
            if (std::cin >> val)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (m_index >= m_values.size())
            {
                return false;
            }
            else
            {
                val = m_values[m_index++];
                return true;
            }
        }
    }

    const std::vector<double>& values() const
    {
        return m_values;
    }
};

std::vector<double> random_val_generator(double min_val, double max_val, size_t val_count)
{
    std::vector<double> m_values;

    // Pre-generate random values
    m_values.reserve(val_count);

    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_val, max_val);

    // Generate values
    for (int i = 0; i < val_count; ++i)
    {
        m_values.push_back(dis(gen));
    }
    return m_values;
}

int main(int argc, char* argv[])
{
    std::string path(argv[0]);
    size_t pos = path.find_last_of("/\\");
    std::string exeName = (pos != std::string::npos) ? path.substr(pos + 1) : path;

    // Print help information
    std::cout << "Help:\n    Usage: " << (argc > 0 ? exeName : "stats") << "\n"
        << "           " << (argc > 0 ? exeName : "stats") << " <min> <max> <count>\n\n"
        << "    Options:\n"
        << "       (no arguments)     Read numbers from standard input\n"
        << "       <min> <max> <count>  Generate random numbers where:\n"
        << "         <min>   - Minimum value for generated numbers\n"
        << "         <max>   - Maximum value for generated numbers\n"
        << "         <count> - How many numbers to generate\n\n"
        << "    Example:\n"
        << "      " << (argc > 0 ? exeName : "stats") << "         # Read from standard input\n"
        << "      " << (argc > 0 ? exeName : "stats") << " 1 100 5 # Generate 5 numbers between 1 and 100\n";


    // Make feeder, depends on command line arguments
    //
    FeedNext* feeder;

    if (argc == 4)
    {
        double min_val = std::stod(argv[1]);
        double max_val = std::stod(argv[2]);
        int val_count = std::stoi(argv[3]);

        // Check if parameters are valid
        if (min_val >= max_val)
        {
            std::cerr << "Error: min_val must be less than max_val\n";
            return 1;
        }

        if (val_count <= 0)
        {
            std::cerr << "Error: val_count must be positive\n";
            return 1;
        }
        std::vector<double> values = random_val_generator(min_val, max_val, val_count);
        feeder = new FeedNext(values);
        std::cout << "\nGenerated random values: " << std::endl;
        for (double const& value : values)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    else if (argc == 1)
    {
        feeder = new FeedNext();
        std::cout << "Enter values (Ctrl+D/Z to end):" << std::endl;
    }
    else
    {
        std::cerr << "Wrong arguments" << std::endl;
        return 1;
    }

    // Create statistics objects
    //
    const size_t statistics_count = 7;
    IStatistics* statistics[statistics_count];

    statistics[0] = new Min{};
    statistics[1] = new Max{};
    statistics[2] = new Mean{};
    statistics[3] = new StdDev{StdDev::Type::Sample};
    statistics[4] = new StdDev{StdDev::Type::Population};
    statistics[5] = new Percentile{90};
    statistics[6] = new Percentile{95};

    // Update statistics objects with values from feeder
    //
    double val = 0;
    while (feeder->next(val))
    {
        for (size_t i = 0; i < statistics_count; ++i)
        {
            statistics[i]->update(val);
        }
    }

    std::cout << std::endl;

    // Print results if any
    //
    std::cout << "Results:" << std::endl;
    for (size_t i = 0; i < statistics_count; ++i)
    {
        std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (size_t i = 0; i < statistics_count; ++i)
    {
        delete statistics[i];
    }

    return 0;
}
