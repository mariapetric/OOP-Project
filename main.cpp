#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Coordonate.h"
#include "Strada.h"
#include "Intersectie.h"
#include "Semafor.h"



int main() {

    Coordonate coord{ 10, 20 };  // Exemplu de coordonate (x = 10, y = 20)

    // Definirea unei limitări de viteză (exemplu)
    std::vector<std::pair<int, int>> limitari = { { 5, 50 }, { 10, 60 }, { 15, 80 } };

    // Crearea unui obiect de tip Strada
    Strada strada(1, "Strada Mare", coord, Orientare::Verticala, limitari);

    // Afișarea obiectului Strada
    std::cout << strada;
    return 0;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
