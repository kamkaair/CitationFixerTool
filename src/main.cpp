#include <iostream>
#include <duckx.hpp>
#include <windows.h>
#include <string>

// Get the characters inside a citation
int get_letters(std::string par, std::string &container, int index) {
    if (par[index] == '[') 
        return index;
    
    container += par[index];
    return get_letters(par, container, index-1);
}

// Check if the citation should have a dot or not.
bool is_citation_eligible(std::string par, int index) {
    if (index <= 0) {
        std::cout << "Citation eligible: FALSE, STRING END" << std::endl;
        return false;
    }

    if (par[index] == ')') { // Skip the sections including ()
        int newIndex = index;
        while (par[newIndex] != '(')
            newIndex--;

        int resultIndex = index - newIndex;
        is_citation_eligible(par, index - resultIndex);
    }

    if (par[index] == '.') {
        for (int i = 0; i < 3; i++) { // Check the next characters, if it contains a citation
            if (par[index - i] == ']') {
                std::cout << "Citation eligible: FALSE" << std::endl;
                return false;
            }
                
        }
        std::cout << "Citation eligible: TRUE" << std::endl;
        return true;
    }
        
    return is_citation_eligible(par, index-1);
}

void read_paragraph(std::string par, int indices[], std::string &container, bool &citationEligible) {
    
    bool whileLoop = true, whiling = true;
    
    if (par.find(']') == std::string::npos)
        return;

    for (int i = par.size(); whileLoop; i--) {
        if (par[i] == ']') {
            for (int j = 0; j < 2; j++) {
                indices[j] = i;
            }

            indices[1] = get_letters(par, container, indices[1]-1);     // Go through all the letters from ']' onwards
            reverse(container.begin(), container.end());                // Reverse the string, because it was iterated backwards

            citationEligible = is_citation_eligible(par, indices[1]);

            std::cout << "Read: " << container << " Index: " << indices[0] << " " << indices[1] << std::endl;
            whileLoop = false;
        }
    }
}

void getCitationAmount(std::string par, int& citationAmount) {
    for (auto c : par) {
        if (c == '[')
            citationAmount++;
    }
}

void insert_char(std::string &inText, int indices[2]) {
    int endPoint = indices[1]-1;
    inText.insert(endPoint, ".");
}

std::string asset_path = ASSET_DIR + std::string("/test_case2.docx");

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    duckx::Document doc(asset_path);
    doc.open();
    int indices[2] = { 0,0 };   // Begin, end
   
    // Get all the paragraphs of the document
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        std::string paragraph, citationCache;    

        // Store the whole paragraph
        for (auto r = p.runs(); r.has_next(); r.next()) {
            paragraph += r.getAll_text();
        }   
        
        bool citationEligible = false;
        read_paragraph(paragraph, indices, citationCache, citationEligible); // Currently the goal is to read the last citation

        int citationAmount = 0;
        getCitationAmount(paragraph, citationAmount);
        std::cout << "Citation amount: " << citationAmount << std::endl;
        
        for (auto r = p.runs(); r.has_next(); r.next()) {
            bool findText = (r.getAll_text().find(citationCache) != std::string::npos);
            bool citationFind = (citationCache != "") && (citationCache.find('.') == std::string::npos);
            
            // Find the citation from the text
            if ((findText && citationFind) && citationEligible) {
                std::cout << "Added a dot to: " << r.getAll_text() << std::endl;

                // Edit the file
                std::string citationFormat = ("[" + citationCache + ".]");
                r.set_citation(citationFormat.c_str());
            }
        }
        std::cout << std::endl; // Leave empty space after one paragraph
        paragraph += "\n\n";
    }

    doc.save();
    return 0;
}
