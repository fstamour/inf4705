#ifndef OPTION_PARSE_H
#define OPTION_PARSE_H

#include "exemplaire_struct.h"

struct recuit_simule_args;

struct Options
{
public:
    // Convention: *_p  -> predicate -> boolean
    // Pas besoin de chercher pour un verbe (e.g. isVerboseOn)
    bool verbose_p = false;
    char *filename = nullptr;

    void initialize(int argc, char** argv);

    struct exemplaire* getExemplaire() const {
        return make_exemplaire(filename);
    }


    virtual ~Options();
};

struct RecuitOptions : public Options {
    struct recuit_simule_args initialize(int argc, char** argv);
};

struct recuit_simule_args {
    //nombre de pas maximal
    int k_max;
    // temperature initial
    float t;
    //palier de refroidissement
    int p;
    // coefficient de refroidissement
    float a;
};


#endif /* end of include guard: OPTION_PARSE_H */

