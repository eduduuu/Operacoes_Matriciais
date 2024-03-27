#include <iostream>
#include <vector>
#include <iterator>

std::vector<int> get_Matrice_Dimensions (float columns_to_Match_Rows) {
    std::vector<int> dimensions;
    int rows, columns;
    if (columns_to_Match_Rows == 0) {
        std::cout << "Quantas linhas a matriz tem?  ";
        std::cin >> rows;
        std::cout << std::endl;
    } else
        rows = columns_to_Match_Rows;
    std::cout << "Quantas colunas a matriz tem?  ";
    std::cin >> columns;
    std::cout << std::endl;
    
    dimensions.push_back(rows);
    dimensions.push_back(columns);
    return dimensions;
}

std::vector<float> build_One_Dimension_Matrice (std::vector<float> matrice, int columns) {
    int value;
    if (matrice.size() < columns) {
        std::cout << "Coluna " << matrice.size()+1 << ": ";
        std::cin >> value;
        matrice.push_back(value);
        return build_One_Dimension_Matrice(matrice, columns);
    }
    return matrice;
}

std::vector<std::vector<float>> build_Two_dimensions_Matrice 
    (std::vector<std::vector<float>> matrice, int rows, int columns) {
    if (matrice.size() < rows) {
        std::cout << "Linha " << matrice.size()+1 << ": " << std::endl;
        matrice.push_back(build_One_Dimension_Matrice({}, columns));
        return build_Two_dimensions_Matrice(matrice, rows, columns);
    }
    return matrice;
}

void show_One_Dimension_Matrice(std::vector<float> m) {
    if (m.empty()) {
        std::cout << std::endl;
        return;
    }

    std::cout << m[0] << " ";
    m.erase(m.begin());
    show_One_Dimension_Matrice(m);
}

void show_Two_Dimensions_Matrice(std::vector<std::vector<float>> m) {
    if (m.empty()) {
        std::cout << std::endl;
        return;
    }

    show_One_Dimension_Matrice(m[0]);
    m.erase(m.begin());
    show_Two_Dimensions_Matrice(m);
}

std::vector<std::vector<float>> scalar_Product_Matrix(float scalar, std::vector<std::vector<float>> m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0 ; j < m[0].size(); j++) {
            m[i][j] *= scalar;
        }
    }

    return m;
}

std::vector<std::vector<float>> add_Matrices(std::vector<std::vector<float>> m1, std::vector<std::vector<float>> m2) {
    for (int i = 0; i < m1.size(); i++) {
        for (int j = 0; j < m1[0].size(); j++) {
            m1[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return m1;
}

std::vector<std::vector<float>> product_Matrices(std::vector<std::vector<float>> m1, std::vector<std::vector<float>> m2) {
    std::vector<std::vector<float>> result_Matrice;
    int sum = 0; 
    for (int i = 0; i < m1.size(); i++) {
        result_Matrice.push_back({});
        for (int j = 0; j < m2[0].size(); j++) {
            for (int h = 0; h < m2.size(); h++) {
                sum += m1[i][h] * m2[h][j];
            }
            result_Matrice[i].push_back(sum);
            sum = 0;
        }

    }
    return result_Matrice;
}

float determinant_of_2X2Matrix(std::vector<std::vector<float>> m) {
    float result = ((m[0][0] * m[1][1]) -(m[0][1] * m[1][0]));
    return result;
}

float determinant_of_3X3Matrix(std::vector<std::vector<float>> m) {
    float diagonal = 1, antidiagonal = 1, diagonalSum = 0, antiDiagonalSum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            diagonal *= m[j][(j+i)%3];
            antidiagonal *= m[j][((5-j-i)%3)];
        }
        diagonalSum += diagonal;
        antiDiagonalSum += antidiagonal;
        diagonal = 1;
        antidiagonal = 1;
    }
    return (diagonalSum - antiDiagonalSum);
}

std::vector<std::vector<float>> transpose_Matrix(std::vector<std::vector<float>> m) {
    std::vector<std::vector<float>> result;

    for (int i = 0; i < m[0].size(); i++) {
        result.push_back({});
        for (int j = 0; j < m.size(); j++) {
            result[i].push_back(m[j][i]);
        }
    }

    return result;
}

std::vector<std::vector<float>> cofactor_3X3_Matrix(std::vector<std::vector<float>> m) {
    std::vector<std::vector<float>> result, small, smallCopy;
    std::vector<std::vector<float>>::iterator it1;
    std::vector<float>::iterator it2;

    for (int i = 0; i < m.size(); i++) {
        result.push_back({});
        small = m;
        it1 = small.begin()+i;
        small.erase(it1);
        smallCopy = small;
        for (int j = 0; j < m[0].size(); j++) {
            small = smallCopy;
            for (int h = 0; h < small.size(); h++) {
                it2 = small[h].begin()+j;
                small[h].erase(it2);
            }
            result[i].push_back(determinant_of_2X2Matrix(small));
            if ((i+j)%2 != 0)
                result[i][j] = result[i][j] * (-1);
        }
    }
    return result;
}

void print_Line() {
    std::cout << std::endl << "----------------------------------------------" << std::endl;
}

void choose_Operation() {
    int option, result, scalar;
    std::vector<int> dimensions_1, dimensions_2;
    std::vector<std::vector<float>> matrice_1, matrice_2, result_Matrice;

    std::cout << "Escolha a operacao desejada pelo numero." << std::endl;
    std::cout << "0: Sair | 1: Somar matrizes | 2: Multiplicar matrizes | 3: Multiplicar escalar por matriz "
        << "| 4: determinante matriz 2x2| 5: determinante matriz 3x3 | 6: Transpor matriz | "
        << "7: Cofatora de matriz 3x3 | 8: Inversa de matriz 3x3" << std::endl;
    std::cin >> option;

    switch (option) {
        case 0:
            return;
            break;
        case 1:
            dimensions_1 = get_Matrice_Dimensions(0);
            std::cout << "Primeira matriz." << std::endl;
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, dimensions_1[0], dimensions_1[1]);
            std::cout << "Segunda Matriz." << std::endl;
            matrice_2 = build_Two_dimensions_Matrice(matrice_2, dimensions_1[0], dimensions_1[1]);
            result_Matrice = add_Matrices(matrice_1, matrice_2);
            print_Line();
            std::cout << "Resuldado: " << std::endl;
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        case 2:
            dimensions_1 = get_Matrice_Dimensions(0);
            dimensions_2 = get_Matrice_Dimensions(dimensions_1[1]);
            std::cout << "Primeira matriz." << std::endl;
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, dimensions_1[0], dimensions_1[1]);
            std::cout << "Segunda Matriz." << std::endl;
            matrice_2 = build_Two_dimensions_Matrice(matrice_2, dimensions_2[0], dimensions_2[1]);
            result_Matrice = product_Matrices(matrice_1, matrice_2);
            print_Line();
            std::cout << "Resuldado: " << std::endl;
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        case 3:
            std::cout << "Qual o valor do escalar? ";
            std::cin >> scalar;
            dimensions_1 = get_Matrice_Dimensions(0);
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, dimensions_1[0], dimensions_1[1]);
            result_Matrice = scalar_Product_Matrix(scalar, matrice_1);
            print_Line();
            std::cout << "Resuldado: " << std::endl;
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        case 4:
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, 2, 2);
            result = determinant_of_2X2Matrix(matrice_1);
            print_Line();
            std::cout << "Resultado: " << result;
            print_Line();
            break;
        case 5:
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, 3, 3);
            result = determinant_of_3X3Matrix(matrice_1);
            print_Line();
            std::cout << "Resultado: " << result;
            print_Line();
            break;
        case 6:
            dimensions_1 = get_Matrice_Dimensions(0);
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, dimensions_1[0], dimensions_1[1]);
            result_Matrice = transpose_Matrix(matrice_1);
            print_Line();
            std::cout << "Resultado: " << std::endl;
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        case 7:
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, 3, 3);
            result_Matrice = cofactor_3X3_Matrix(matrice_1);
            print_Line();
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        case 8:
            matrice_1 = build_Two_dimensions_Matrice(matrice_1, 3, 3);
            result_Matrice = cofactor_3X3_Matrix(matrice_1);
            result_Matrice = transpose_Matrix(result_Matrice);
            result_Matrice = scalar_Product_Matrix((1/determinant_of_3X3Matrix(matrice_1)), result_Matrice);
            print_Line();
            show_Two_Dimensions_Matrice(result_Matrice);
            print_Line();
            break;
        default:
            std::cout << "Opcao Invalida.";
    }
    choose_Operation();
}

int main () {
    std::cout << "Operacoes Matriciais." << std::endl << "Feito por: Eduardo Bomfim." << std::endl;
    choose_Operation();
    return 0;
}