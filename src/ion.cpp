#include <vector>

using namespace std;


class Ion: public std::vector<double>{
private:
    double fvalue;
    bool cation;

public:
    Ion(std::vector<double> position, bool cation) : vector(position){
        this->cation = cation;
        this->fvalue = fitness(position);
    }
};
