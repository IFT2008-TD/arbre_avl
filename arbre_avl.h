//
// Created by Pascal Charpentier on 2022-06-23.
//

#ifndef ARBRE_AVL_ARBRE_AVL_H
#define ARBRE_AVL_ARBRE_AVL_H

template<typename C, typename V>
class Arbre_AVL {

private:        // Type privé

    struct Arbre {
        C      cle ;
        V      valeur ;
        Arbre *gauche ;
        Arbre *droite ;

        int    hauteur ;

        explicit Arbre(C c, V v) : cle(c), valeur(v), gauche(nullptr), droite(nullptr), hauteur(0) {} ;
    };

public:             // Interface

                    Arbre_AVL() ;
                    Arbre_AVL(const Arbre_AVL<C, V>& source) ;
    Arbre_AVL<C, V>&   operator = (Arbre_AVL<C, V> rhs) ;
                    ~Arbre_AVL() ;

    bool            vide () const ;
    size_t          cardinal () const ;

    void            effacer () ;
    const V&        rechercher(const C& cle) const ;
    void            inserer(const C& cle, const V& valeur) ;
    void            supprimer (const C& cle) ;

private:            // Méthodes auxiliaires d'un arbre binaire de tri

    size_t          aux_compter(Arbre* root) const ;
    void            aux_inserer(const C& cle, const V& valeur, Arbre*& root) ;
    const V&        aux_rechercher(const C& cle, Arbre* root) const ;
    void            aux_effacer (Arbre*& root) ;
    void            aux_supprimer (const C& cle, Arbre*& root) ;
    void            aux_retirer_noeud(Arbre*& root) ;
    void            aux_transplanter(Arbre*& enfant, Arbre*& parent) ;
    void            aux_couper_feuille(Arbre*& root) ;
    Arbre*          aux_copier(Arbre *root) ;

private:        // Méthodes auxiliaires d'un arbre AVL

    int         aux_hauteur(Arbre* root) const ;
    void        mise_a_jour_hauteur(Arbre* root) ;
    void        equilibrer_le_sous_arbre_avl(Arbre* root) ;
    int         facteur_equilibre_du_sous_arbre(Arbre* root) const ;
    void        rotation_vers_la_droite(Arbre*& root) ;
    void        rotation_vers_la_gauche(Arbre*& root) ;

private:        // Contrat

    bool        sous_arbre_est_inferieur_a(const C& cle, Arbre* root) const ;
    bool        sous_arbre_est_superieur_a(const C& cle, Arbre* root) const ;
    bool        sous_arbre_est_valide(Arbre* root) const ;
    bool        arbre_est_valide() const ;
    bool        sous_arbre_est_avl(Arbre* root) const ;
    bool        arbre_est_avl() const ;
    bool        invariant() const ;

private:
    Arbre *racine ;
};

template<typename C, typename V>
Arbre_AVL<C, V>::Arbre_AVL() : racine(nullptr) {

}

template<typename C, typename V>
bool Arbre_AVL<C, V>::vide() const {
    return racine == nullptr ;
}

template<typename C, typename V>
size_t Arbre_AVL<C, V>::cardinal() const {
    return aux_compter(racine) ;
}

template<typename C, typename V>
size_t Arbre_AVL<C, V>::aux_compter(Arbre_AVL::Arbre *root) const {
    if (!root) return 0 ;
    return 1 + aux_compter(root->gauche) + aux_compter(root->droite) ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::inserer(const C &cle, const V& valeur) {
    aux_inserer(cle, valeur, racine) ;
    assert(invariant()) ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_inserer(const C& cle, const V& valeur, Arbre*& root) {
    if (!root) root = new Arbre(cle, valeur) ;
    else if (cle < root->cle) aux_inserer(cle, valeur, root->gauche) ;
    else if (cle > root->cle) aux_inserer(cle, valeur, root->droite) ;

    else throw std::runtime_error("insertion: duplication de clé") ;

    mise_a_jour_hauteur(root) ;
    equilibrer_le_sous_arbre_avl(root) ;
}

template<typename C, typename V>
const V &Arbre_AVL<C, V>::rechercher(const C &cle) const {
    return  aux_rechercher(cle, racine) ;
}

template<typename C, typename V>
const V &Arbre_AVL<C, V>::aux_rechercher(const C &cle, Arbre_AVL::Arbre *root) const {
    if (!root) throw std::runtime_error("Clé introuvable dans l'arbre.") ;

    if (cle < root->cle) return aux_rechercher(cle, root->gauche) ;
    if (cle > root->cle) return aux_rechercher(cle, root->droite) ;
    return root->valeur ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_effacer(Arbre_AVL::Arbre*& root) {
    if (!root) return ;

    aux_effacer(root->gauche) ;
    aux_effacer(root->droite) ;

    delete root ;
    root = nullptr ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::effacer() {
    aux_effacer(racine) ;
}

template<typename C, typename V>
Arbre_AVL<C, V>::~Arbre_AVL() {
    effacer() ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::supprimer(const C &cle) {
    aux_supprimer(cle, racine) ;
    assert(invariant()) ;

}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_supprimer(const C &cle, Arbre_AVL::Arbre*& root) {
    if (!root) throw std::runtime_error("suppression: clé absente") ;

    if (cle > root->cle) aux_supprimer(cle, root->droite) ;
    else if (cle < root->cle) aux_supprimer(cle, root->gauche) ;
    else aux_retirer_noeud(root) ;

    if (root) mise_a_jour_hauteur(root) ;
    equilibrer_le_sous_arbre_avl(root) ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_retirer_noeud(Arbre_AVL::Arbre*& root) {

    if (!root->droite)  {
        if (!root->gauche) aux_couper_feuille(root) ;
        else aux_transplanter(root->gauche, root) ;
    }
    else if (!root->gauche) aux_transplanter(root->droite, root) ;
    else {
        auto& pred = root->gauche ;
        while (pred->droite) pred = pred->droite ;
        root->cle = pred->cle ;
        root->valeur = pred->valeur ;
        if (!pred->gauche) aux_couper_feuille(pred) ;
        else aux_transplanter(pred->gauche, pred) ;
    }
}

template<typename C, typename V>
Arbre_AVL<C, V>::Arbre_AVL(const Arbre_AVL<C, V> &source) : racine(aux_copier(source.racine)) {

}

template<typename C, typename V>
typename Arbre_AVL<C, V>::Arbre*
Arbre_AVL<C, V>::aux_copier(Arbre_AVL::Arbre *root) {
    if (!root) return ;

    auto* retval = new Arbre(root->cle, root->valeur) ;
    retval->gauche = aux_copier(root->gauche) ;
    retval->droite = aux_copier(root->droite) ;
    return retval ;
}

template<typename C, typename V>
Arbre_AVL<C, V> &Arbre_AVL<C, V>::operator=(Arbre_AVL<C, V> rhs) {
    std::swap(racine, rhs.racine) ;
    return *this ;
}

template<typename C, typename V>
int Arbre_AVL<C, V>::aux_hauteur(Arbre* root) const {
    if (!root) return -1 ;

    return 1 + std::max(aux_hauteur(root->gauche), aux_hauteur(root->droite)) ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::rotation_vers_la_droite(Arbre_AVL::Arbre*& root) {
    auto& new_root = root->droite ;
    if (new_root->gauche) root->droite = new_root->gauche ;
    new_root->gauche = root ;
    root = new_root ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::rotation_vers_la_gauche(Arbre_AVL::Arbre*& root) {
    auto& new_root = root->gauche ;
    if (new_root->droite) root->gauche = new_root->droite ;
    new_root->droite = root ;
    root = new_root ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::mise_a_jour_hauteur(Arbre_AVL::Arbre *root) {
    root->hauteur = aux_hauteur(root) ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::equilibrer_le_sous_arbre_avl(Arbre_AVL::Arbre *root) {
    int facteur = facteur_equilibre_du_sous_arbre(root) ;
    if (facteur < 2) {
        if (facteur > -2) return ;

        if (facteur_equilibre_du_sous_arbre(root->gauche) <= 0) rotation_vers_la_droite(root) ;
        else {
            rotation_vers_la_gauche(root->gauche) ;
            rotation_vers_la_droite(root) ;
        }
    }
    else {
        if (facteur_equilibre_du_sous_arbre(root->droite) >= 0) rotation_vers_la_gauche(root) ;
        else {
            rotation_vers_la_droite(root->droite) ;
            rotation_vers_la_gauche(root) ;
        }
    }
}

template<typename C, typename V>
int Arbre_AVL<C, V>::facteur_equilibre_du_sous_arbre(Arbre_AVL::Arbre *root) const {
    if (!root) return 0 ;

    int h_gauche = root->gauche ? root->gauche->hauteur : -1 ;
    int h_droite = root->droite ? root->droite->hauteur : -1 ;
    return h_droite - h_gauche ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_valide(Arbre_AVL::Arbre *root) const {
    if (!root) return true ;

    bool valide_gauche ;
    if (root->gauche) valide_gauche = sous_arbre_est_inferieur_a(root->cle, root->gauche) && sous_arbre_est_valide(root->gauche) ;
    else  valide_gauche = true ;

    bool valide_droite ;
    if (root->droite) valide_droite = sous_arbre_est_superieur_a(root->cle, root->droite) && sous_arbre_est_valide(root->droite) ;
    else valide_droite = true ;

    return valide_gauche && valide_droite ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::arbre_est_valide() const {
    return sous_arbre_est_valide(racine) ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_avl(Arbre_AVL::Arbre *root) const {
    if (!root) return true ;
    int eq = facteur_equilibre_du_sous_arbre(root) ;
    return (eq < 2) && (eq > -2) && sous_arbre_est_avl(root->gauche) && sous_arbre_est_avl(root->droite) ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::arbre_est_avl() const {
    return sous_arbre_est_avl(racine) ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::invariant() const {
    return arbre_est_avl() && arbre_est_valide() ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_transplanter(Arbre_AVL::Arbre*& enfant, Arbre_AVL::Arbre *&parent) {
    parent->cle = enfant->cle ;
    parent->valeur = enfant->valeur ;
    parent->gauche = enfant->gauche ;
    parent->droite = enfant->droite ;
    delete enfant ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_couper_feuille(Arbre_AVL::Arbre *&root) {
    delete root ;
    root = nullptr ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_inferieur_a(const C &cle, Arbre_AVL::Arbre *root) const {
    if (!root) return true ;
    return (root->cle < cle) && sous_arbre_est_inferieur_a(cle, root->gauche) && sous_arbre_est_inferieur_a(cle, root->droite);
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_superieur_a(const C &cle, Arbre_AVL::Arbre *root) const {
    if (!root) return true ;
    return (root->cle > cle) && sous_arbre_est_superieur_a(cle, root->gauche) && sous_arbre_est_superieur_a(cle, root->droite) ;

}


#endif //ARBRE_AVL_ARBRE_AVL_H
