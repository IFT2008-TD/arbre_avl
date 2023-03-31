//
// Created by Pascal Charpentier on 2022-06-23.
//

#ifndef ARBRE_AVL_ARBRE_AVL_H
#define ARBRE_AVL_ARBRE_AVL_H

template<typename C, typename V>
class Arbre_AVL {

private:        // Type privé

    struct Arbre {
        //eeeee
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
Arbre_AVL<C, V>::Arbre_AVL()  {

}

template<typename C, typename V>
bool Arbre_AVL<C, V>::vide() const {
    return false ;
}

template<typename C, typename V>
size_t Arbre_AVL<C, V>::cardinal() const {
    return 0  ;
}

template<typename C, typename V>
size_t Arbre_AVL<C, V>::aux_compter(Arbre_AVL::Arbre *root) const {
    return 0 ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::inserer(const C &cle, const V& valeur) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_inserer(const C& cle, const V& valeur, Arbre*& root) {

}

template<typename C, typename V>
const V &Arbre_AVL<C, V>::rechercher(const C &cle) const {
    return  V() ;
}

template<typename C, typename V>
const V &Arbre_AVL<C, V>::aux_rechercher(const C &cle, Arbre_AVL::Arbre *root) const {
    return V() ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_effacer(Arbre_AVL::Arbre*& root) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::effacer() {

}

template<typename C, typename V>
Arbre_AVL<C, V>::~Arbre_AVL() {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::supprimer(const C &cle) {


}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_supprimer(const C &cle, Arbre_AVL::Arbre*& root) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_retirer_noeud(Arbre_AVL::Arbre*& root) {



}

template<typename C, typename V>
Arbre_AVL<C, V>::Arbre_AVL(const Arbre_AVL<C, V> &source) {

}

template<typename C, typename V>
typename Arbre_AVL<C, V>::Arbre*
Arbre_AVL<C, V>::aux_copier(Arbre_AVL::Arbre *root) {
   return Arbre_AVL<C, V> () ;
}

template<typename C, typename V>
Arbre_AVL<C, V> &Arbre_AVL<C, V>::operator=(Arbre_AVL<C, V> rhs) {
    return *this ;
}

template<typename C, typename V>
int Arbre_AVL<C, V>::aux_hauteur(Arbre* root) const {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::rotation_vers_la_droite(Arbre_AVL::Arbre*& root) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::rotation_vers_la_gauche(Arbre_AVL::Arbre*& root) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::mise_a_jour_hauteur(Arbre_AVL::Arbre *root) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::equilibrer_le_sous_arbre_avl(Arbre_AVL::Arbre *root) {

}

template<typename C, typename V>
int Arbre_AVL<C, V>::facteur_equilibre_du_sous_arbre(Arbre_AVL::Arbre *root) const {
   return 0 ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_valide(Arbre_AVL::Arbre *root) const {
    return false ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::arbre_est_valide() const {
    return false ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_avl(Arbre_AVL::Arbre *root) const {
    return true ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::arbre_est_avl() const {
    return true ;
}

template<typename C, typename V>
bool Arbre_AVL<C, V>::invariant() const {
    return true ;
}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_transplanter(Arbre_AVL::Arbre*& enfant, Arbre_AVL::Arbre *&parent) {

}

template<typename C, typename V>
void Arbre_AVL<C, V>::aux_couper_feuille(Arbre_AVL::Arbre *&root) {

}

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_inferieur_a(const C &cle, Arbre_AVL::Arbre *root) const {
    }

template<typename C, typename V>
bool Arbre_AVL<C, V>::sous_arbre_est_superieur_a(const C &cle, Arbre_AVL::Arbre *root) const {
   return true ;
}


#endif //ARBRE_AVL_ARBRE_AVL_H
