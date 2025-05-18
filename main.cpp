#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;
/****
 * HARD-CODED TABLES
 * TODO: replace for either manual input or something like CSV
 ****/
const vector<unsigned char> table1 { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
    'j', 'k', 'l', 'm', 'n', 164, 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
    'x', 'y', 'z', ' ', '!', '@', '#', '$', '%', '*', '(', ')', '-', '+', '/',
    '&', ':', ';', ',', '.', 168, '?', 34, 39, '[', ']', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', 160, 130, 161, 162, 163, 248,
};

const vector<unsigned char> table2 {'9', '8', '7', '6', '5', '4', '3', '2', '1', 
    '0', '.', ',', ';', ':', ' ', 39, 34, 248, ')', '(', '*', '%', '$', '#', '!',
    '?', 168, 'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q', 'p', 'o', 164, 
    'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'
};

const vector<pair<char, char>> testTable {
    {'h', '6'}, {'s','0'}, {'p', 'f'},
};

/****
 * UTILITY FUNCTIONS
 ****/
int mod (int a, int b) {
    return (a%b+b)%b;
}

int tableIndexLookup(unsigned char c, const vector<unsigned char> table) {
    return distance(table.cbegin(), find(table.cbegin(), table.cend(), c));
}

void printValidSeeds(int tableSize, vector<pair<int, int>> seeds) {
    cout << "Semillas y sus inversos para tablas de modulo " << tableSize << endl;
    for (auto x: seeds) {
        cout << "semilla: " << x.first << " inverso: " << x.second << endl;
    }
}

//Implementation of the Extended Euclidean Algorithm for modular inverses
int calculateInverse(int a, int size) {
    int t {0};
    int r {size};
    int newt {1};
    int newr {a};

    while (newr != 0) {
        int coeficiente = r / newr;
        int tempt {t};
        t = newt;
        newt = tempt - (coeficiente * newt);
        int tempr {r};
        r = newr;
        newr = tempr - (coeficiente * newr);
    }
    if (r > 1)
        return 0;
    if (t < 0)
        t = t + size;
    return t;
}

// helper funtion to call inverse() on all elements of a table
vector<pair<int, int>> calculateTableinverses(const vector<unsigned char> tabla) {
    vector<pair<int, int>> result {};
    for (int i = 0; i < tabla.size(); ++i) {
        int inv = calculateInverse(i, tabla.size());
        if (inv != 0)
            result.push_back({i, inv});
    }
    return result;
}

/****
 * Verifies if a seed + formula combination solves the cypher
 * using the already decrypted values
 ****/
bool testCypher(const vector<unsigned char> table, 
        const vector<pair<char, char>> testTable, 
        pair<int, int> seed,
        int formula) { 
    for (auto x : testTable) {
        int idx = tableIndexLookup(x.first, table);
        int y = mod((seed.first * idx + formula), table.size());
        if (table[y] != x.second)
            return false;
    }
    return true;
}

/****
 * Verifies if a table can solve the cypher with any combination of
 * seed + formula
 ****/
vector<pair<int, int>> generateValidSeeds(const vector<unsigned char> table,
        const vector<pair<char, char>> testTable,
        vector<pair<int, int>> seedTable,
        vector<int> formulaValues) {
    vector<pair<int, int>> results {};
    for (auto x: formulaValues) {
        for (auto y : seedTable) {
            if (testCypher(table, testTable, y, x))
                results.push_back({x, y.first});
        }
    }

    return results;
}

/****
 * Used to decrypt the full message, using the table, formula and seed pair
 * found
 ****/
void solveCypher(const vector<unsigned char> table,
        int num,
        const pair<int, int> seed) {
    string cypheredMsg {};
    string msg {};
    cout << "Ingrese el codigo a descifrar:\n";
    getline(cin, cypheredMsg);
    for (unsigned char x : cypheredMsg) {
        size_t idx = tableIndexLookup(x, table);
        size_t resultIdx = mod((idx - num) * seed.second, table.size());
        msg += table[resultIdx];
    }
    cout << "El mensaje desencriptado es:\n" << msg << endl;
}

int main() {
    cout << "Formula Y = a.X + num\n"; 
    vector<int> nums {9784562, 30018, 375839};
    
    auto inversosTabla1 = calculateTableinverses(table1);
    printValidSeeds(table1.size(), inversosTabla1);

    auto inversosTabla2 = calculateTableinverses(table2);
    printValidSeeds(table2.size(), inversosTabla2);

    auto validSeeds = generateValidSeeds(table1, testTable, inversosTabla1, nums);
    cout << "Formulas y Semillas que resuelven el encriptado:\n";
    if (validSeeds.empty())
        cout << "No existe semilla que resuelva el encriptado-desencriptado para la"
            << " tabla 1\n";
    else {
        cout << "Tabla 1:\n";
        for (auto x : validSeeds) {
            cout << "num: " << x.first << " a: " << x.second << endl;
            solveCypher(table1, x.first, {x.second, calculateInverse(x.second, table1.size())});
        }
    }
    validSeeds = generateValidSeeds(table2, testTable, inversosTabla2, nums);
    if (validSeeds.empty())
        cout << "No existe semilla que resuelva el encriptado-desencriptado para la"
            << " tabla 2\n";
    else {
        cout << "Tabla 2:\n";
        for (auto x : validSeeds) {
            cout << "num: " << x.first << " a: " << x.second << endl;
            solveCypher(table2, x.first, {x.second, calculateInverse(x.second, table2.size())});
        }
    }
    return 0;
}
