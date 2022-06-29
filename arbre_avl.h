//
// Created by Pascal Charpentier on 2022-06-23.
//

#ifndef ARBRE_AVL_ARBRE_AVL_H
#define ARBRE_AVL_ARBRE_AVL_H

template<typename V>
class Arbre_AVL {
private:
    struct Arbre{
        V      cle ;
        Arbre *gauche ;
        Arbre *droite ;

        int    hauteur ;

        explicit Arbre(V v) : cle(v), gauche(nullptr), droite(nullptr), hauteur(0) {} ;
    };

public:

                    Arbre_AVL() ;
                    Arbre_AVL(std::initializer_list<V> l) ;
                    Arbre_AVL(const Arbre_AVL<V>& source) ;
    Arbre_AVL<V>&   operator = (Arbre_AVL<V> rhs) ;
                    ~Arbre_AVL() ;

    bool            vide () const ;
    size_t          cardinal () const ;

    void            effacer () ;
    const V&        rechercher(const V& cle) const ;
    void            inserer(const V& cle) ;
    void            supprimer (const V& cle) ;

private:
    size_t          aux_compter(Arbre* root) const ;
    void            aux_inserer(const V& cle, Arbre*& root) ;
    const V&        aux_rechercher(const V& cle, Arbre* root) const ;
    void            aux_effacer (Arbre* root) ;
    void            aux_supprimer (const V& cle, Arbre*& root) ;
    void            aux_retirer_noeud(Arbre*& root) ;
    void            aux_ecraser_noeud(Arbre*& root) ;
    Arbre*          aux_copier(Arbre *root) ;

private:
    int         aux_hauteur(Arbre* root) const ;
    void        mise_a_jour_hauteur(Arbre* root) ;
    void        equilibrer_le_sous_arbre_avl(Arbre* root) ;
    int         facteur_equilibre_du_sous_arbre(Arbre* root) const ;
    void        rotation_vers_la_droite(Arbre*& root) ;
    void        rotation_vers_la_gauche(Arbre*& root) ;

private:
    bool        sous_arbre_est_valide(Arbre* root) const ;
    bool        arbre_est_valide() const ;
    bool        sous_arbre_est_avl(Arbre* root) const ;
    bool        arbre_est_avl() const ;
    bool        invariant() const ;

private:
    Arbre *racine ;
};

template<typename V>
Arbre_AVL<V>::Arbre_AVL() : racine(nullptr) {

}

template<typename V>
bool Arbre_AVL<V>::vide() const {
    return racine == nullptr ;
}

template<typename V>
size_t Arbre_AVL<V>::cardinal() const {
    return aux_compter(racine) ;
}

template<typename V>
size_t Arbre_AVL<V>::aux_compter(Arbre_AVL::Arbre *root) const {
    if (!root) return 0 ;
    return 1 + aux_compter(root->gauche) + aux_compter(root->droite) ;
}

template<typename V>
void Arbre_AVL<V>::inserer(const V &cle) {
    aux_inserer(cle, racine) ;
    assert(invariant()) ;
}

template<typename V>
void Arbre_AVL<V>::aux_inserer(const V& cle, Arbre*& root) {
    if (!root) root = new Arbre(cle) ;
    else if (cle < root->cle) aux_inserer(cle, root->gauche) ;
    else if (cle > root->cle) aux_inserer(cle, root->droite) ;

    else throw std::runtime_error("insertion: duplication de clé") ;

    mise_a_jour_hauteur(root) ;
    equilibrer_le_sous_arbre_avl(root) ;
}

template<typename V>
const V &Arbre_AVL<V>::rechercher(const V &cle) const {
    return  aux_rechercher(cle, racine) ;
}

template<typename V>
const V &Arbre_AVL<V>::aux_rechercher(const V &cle, Arbre_AVL::Arbre *root) const {
    if (!root) throw std::runtime_error("Clé introuvable dans l'arbre.") ;

    if (cle < root->cle) return aux_rechercher(cle, root->gauche) ;
    if (cle > root->cle) return aux_rechercher(cle, root->droite) ;
    return root->cle ;
}

template<typename V>
void Arbre_AVL<V>::aux_effacer(Arbre_AVL::Arbre *root) {
    if (!root) return ;

    aux_effacer(root->gauche) ;
    aux_effacer(root->droite) ;

    delete root ;
}

template<typename V>
void Arbre_AVL<V>::effacer() {
    aux_effacer(racine) ;
    racine = nullptr ;
}

template<typename V>
Arbre_AVL<V>::~Arbre_AVL() {
    effacer() ;
}

template<typename V>
void Arbre_AVL<V>::supprimer(const V &cle) {
    aux_supprimer(cle, racine) ;
    assert(invariant()) ;

}

template<typename V>
void Arbre_AVL<V>::aux_supprimer(const V &cle, Arbre_AVL::Arbre*& root) {
    if (!root) throw std::runtime_error("suppression: clé absente") ;

    if (cle > root->cle) aux_supprimer(cle, root->droite) ;
    else if (cle < root->cle) aux_supprimer(cle, root->gauche) ;
    else aux_retirer_noeud(root) ;

    if (root) mise_a_jour_hauteur(root) ;
    equilibrer_le_sous_arbre_avl(root) ;
}

template<typename V>
void Arbre_AVL<V>::aux_retirer_noeud(Arbre_AVL::Arbre*& root) {

    if (!root->droite)  {
        if (!root->gauche) {
            delete root ;
            root = nullptr ;
            return ;
        }
        auto pred = root->gauche ;
        root->cle = pred->cle ;
        root->gauche = pred->gauche ;
        root->droite = pred->droite ;
        delete pred ;
    }
    else if (!root->gauche) {
        auto pred = root->droite;
        root->cle = pred->cle;
        root->gauche = pred->gauche;
        root->droite = pred->droite;
        delete pred;
    }
    else {
        auto& pred = root->gauche ;
        while (pred->droite) pred = pred->droite ;
        root->cle = pred->cle ;
        if (!pred->gauche) {
            delete pred ;
            pred = nullptr ;
            return ;
        }
        auto elim = pred->gauche ;
        pred->cle = elim->cle ;
        pred->droite = elim->droite ;
        pred->gauche = elim->gauche ;
        delete elim ;
    }
}

template<typename V>
Arbre_AVL<V>::Arbre_AVL(const Arbre_AVL<V> &source) : racine(aux_copier(source.racine)) {

}

template<typename V>
typename Arbre_AVL<V>::Arbre*
Arbre_AVL<V>::aux_copier(Arbre_AVL::Arbre *root) {
    if (!root) return ;

    auto* retval = new Arbre(root->cle) ;
    retval->gauche = aux_copier(root->gauche) ;
    retval->droite = aux_copier(root->droite) ;
    return retval ;
}

template<typename V>
Arbre_AVL<V> &Arbre_AVL<V>::operator=(Arbre_AVL<V> rhs) {
    std::swap(racine, rhs.racine) ;
    return *this ;
}

template<typename V>
Arbre_AVL<V>::Arbre_AVL(std::initializer_list<V> l) : racine(nullptr) {
    for (auto e: l) inserer(e) ;
}

template<typename V>
int Arbre_AVL<V>::aux_hauteur(Arbre* root) const {
    if (!root) return -1 ;

    return 1 + std::max(aux_hauteur(root->gauche), aux_hauteur(root->droite)) ;
}

template<typename V>
void Arbre_AVL<V>::rotation_vers_la_droite(Arbre_AVL::Arbre*& root) {
    auto& new_root = root->droite ;
    if (new_root->gauche) root->droite = new_root->gauche ;
    new_root->gauche = root ;
    root = new_root ;
}

template<typename V>
void Arbre_AVL<V>::rotation_vers_la_gauche(Arbre_AVL::Arbre*& root) {
    auto& new_root = root->gauche ;
    if (new_root->droite) root->gauche = new_root->droite ;
    new_root->droite = root ;
    root = new_root ;
}

template<typename V>
void Arbre_AVL<V>::mise_a_jour_hauteur(Arbre_AVL::Arbre *root) {
    root->hauteur = aux_hauteur(root) ;
}

template<typename V>
void Arbre_AVL<V>::equilibrer_le_sous_arbre_avl(Arbre_AVL::Arbre *root) {
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

template<typename V>
int Arbre_AVL<V>::facteur_equilibre_du_sous_arbre(Arbre_AVL::Arbre *root) const {
    if (!root) return 0 ;

    int h_gauche = root->gauche ? root->gauche->hauteur : -1 ;
    int h_droite = root->droite ? root->droite->hauteur : -1 ;
    return h_droite - h_gauche ;
}

template<typename V>
bool Arbre_AVL<V>::sous_arbre_est_valide(Arbre_AVL::Arbre *root) const {
    if (!root) return true ;

    bool valide_gauche ;
    if (root->gauche) valide_gauche = (root->cle > root->gauche->cle) && sous_arbre_est_valide(root->gauche) ;
    else  valide_gauche = true ;

    bool valide_droite ;
    if (root->droite) valide_droite = (root->cle < root->droite->cle) && sous_arbre_est_valide(root->droite) ;
    else valide_droite = true ;

    return valide_gauche && valide_droite ;
}

template<typename V>
bool Arbre_AVL<V>::arbre_est_valide() const {
    return sous_arbre_est_valide(racine) ;
}

template<typename V>
bool Arbre_AVL<V>::sous_arbre_est_avl(Arbre_AVL::Arbre *root) const {
    if (!root) return true ;
    int eq = facteur_equilibre_du_sous_arbre(root) ;
    return (eq < 2) && (eq > -2) && sous_arbre_est_avl(root->gauche) && sous_arbre_est_avl(root->droite) ;
}

template<typename V>
bool Arbre_AVL<V>::arbre_est_avl() const {
    return sous_arbre_est_avl(racine) ;
}

template<typename V>
bool Arbre_AVL<V>::invariant() const {
    return arbre_est_avl() && arbre_est_valide() ;
}

template<typename V>
void Arbre_AVL<V>::aux_ecraser_noeud(Arbre_AVL::Arbre *&root) {
    auto pred = root ;
    root->cle = pred->cle ;
    root->gauche = pred->gauche ;
    root->droite = pred->droite ;
    delete pred ;
}


#endif //ARBRE_AVL_ARBRE_AVL_H
