#include <iostream>
#include <duckx.hpp>
#include <windows.h>
#include <string>
#include <vector>

#include "utils.h"

std::string in_asset_path = ASSET_DIR + std::string("/test_case2.docx");

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    utils ut(in_asset_path);
    ut.getDoc().open();

    std::string entireText;
   
    // Get all the paragraphs of the document
    for (auto p = ut.getDoc().paragraphs(); p.has_next(); p.next()) {
        std::cout << "/////// -BEGIN- ///////" << std::endl;
        std::string paragraph, citationCache;

        // Store the whole paragraph
        for (auto r = p.runs(); r.has_next(); r.next()) {
            paragraph += r.getAll_text();
        }   
        
        std::vector<citation> tempCitations; // temporary citation cache used for adding the spaces for the recent citations
        ut.createAllCitations(paragraph, tempCitations);
        ut.addSpaces(paragraph, tempCitations);

        bool citationEligible = false;
        ut.read_paragraph(paragraph, citationCache, citationEligible); // Currently the goal is to read the last citation
        
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

        //p.runs().set_text(paragraph);

        //for (auto r = p.runs(); r.has_next(); r.next()) {
            //r.set_citation()
        //}
        //ut.addSpaces(paragraph);

        /*for (auto c : ut.getCitations()) {
            c.printIndices();
            std::cout << c.getIndexBegin() << " " << c.getIndexEnd() << std::endl;
        }*/

        std::cout << paragraph << std::endl;
        std::cout << "/////// -END- ///////" << std::endl;
        std::cout << std::endl; // Leave empty space after one paragraph
        paragraph += "\n\n";
        
        entireText += paragraph;
    }

    for (auto c : ut.getCitations()) {
        std::cout << "Begin I: " << c.getIndexBegin() << " - End I: " << c.getIndexEnd() << " - Content: " << c.getName() << std::endl;
    }

    //ut.getDoc().save();
    return 0;
}
