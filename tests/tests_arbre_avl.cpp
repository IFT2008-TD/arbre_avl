//
// Created by Pascal Charpentier on 2022-06-23.
//

#include "gtest/gtest.h"
#include "arbre_avl.h"

class Arbre_AVL_Test : public ::testing::Test {
protected:
    Arbre_AVL<size_t> arbre_vide ;
    Arbre_AVL<size_t> arbre_1 ;
    Arbre_AVL<size_t> arbre_2 ;

    void SetUp () override {
        arbre_1.inserer(1) ;

        arbre_2.inserer(1) ;
        arbre_2.inserer(2) ;
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
    EXPECT_EQ(1, arbre_1.rechercher(1)) ;
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
    EXPECT_EQ(1, arbre_2.rechercher(1)) ;
    EXPECT_EQ(2, arbre_2.rechercher(2)) ;
}

TEST_F(Arbre_AVL_Test, arbre_deux_elements_cle_absente_throw) {
    EXPECT_THROW(arbre_2.rechercher(3), std::runtime_error) ;
}
