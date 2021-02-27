#include "gtest-1.8.1/gtest.h"
#include "../src/Conjunto.h"


/**
 * Test simple básico
 */


TEST(conjunto_test, test_mio_pertenece) { // test mio
    Conjunto<int> c;
    c.insertar(500);
    c.insertar(400);
    c.insertar(700);
    c.insertar(600);
    c.insertar(800);
    c.insertar(450);
    c.insertar(640);
    c.insertar(610);
    c.insertar(725);
    EXPECT_EQ(c.cardinal(),9);
    c.remover(700);
    c.remover(700);
    EXPECT_EQ(c.cardinal(), 8);
    ASSERT_FALSE(c.pertenece(700));
    ASSERT_TRUE(c.pertenece(500));
    c.remover(500);
    ASSERT_FALSE(c.pertenece(500));

    ASSERT_TRUE(c.pertenece(400));
    ASSERT_TRUE(c.pertenece(600));
    ASSERT_TRUE(c.pertenece(450));
    ASSERT_TRUE(c.pertenece(400));
    ASSERT_TRUE(c.pertenece(640));
    ASSERT_TRUE(c.pertenece(610));
    ASSERT_TRUE(c.pertenece(725));
    ASSERT_FALSE(c.pertenece(700));

    EXPECT_EQ(c.cardinal(),7);
    c.remover(500);
    EXPECT_EQ(c.cardinal(),7);
    c.remover(600); //
    ASSERT_FALSE(c.pertenece(600));
    c.insertar(600);
    c.remover(600);
    c.insertar(0);
    c.insertar(1000);
    c.insertar(545);
    ASSERT_FALSE(c.pertenece(700));
    c.remover(450);
    ASSERT_TRUE(c.pertenece(610));
    ASSERT_FALSE(c.pertenece(450));
    ASSERT_FALSE(c.pertenece(600));
    ASSERT_TRUE(c.pertenece(1000));
    ASSERT_TRUE(c.pertenece(640));





}








TEST(conjunto_test, conjunto_vacio) {
    Conjunto<int> c;
    EXPECT_EQ(c.cardinal(), 0);
}


TEST(conjunto_test, test_insertar_un_valor) {
    Conjunto<int> c;
    c.insertar(5);
    EXPECT_EQ(c.cardinal(), 1);
}


TEST(conjunto_test, test_insertar_cinco_valores) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(7);
    c.insertar(6);
    c.insertar(8);
    EXPECT_EQ(c.cardinal(), 5);
}

TEST(conjunto_test, test_pertenece) {
  Conjunto<int> c;
  
  for (int i = 0; i < 5; i++) {
    EXPECT_FALSE(c.pertenece(i));
  }

  // Agrego el 3
  c.insertar(3);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(c.pertenece(i), i == 3);
  }

  // Agrego el 3
  c.insertar(5);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(c.pertenece(i), i == 3);
  }
  EXPECT_TRUE(c.pertenece(5));

}

TEST(conjunto_test, test_insertar_remover_un_valor) {
    Conjunto<int> c;
    c.insertar(5);
    c.remover(5);
    EXPECT_EQ(c.cardinal(), 0);
    c.insertar(5);
    EXPECT_EQ(c.cardinal(), 1);
}

TEST(conjunto_test, test_minimo) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(7);
    c.insertar(6);
    c.insertar(8);
    EXPECT_EQ(c.minimo(), 4); //4
}

TEST(conjunto_test, test_maximo) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(7);
    c.insertar(6);
    c.insertar(8);
    EXPECT_EQ(c.maximo(), 8);
}

TEST(conjunto_test, test_remover_caso_un_hijo) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(6);
    c.insertar(7);
    c.remover(6);
    EXPECT_EQ(c.cardinal(), 2);
}

TEST(conjunto_test, test_remover_caso_dos_hijos_simple) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(7);
    c.insertar(6);
    c.insertar(8);
    c.remover(7);
    EXPECT_EQ(c.cardinal(), 4);
}

TEST(conjunto_test, test_remover_caso_dos_hijos_doble) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(20);
    c.insertar(15);
    c.insertar(12);
    c.insertar(16);
    c.insertar(24);
    c.insertar(22);
    c.insertar(25);
    c.remover(20);
    EXPECT_EQ(c.cardinal(), 8);
}

TEST(conjunto_test, test_siguiente_inorder) {
    Conjunto<int> c;
    c.insertar(5);
    c.insertar(4);
    c.insertar(20);
    c.insertar(15);
    c.insertar(12);
    c.insertar(16);
    c.insertar(24);
    c.insertar(22);
    c.insertar(25);

    EXPECT_EQ(c.siguiente(20), 22);
    EXPECT_EQ(c.siguiente(4), 5);
    EXPECT_EQ(c.siguiente(15), 16);
}

const int NCLAVES = 1000; //1000

int clave(int i) {
	return NCLAVES * ((i * i - 100 * i) % NCLAVES) + i;
}

TEST(conjunto_test, test_stress) {
    Conjunto<int> c;

    // Insertar
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_EQ(c.cardinal(), i);
	    ASSERT_FALSE(c.pertenece(k));
	    c.insertar(k);
	    ASSERT_TRUE(c.pertenece(k));
    }
    ASSERT_EQ(c.cardinal(), NCLAVES);

    // Insertar de nuevo
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_TRUE(c.pertenece(k));
	    c.insertar(k);
	    ASSERT_TRUE(c.pertenece(k));
	    ASSERT_EQ(c.cardinal(), NCLAVES);
    }

    // Eliminar los valores para i par    /nada abajo de 200
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_TRUE(c.pertenece(k));
	    if (i % 2 == 0) {
	    	c.remover(k);
	    	ASSERT_FALSE(c.pertenece(k));
	    }
    }
    ASSERT_EQ(c.cardinal(), NCLAVES / 2);

    // Eliminar los valores para i impar
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    if (i % 2 == 0) {
	    	ASSERT_FALSE(c.pertenece(k));
	    } else {
	    	ASSERT_TRUE(c.pertenece(k));
	    	c.remover(k);
	    	ASSERT_FALSE(c.pertenece(k));
	    }
    }
    ASSERT_EQ(c.cardinal(), 0);

    // Verificar que no haya valores
    for (int i = 0; i < NCLAVES; i++) {
	    int k = clave(i);
	    ASSERT_FALSE(c.pertenece(k));
    }
}
