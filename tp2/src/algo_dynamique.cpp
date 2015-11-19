#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <map>
#include <deque>
#include <stdexcept>

#include "algo_dynamique.h"
#include "utils.h"

using std::map;
using std::vector;
using std::pair;
using std::make_pair;

using std::cout;
using std::endl;

// Un tableau éparse, spécialisé pour ce probleme.
template<typename T>
class SparseTable {
    public:
        // Types
        typedef vector<int> key_t;
        typedef pair<key_t, T> backtrack_element_t;

        // Ctor
        SparseTable(int m, int c, int n): m(m), c(c) {
            m_data.resize(n+1);
            backtrack_info.resize(n+1);
        }
       
        // On vérifie que la clé correspond a une combinaisons valide selon les parametre du probleme.
        bool valid_key_p(const key_t& key) const {
            if(key.size() != c+1) {
                return false;
            }

            int j = 0;
            int sum = 0;
            for(auto mu : key) {
                if(mu < 0 || sum > m*c)
                    return false;
                sum += mu * j;
                ++j;
            }
            return true;
        }

        // Get values from the table
        T get(int i, const key_t& key) const {
            // Si le nombre d'item est nul.
            if(i == 0) {
                return 0;
            }

            if(i < 0 || !valid_key_p(key)) {
                return -1;
            }

            auto it = m_data[i].find(key);
            if(it == m_data[i].end()) {
                throw std::logic_error("[SparseTable::get] Tried to access uninitialized value.");
            }
            return it->second;
        }
        
        // Set values in the table.
        void set(int i, const key_t& key, T value) {
            m_data[i][key] = value; 
        }

        T compute_max_volume(int i, T volume, const key_t& key) {
            // Valeur si on ne met pas l'objet i.
            T max = get(i-1, key);
            vector<int> key2(key.size());

            // print(key, cout, true);
            T chosen_k = 0;
            vector<int> chosen_key;
            chosen_key.resize(key.size());
            std::copy(key.begin(), key.end(), chosen_key.begin());
           
            // Valeur si on met l'objet dans une boite de capacite k
            for(T k = volume; k < c+1; ++k) {
                // S'il y a une boite de capacite k.
                if(key[k] > 0) {
                    // On copy la clef courante.
                    std::copy(key.begin(), key.end(), key2.begin());
                    
                    /// On modifie la clef (i.e. on met l'objet dans la boite et on recalcule les capacites).
                    // Il y a une boite de capacite k de moins.
                    key2[k] -= 1;
                    // Et une boite de capacite (k-volume) de plus.
                    key2[k-volume] += 1;
                    
                    int value = volume + get(i-1, key2);
                    if( value > max ) {
                        max = value;
                        chosen_k = k;
                        std::copy(key2.begin(), key2.end(), chosen_key.begin());
                    }
                }
            }
            backtrack_info[i][key] = make_pair(chosen_key, chosen_k);
            
            return max;
        }


        vector<map<key_t, backtrack_element_t>> backtrack_info;

        void dump_data(std::ostream& out) {
            int i = 0;
            for(auto it: m_data) {
                out << i << endl;
                for(auto j: it) {
                    out << "\t" << j.second << " ";
                }
                ++i;
            }
            out << endl;
        }
        
    private:
        vector<map<key_t, T>> m_data;
        // vector<
        int m;
        int c;
};


void fill_table(exemplaire* e, SparseTable<int>& v) {
    int col_size = e->capacity + 1;
    auto keygen = Combinatoric_generator(e->nb_box, col_size);
    vector<int> key(col_size);

    // Pour chaque objet.
    for(int i = 1; i <= e->data.size(); ++i) {
        // std::cerr << "." << std::flush;
        unsigned volume = e->data[i-1];
        
        keygen.reinitialize();
        keygen.get_in_place(key);

        int count = 1;
        // print(key, cout, true);
       
        // Pour chaque clef
        do {
            // Arret premature
            if(is_timeout(e))
                exit_timeout();
            int max = v.compute_max_volume(i, volume, key);
            v.set(i, key, max);

            keygen.get_in_place(key);
            ++count;
            // cout << "\t" << count << endl;
            // print(key, cout, true);
        } while(keygen.next());

        int max = v.compute_max_volume(i, volume, key);
        v.set(i, key, max);

        /*cout << "V(" << i << ", (";
        print(key, cout, false);
        cout << ") " << i << endl;*/
    }
}

void find_solution(exemplaire* e, const SparseTable<int>& v) {
    vector<int> key(e->capacity + 1);
    std::fill(key.begin(), key.end(), 0);
    key[key.size()-1] = e->nb_box;        
    //print(key, cout, true);
    
    vector<int> box_capacity(e->nb_box, e->capacity);
    e->result.resize(e->nb_box);

    int i = e->nb_element;
    while(true) {
        // Arret premature
        if(is_timeout(e))
            exit_timeout();

        // Retreive backtrack information.
        auto it = v.backtrack_info[i].find(key);
        if(it == v.backtrack_info[i].end()) {
            break;
        }
        const SparseTable<int>::backtrack_element_t& be = it->second;
        auto chosen_key = be.first;
        int chosen_k = be.second;

        // Si l'objet a été mit dans une boite de capacité k.
        if(chosen_k > 0) {
            //cout << "key1: ";
            //print(key, cout, true);
            //cout << "chosen_key: ";
            //print(chosen_key, cout, true);
            //print(box_capacity, cout, true);

            auto it2 = box_capacity.begin();
            int j = 0;
            while(it2 != box_capacity.end()) {
                if(*it2 == chosen_k) {
                    break;
                }
                ++j;
                ++it2;
            }
            // On soustrait le volume de l'objet courant a la capacite de la boite.
            int volume = e->data[i-1];
            *it2 -= volume;
            /*cout << "Element " << i << "(v=" << volume << ") was put in (chosen_k=" << chosen_k 
                << ") " << j << "\n" << endl;*/
            e->result[j].push_back(volume);
        }
        --i;
        key = chosen_key;

        // Fail-safe
        if(i < -10) {
            break;
        }
    }
}

void mise_en_boite_dynamique(Options& options) {
    exemplaire* e = options.get_exemplaire();
    int m = e->nb_box;
    int c = e->capacity;

    // Estimation de la quantite de memoire qui serait necessaire.
    double numerator = factorial<double>(m + c);
    double denumerator = factorial<double>(m)*factorial<double>(c);
    double rat = numerator/denumerator;
    if(rat > 5e8) {
        // On bail-out quand on croit que c'est trop gros.
        throw std::out_of_range("This is too much.");
    }

    // Initialisation du tableau
    SparseTable<int> v(e->nb_box, e->capacity, e->nb_element);
    fill_table(e, v);

    //v.dump_data(cout);
    //return;

    // On calcul le contenue des boites en parcourant le tableau.
    find_solution(e, v);

}
