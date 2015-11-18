
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <map>

#include "algo_dynamique.h"

using std::map;
using std::vector;

// Un tableau éparse, spécialisé pour ce probleme.
template<typename T, typename U>
class SparseTable {
    public:
        typedef vector<int> key_t;


        SparseTable(int m, int c): m(m), c(c) {}

       
        // On vérifie que la clé correspond a une combinaisons valide selon les parametre du probleme.
        bool valid_key_p(const key_t& key) {
            int j = 0;
            int count = 0;
            int sum = 0;
            for(auto mu : key) {
                if(mu < 0)
                    return false;
                count += mu;
                sum += mu * j;
            }
            if(count != m || sum > m*c) {
                return false;
            }
            return true;
        }

        T get(U i, const key_t& key) {
            // Si le nombre d'item est nul.
            if(i == 0) {
                return 0;
            }

            if(i < 0 || !valid_key_p(key)) {
                return -1;
            }

            // Si la capacité est nulle?
           
            auto it = m_data.find(key);

            return *it;
        }
        
        void set(U i, const key_t& key, T value) {
            m_data[key] = value; 
        }

    private:

        map<key_t, T> m_data;
        int m;
        int c;
};

void mise_en_boite_dynamique(exemplaire* e) {
    SparseTable<int, int> v(e->nb_box, e->capacity);

    mu_iterator mi(e->nb_box, e->capacity);
    // mi.print(std::cout);
    int count = 0;
    while(mi.next()) {
        auto key = mi.get();
        // mi.print(std::cout);
        // std::cout << std::endl;
        if( v.valid_key_p(key) ) {
            ++count;
            std::cout << "Count: " << count << std::endl;
        }
    }
    std::cout << "Count: " << count << std::endl;

/*    for(auto volume : e->data) {
        for (int j = 0; j < e->nb_box; ++j) {
//            int opt1 = v.get(volume, );

        }
    }
*/
}
