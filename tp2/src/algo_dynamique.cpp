
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

        
        T get(U i, const key_t& key) {
            // Si le nombre d'item est nul.
            if(i == 0) {
                return 0;
            }

            // Si le nombre de boite est nul.
            if(std::all_of(key.begin(), key.end(), [](int ki) { return ki == 0; })) {
                return 0;
            }
           
            auto it = m_data.find(key);

            return *it;
        }
        
        void set(U i, const key_t& key, T value) {
            m_data[key] = value; 
        }

    private:

        map<key_t, T> m_data;
};


void mise_en_boite_dynamique(exemplaire* e) {
    for(int i = 0; i < e->nb_element; ++i) {
        for (int j = 0; j < e->nb_box; ++j) {

        }
    }
}
