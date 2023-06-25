//
// Created by Pascal Charpentier on 2022-06-23.
//

#include "gtest/gtest.h"
#include "arbre_avl.h"

class Arbre_AVL_Test : public ::testing::Test {
protected:
    Arbre_AVL<size_t, size_t> arbre_vide ;
    Arbre_AVL<size_t, size_t> arbre_1 ;
    Arbre_AVL<size_t, size_t> arbre_2 ;
    Arbre_AVL<size_t, size_t> arbre_3 ;

    void SetUp () override {
        arbre_1.inserer(1, 1000) ;

        arbre_2.inserer(1, 1000) ;
        arbre_2.inserer(2, 2000) ;

        arbre_3.inserer(2, 2000) ;
        arbre_3.inserer(1, 1000) ;
        arbre_3.inserer(3, 3000) ;
    }
};

TEST_F(Arbre_AVL_Test, arbre_vide_retourne_true) {
    EXPECT_TRUE(arbre_vide.vide()) ;
}

TEST_F(Arbre_AVL_Test, arbre_vide_zero_element) {
    EXPECT_EQ(0, arbre_vide.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_vide_recherche_cle_throw) {
    EXPECT_THROW(arbre_vide.rechercher(1), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_vide_suppression_throw) {
    EXPECT_THROW(arbre_vide.supprimer(1), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_non_vide) {
    EXPECT_FALSE(arbre_1.vide()) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_cardinal_egal_1) {
    EXPECT_EQ(1, arbre_1.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_rechercher_cle_presente) {
    EXPECT_EQ(1000, arbre_1.rechercher(1)) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_rechercher_cle_absente_throw) {
    EXPECT_THROW(arbre_1.rechercher(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_vide_apres_suppression) {
    arbre_1.supprimer(1) ;
    EXPECT_TRUE(arbre_1.vide()) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_cardinal_zero_apres_suppression) {
    arbre_1.supprimer(1) ;
    EXPECT_EQ(0, arbre_1.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_cle_absente_apres_suppression) {
    arbre_1.supprimer(1) ;
    EXPECT_THROW(arbre_1.rechercher(1), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_double_suppression_impossible) {
    arbre_1.supprimer(1) ;
    EXPECT_THROW(arbre_1.supprimer(1), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_un_element_suppression_cle_absente_throw) {
    EXPECT_THROW(arbre_1.supprimer(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_non_vide) {
    EXPECT_FALSE(arbre_2.vide()) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cardinal_2) {
    EXPECT_EQ(2, arbre_2.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cles_1_2_presentes) {
    EXPECT_EQ(1000, arbre_2.rechercher(1)) ;
    EXPECT_EQ(2000, arbre_2.rechercher(2)) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_absente_throw) {
    EXPECT_THROW(arbre_2.rechercher(3), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_absente_apres_suppression) {
    arbre_2.supprimer(1) ;
    EXPECT_THROW(arbre_2.rechercher(1), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cardinal_1_apres_suppression) {
    arbre_2.supprimer(1) ;
    EXPECT_EQ(1, arbre_2.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_restante_apres_suppression) {
    arbre_2.supprimer(1) ;
    EXPECT_EQ(2000, arbre_2.rechercher(2)) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_2_absente_apres_suppression) {
    arbre_2.supprimer(2) ;
    EXPECT_THROW(arbre_2.rechercher(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cardinal_1_apres_suppression_cle_2) {
    arbre_2.supprimer(2) ;
    EXPECT_EQ(1, arbre_2.cardinal()) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_1_restante_apres_suppression) {
    arbre_2.supprimer(2) ;
    EXPECT_EQ(1000, arbre_2.rechercher(1)) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_vide_apres_2_suppressions) {
    arbre_2.supprimer(1) ;
    arbre_2.supprimer(2) ;
    EXPECT_TRUE(arbre_2.vide()) ;
    EXPECT_EQ(0, arbre_2.cardinal()) ;
    EXPECT_THROW(arbre_2.supprimer(1), std::runtime_error) ;
    EXPECT_THROW(arbre_2.supprimer(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_trois_elements_cardinal_2_apres_suppression) {
    arbre_3.supprimer(2) ;
    EXPECT_FALSE(arbre_3.vide()) ;
    EXPECT_EQ(2, arbre_3.cardinal()) ;
    EXPECT_EQ(1000, arbre_3.rechercher(1)) ;
    EXPECT_EQ(3000, arbre_3.rechercher(3)) ;
    EXPECT_THROW(arbre_3.rechercher(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, arbre_trois_elements_cardinal_1_apres_2_suppressions) {
    arbre_3.supprimer(2) ;
    arbre_3.supprimer(1) ;
    EXPECT_FALSE(arbre_3.vide()) ;
    EXPECT_EQ(1, arbre_3.cardinal()) ;
    EXPECT_EQ(3000, arbre_3.rechercher(3)) ;
    EXPECT_THROW(arbre_3.rechercher(1), std::runtime_error) ;
    EXPECT_THROW(arbre_3.rechercher(2), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, constructeur_copie) {
    Arbre_AVL<size_t, size_t> copie(arbre_3) ;

    EXPECT_EQ(3, copie.cardinal()) ;
    EXPECT_EQ(1000, copie.rechercher(1)) ;
    EXPECT_EQ(2000, copie.rechercher(2)) ;
    EXPECT_EQ(3000, copie.rechercher(3)) ;
    EXPECT_THROW(copie.rechercher(5), std::runtime_error) ;
}

TEST_F(Arbre_AVL_Test, operateur_assignation) {
    Arbre_AVL<size_t, size_t> arbre(arbre_1) ; 
    arbre = arbre_3 ;
    EXPECT_EQ(3, arbre.cardinal()) ;
    EXPECT_EQ(1000, arbre.rechercher(1)) ;
    EXPECT_EQ(2000, arbre.rechercher(2)) ;
    EXPECT_EQ(3000, arbre.rechercher(3)) ;
    EXPECT_THROW(arbre.rechercher(5), std::runtime_error) ;
    
}
