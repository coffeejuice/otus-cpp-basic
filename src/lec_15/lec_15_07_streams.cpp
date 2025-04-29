#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


class IntType
{
public:
    IntType(int value):value_(value) {}

    friend std::ostream& operator<< (std::ostream& os, const IntType& it);

private:
    int value_;
};

int stdstyle()
{
    // 1
    std::cout << "Hello, world!\n";
    const std::string filename("testfile2.txt");
    
    std::ofstream ostr;
    ostr.open(filename);
    if (ostr) 
    {
        for (int i = 0; i < 16; i++) 
        {
            ostr << i*i << std::endl;
            if (ostr.bad()) 
            {
                std::cerr << "Unrecoverable write error" << std::endl;
                return 1;
            }
        }
        ostr.close();
    }
    else 
    {
        std::cerr << "Output file open error \"" << filename << "\"" << std::endl;
        return 1;
    }

    // 2.
    int data;
    int counter = 0;
    std::ifstream istr(filename);
    if (istr) 
    {
        while (!(istr >> data).eof()) 
        {
            if (istr.bad()) 
            {
                std::cerr << "Unrecoverable read error" << std::endl;
                return 2;
            }
            std::cout.width(8);
            std::cout << data;
            if (++counter % 4 == 0) 
            {
                std::cout << std::endl;
            }
        }
        istr.close();
    }
    else {
        std::cerr << "Input file open error \"" << filename << "\"" << std::endl;
        return 2;
    }

    return 0;
}

void format()
{
    int postalCode1 = 555555;
    std::string outString1{"Postal code is"};
    outString1 += " " + std::to_string(postalCode1);
    std::cout << outString1 << "\n";

    int postalCode2 = 123456789;
    std::stringstream stream2;
    stream2 << "Postal code is " << postalCode2;
    std::cout << stream2.str() << "\n";    
}

void inoutmanip()
{
    bool flag = true;
    std::cout << flag << std::endl;
    std::cout << std::boolalpha << flag << std::endl;

    float num = 1.1114234234f;
    std::cout << std::setprecision(3) << std::setw(10) << num << std::endl;
    std::cout << std::setprecision(3) << std::setw(10) << 123456l << std::endl;

    char prev = std::cout.fill ('.');
    const int n = 6;
    unsigned long v = 1;
    for (int i = 0; i < n; ++i)
    {
        v *= 10;
        std::cout << std::setw(15) << v << std::endl;
    }
    std::cout.fill(prev);

    std::cout << std::setw(14) << " done" << std::endl;
}

void stream_overload()
{
    IntType itp(10);
    std::cout << itp << std::endl;

}

void binary_io()
{
    class dataIO
    {
    public:
        dataIO():name_(), surname_(), age_(0)
        {
        }

        void input()
        {
            std::stringstream ss;
            ss << "Vasya";
            ss.getline(name_, 15);
            std::cout << name_ << std::endl;

            surname_ = "Ivanov";

            age_ = 123;
        }

        void to_file()
        {
            std::ofstream fs("example.bin", std::ios::out | std::ios::binary | std::ios::app);
            std::cout << sizeof name_ << std::endl;
            fs.write(name_, sizeof name_);
            fs.write(surname_.c_str(), surname_.size());
            fs.write(reinterpret_cast<const char*>(&age_), sizeof age_);
            fs.close();
        }

        void from_file()
        {
            std::ifstream fs("example.bin", std::ios::in | std::ios::binary);
            fs.read(name_, sizeof name_);

            const size_t n = 6;
            char buffer[10];
            fs.read(buffer, n);
            for (std::size_t i = 0; i < n; ++i)
                surname_[i] = buffer[i];

            fs.read(reinterpret_cast<char*>(&age_), sizeof age_);
            fs.close();

            std::cout << name_ << std::endl;
            std::cout << surname_ << std::endl;
            std::cout << age_ << std::endl;
        }        

    private: 
        char name_[15];
        std::string surname_;
        int age_;
    };

    dataIO data_io;
    
    data_io.input();
    data_io.to_file();
    data_io.from_file();
}

void f(int i)
{

    std::cout << i << std::endl;
}

int main()
{
    stdstyle();
    format();
    inoutmanip();
    stream_overload();
    binary_io();
   
    return 0;
}

std::ostream& operator<< (std::ostream& os, const IntType& it)
{
    return os << "(" << it.value_ << ", ";
}
