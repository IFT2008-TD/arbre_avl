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

        explicit Arbre(V v) : cle(v), gauche(nullptr), droite(nullptr) {} ;
    };

public:

    bool vide () const ;
    size_t cardinal () const ;

    void effacer () ;
    const V&    rechercher(const V& cle) const ;
    void inserer(const V& cle) ;
    void supprimer (const V& cle) ;

private:
    Arbre *racine ;
};

#endif //ARBRE_AVL_ARBRE_AVL_H
