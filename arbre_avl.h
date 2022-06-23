//
// Created by Pascal Charpentier on 2022-06-23.
//

#ifndef ARBRE_AVL_ARBRE_AVL_H
#define ARBRE_AVL_ARBRE_AVL_H

template<typename V>
class Arbre_AVL {
private:
    struct Arbre{
        V cle ;
        Arbre *gauche ;
        Arbre *droite ;

        size_t hauteur ;

        explicit Arbre(V v) : cle(v), gauche(nullptr), droite(nullptr), hauteur(0) {} ;
    };

public:

    Arbre_AVL() ;
    Arbre_AVL(const Arbre_AVL<V>& source) ;
    Arbre_AVL<V>& operator = (Arbre_AVL<V> rhs) ;
    ~Arbre_AVL() ;

    bool vide () const ;
    size_t cardinal () const ;

    void effacer () ;
    const V&    rechercher(const V& cle) const ;
    void inserer(const V& cle) ;
    void supprimer (const V& cle) ;

private:
    size_t aux_compter(Arbre* root) ;
    void aux_inserer(const V& cle, Arbre*& root) ;
    const V& aux_rechercher(const V& cle, Arbre* root) const ;
    void aux_effacer (Arbre* root) ;
    void aux_supprimer (const V& cle, Arbre*& root) ;
    void aux_retirer_noeud(Arbre*& root) ;
    Arbre* aux_trouver_predecesseur_immediat(Arbre* root) const ;

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
size_t Arbre_AVL<V>::aux_compter(Arbre_AVL::Arbre *root) {
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

    if (cle > root->cle) aux_effacer(cle, root->droite) ;
    else if (cle < root->cle) aux_effacer(cle, root->gauche) ;
    else aux_retirer_noeud(root) ;
}

template<typename V>
void Arbre_AVL<V>::aux_retirer_noeud(Arbre_AVL::Arbre*& root) {
    Arbre *pred = nullptr ;

    if (!root->gauche) {
        if (!root->droite) {
            delete root ;
            root = nullptr ;
            return ;
        }
        pred = root->droite ;
    }
    else
        pred = aux_trouver_predecesseur_immediat(root) ;

    root->cle = pred->cle ;
    root->droite = pred->droite ;
    root->gauche = pred->gauche ;
    delete pred ;
}

template<typename V>
typename Arbre_AVL<V>::Arbre *Arbre_AVL<V>::aux_trouver_predecesseur_immediat(Arbre_AVL::Arbre *root) const {
    Arbre *succ = root->gauche ;
    while (succ->droite) succ = succ->droite ;

    return succ ;
}


#endif //ARBRE_AVL_ARBRE_AVL_H
