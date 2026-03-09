#include <iostream>
#include <duckx.hpp>
#include <windows.h>
//#include <bits/stdc++.h>

int get_letters(std::string par, std::string &container, int index) {
    if (par[index] == '[') 
        return index;
    
    container += par[index];
    return get_letters(par, container, index-1);
}

void read_paragraph(std::string par) {
    std::string container;
    bool whileLoop = true;
    int indices[2] = {0,0};
    
    if (par.find(']') == std::string::npos)
        return;

    for (int i = par.size(); whileLoop; i--) {
        if (par[i] == ']') {
            for (auto& index : indices) {
                index = i;
            }

            indices[1] = get_letters(par, container, indices[1]-1);     // Go through all the letters from ']' onwards
            reverse(container.begin(), container.end());                // Reverse the string, because it was iterated backwards
            container += '.';                                           // Add the dot

            std::cout << "Check this shit out: " << container << " Index: " << indices[0] << " " << indices[1] << std::endl;
            whileLoop = false;
        }
    }
}

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    duckx::Document doc(ASSET_DIR + std::string("/my_test.docx"));
    doc.open();
    std::string textCache;
   
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        std::string paragraph;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            paragraph += r.getAll_text();
        }   
        //textCache += '\n';
        read_paragraph(paragraph);
        paragraph += "\n\n";
        std::cout << paragraph << std::endl;
    }

    //cout << textCache << endl;
    return 0;
}
