#ifndef OPTION_PARSE_H
#define OPTION_PARSE_H

#include "exemplaire_struct.h"

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


#endif /* end of include guard: OPTION_PARSE_H */

