//
// Created by Pascal Charpentier on 2022-06-23.
//

#ifndef ARBRE_AVL_ARBRE_AVL_H
#define ARBRE_AVL_ARBRE_AVL_H

template<typename V>
class Arbre_AVL {
private:
    static const int HAUTEUR_NULLPTR = -1 ;

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
    Arbre*          aux_copier(Arbre *root) ;

private:
    int             aux_hauteur(Arbre* root) ;
    void            rotation_vers_la_droite(Arbre*& root) ;
    void            rotation_vers_la_gauche(Arbre*& root) ;

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
}

template<typename V>
void Arbre_AVL<V>::aux_inserer(const V& cle, Arbre*& root) {
    if (!root) root = new Arbre(cle) ;
    else if (cle < root->cle) aux_inserer(cle, root->gauche) ;
    else if (cle > root->cle) aux_inserer(cle, root->droite) ;
    else throw std::runtime_error("insertion: duplication de clé") ;
    root->hauteur = aux_hauteur(root) ;
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

}

template<typename V>
void Arbre_AVL<V>::aux_supprimer(const V &cle, Arbre_AVL::Arbre*& root) {
    if (!root) throw std::runtime_error("suppression: clé absente") ;

    if (cle > root->cle) aux_supprimer(cle, root->droite) ;
    else if (cle < root->cle) aux_supprimer(cle, root->gauche) ;
    else aux_retirer_noeud(root) ;
    if (root) root->hauteur = aux_hauteur(root) ;
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
int Arbre_AVL<V>::aux_hauteur(Arbre* root) {
    if (!root) return HAUTEUR_NULLPTR ;
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


#endif //ARBRE_AVL_ARBRE_AVL_H
