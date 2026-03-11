#include <iostream>
#include <duckx.hpp>
#include <windows.h>
#include <string>
//#include <bits/stdc++.h>

int get_letters(std::string par, std::string &container, int index) {
    if (par[index] == '[') 
        return index;
    
    container += par[index];
    return get_letters(par, container, index-1);
}

void read_paragraph(std::string par, int indices[], std::string &container) {
    
    bool whileLoop = true;
    
    if (par.find(']') == std::string::npos)
        return;

    for (int i = par.size(); whileLoop; i--) {
        if (par[i] == ']') {
            /*for (auto& index : indices) {
                index = i;
            }*/

            for (int j = 0; j < 2; j++) {
                indices[j] = i;
            }

            indices[1] = get_letters(par, container, indices[1]-1);     // Go through all the letters from ']' onwards
            reverse(container.begin(), container.end());                // Reverse the string, because it was iterated backwards
            //container += '.';                                           // Add the dot

            std::cout << "Read: " << container << " Index: " << indices[0] << " " << indices[1] << std::endl;
            whileLoop = false;
        }
    }
}

void insert_char(std::string &inText, int indices[2]) {
    int endPoint = indices[1]-1;
    inText.insert(endPoint, ".");
}

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    duckx::Document doc(ASSET_DIR + std::string("/test_case2.docx"));
    doc.open();
    int indices[2] = { 0,0 };   // Begin, end
   
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        std::string paragraph, container;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            paragraph += r.getAll_text();
        }   
        
        read_paragraph(paragraph, indices, container);
        
        for (auto r = p.runs(); r.has_next(); r.next()) {
            if ((r.getAll_text().find(container) != std::string::npos) && (container != "") && (container.find('.') == std::string::npos)) {
                std::cout << "Added a dot to: " << r.getAll_text() << std::endl;

                std::string citationFormat = ("[" + container + ".]");
                r.set_citation(citationFormat.c_str());
            }
        }

        paragraph += "\n\n";
        //std::cout << paragraph << std::endl;
    }

    doc.save();
    return 0;
}
