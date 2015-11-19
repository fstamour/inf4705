#ifndef OPTION_PARSE_H
#define OPTION_PARSE_H

#include "exemplaire_struct.h"

enum class Algo {
    dynamique,
    recuit_simule,
    vorace
};

class Options
{
public:
    // Convention: *_p  -> predicate -> boolean
    // Pas besoin de chercher pour un verbe (e.g. isVerboseOn)
    
    /// Options communne
    bool verbose_p = false;
    char *filename = nullptr;
    struct exemplaire * exemplaire = nullptr;

    /// Options specifique au recuit simule
    //nombre de pas maximal
    int k_max;
    // temperature initial
    float t;
    //palier de refroidissement
    int p;
    // coefficient de refroidissement
    float a;
        
    virtual void initialize(Algo algo, int argc, char** argv);
    virtual void initialize_recuit(int argc, char** argv);

    struct exemplaire* get_exemplaire() {
        if(exemplaire == nullptr) {
            exemplaire = make_exemplaire(filename);
        }
        return exemplaire;
    }

    virtual ~Options();
};


#endif /* end of include guard: OPTION_PARSE_H */

