#ifndef STATS_H_7QPZDO9B
#define STATS_H_7QPZDO9B

#include <ostream>
#include <string>
#include <cmath>
#include <vector>

// Brainstorm:
// count, avg, variance(standard deviation), mode

template<
    // Le type que les données ont.
    typename data_t = int,
    // Le type avec lequelle on fait les calculs.
    typename comp_t = float
>
class Stats {
    // Le nombre d'element.
    comp_t n = 0;
    comp_t sum = 0;
    comp_t mean = 0;

    // Utilisé pour calcule la variance.
    comp_t sum_of_squares = 0;

public:

    void add_data(const data_t& d) {
        ++n;
        sum += d;
        sum_of_squares += d*d;
        mean = sum/n;
    }

    void add_data(const std::vector<data_t>& data) {
        for(auto datum : data) { add_data(datum); }
    }

    void remove_data(const data_t d) {
        if(n = 0) {
            throw std::logic_error("[Stats] Removed more data than added.");
        }
        --n;
        sum -= d;
        sum_of_squares -= d*d;
        mean = sum/n;
    }

    void remove_data(const std::vector<data_t>& data) {
        for(auto datum : data) { remove_data(datum); }
    }

    void reset() {
        n = 0;
        sum = 0;
        mean = 0;
    }

    comp_t get_n() const { return n; }
    comp_t get_sum() const { return sum; }
    comp_t get_mean() const { return mean; }
    comp_t get_variance() const {
        // Shouldn't happen...
         /*if(n == 0){
             return std::numeric_limits<comp_t>::max();
         }*/
        return sum_of_squares/n - mean*mean; }
    comp_t get_std_deviation() const { return sqrt(get_variance()); }

    void print_summary(std::ostream& out, const std::string& title = "") {
        if(title.size()) {
            out << title << "\n";
	    // "Soulignement" du titre
            for(size_t i = 0; i < title.size(); ++i) {
                out << "-";
            }
            out << "\n";
        }
        out << "N:         " << n << "\n";
        out << "Sum:       " << sum << "\n";
        out << "Mean:      " << mean << "\n";
        out << "Std. Dev.: " << get_std_deviation() << "\n";
    }

};


#endif /* end of include guard: STATS_H_7QPZDO9B */
