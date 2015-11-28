#ifndef DATA_H_PAGNMEPF
#define DATA_H_PAGNMEPF

#include <vector>
#include <string>

// Le type représentant les employés (ce ne sont que des int).
typedef int employee_t;

// Le type servant a representer les animaux (ils sont représenté par leur 
// contribution a la charge de travail.)
typedef int animal_contrib_t;

// Le type représentant les écosystemes sont une liste d'animaux.
//typedef std::vector<animal_contrib_t> ecosystem_t;
typedef struct ecosystem_t  {
    std::vector<animal_contrib_t> eco;
    int id;
} ecosystem_t;

struct ProblemData {
    // Le nombre d'employés.
    int nb_employee = -1;
    // La liste des écosystemes.
    std::vector<ecosystem_t> ecosystem;

    // Methode pour afficher les données du probleme dans un flux.
    void print(std::ostream& out) const;
};

/// Lit un fichier contenant les données du probleme et retourne un objet 
/// contenant ces données.
ProblemData make_problem_data(const std::string& filename);

#endif /* end of include guard: DATA_H_PAGNMEPF */
