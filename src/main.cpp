#include <iostream>
#include <duckx.hpp>
#include <windows.h>
#include <string>

#include "utils.h"

std::string in_asset_path = ASSET_DIR + std::string("/test_case2.docx");

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    utils ut(in_asset_path);
    ut.getDoc().open();
   
    // Get all the paragraphs of the document
    for (auto p = ut.getDoc().paragraphs(); p.has_next(); p.next()) {
        std::cout << "/////// -BEGIN- ///////" << std::endl;
        std::string paragraph, citationCache;
        int indices[2] = { 0,0 };   // Begin, end

        // Store the whole paragraph
        for (auto r = p.runs(); r.has_next(); r.next()) {
            paragraph += r.getAll_text();
        }   
        
        bool citationEligible = false;
        ut.read_paragraph(paragraph, indices, citationCache, citationEligible); // Currently the goal is to read the last citation

        int citationAmount = 0;
        ut.getCitationAmount(paragraph, citationAmount);
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
        std::cout << paragraph << std::endl;
        std::cout << "/////// -END- ///////" << std::endl;
        std::cout << std::endl; // Leave empty space after one paragraph
        paragraph += "\n\n";
    }

    ut.getDoc().save();
    return 0;
}
