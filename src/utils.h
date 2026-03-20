#pragma once
#include <vector>
#include <array>

#include "citation.h"

class utils {
public:
	utils::utils(std::string path) : m_asset_path(path) {
        doc = duckx::Document(m_asset_path);
    };

    // Get the characters inside a citation
    int get_letters(const std::string par, std::string& container, const char endChar, int index, bool reverse = false) {
        if (par[index] == endChar)
            return index;

        container += par[index];
        return reverse ? get_letters(par, container, endChar, index - 1, true) : get_letters(par, container, endChar, index + 1, false);
        //return get_letters(par, container, endChar, index + minPlus, minPlus);
    }

    // Check if the citation should have a dot or not.
    bool is_citation_eligible(const std::string par, int index) {
        if (index <= 0) {
            std::cout << "Citation eligible: TRUE, STRING END" << std::endl;
            return true;
        }

        if (par[index] == ')') { // Skip the sections including ()
            int newIndex = index;
            while (par[newIndex] != '(')
                newIndex--;

            return is_citation_eligible(par, newIndex);
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

        return is_citation_eligible(par, index - 3); // Skip a possible dot next to the processed citation
    }

    void read_paragraph(std::string par, std::string& container, bool& citationEligible) {

        bool whileLoop = true;
        int indices[2] = {0,0};

        if (par.find(']') == std::string::npos)
            return;

        for (int i = par.size(); whileLoop; i--) {
            if (par[i] == ']') {
                for (int j = 0; j < 2; j++) {
                    indices[j] = i;
                }

                indices[1] = get_letters(par, container, '[', indices[1]-1, true); // Go through all the letters from ']' onwards. Added true, because we want to go backwards
                reverse(container.begin(), container.end());                          // Reverse the string, because it was iterated backwards

                citationEligible = is_citation_eligible(par, indices[1]);             // Check if citation is eligible to have a dot added to them

                //std::cout << "Read: " << container << " Index: " << indices[0] << " " << indices[1] << std::endl;
                whileLoop = false;
            }
        }
    }

    void createNewCitation(std::string name, int indices[2]) {
        citation newCitation(name, indices, m_citationIndex);
        m_citations.push_back(newCitation);
        m_citationIndex++;
    }

    void getCitationAmount(std::string par, int& citationAmount) {
        for (auto c : par) {
            if (c == '[') {
                citationAmount++;
            }
        }
    }

    int skipCondition(std::string par, int currIndex, char beginChar, char endChar) {
        if (par[currIndex] != beginChar) {
            std::cout << "ERROR: couldn't skip condition " << beginChar << " because the input paragraph char and begin char didn't match!" << std::endl;
            return -1;
        }

        int newIndex = currIndex;
        while (par[newIndex] != endChar) {
            newIndex++;
        }
        return newIndex;
    }

    void createAllCitations(const std::string par, std::vector<int*> indices, int currIndex) {
        /*for (int i = 0; i < par.size(); i++) {
            if (par[i] == '[') {
                int indicesTemp[2] = {i,0}; // begin and end
                std::cout << "Begin: " << i << std::endl;

                while (!par[i] != ']') 
                    i++;

                indicesTemp[2] = i;
                indices.push_back(indicesTemp);
                std::cout << "End: " << i << std::endl;
            }
        }*/

        if (par.size() < currIndex)
            return;

        if (par[currIndex] == '[') {
            int indicesTemp[2] = {currIndex,0}; // begin and end
            std::string citationContent;

            //int newIndex = skipCondition(par, currIndex, '[', ']');
            int newIndex = get_letters(par, citationContent, ']', currIndex+1); // Add +1 to the index to ignore the initial bracket

            indicesTemp[1] = newIndex;

            createNewCitation(citationContent, indicesTemp);

            std::cout << "Added index[0]: " << indicesTemp[0] << " index[1]: " << indicesTemp[1] << std::endl;
        }
        
        createAllCitations(par, indices, currIndex+1);
    }

    void insert_char(std::string& inText, int indices[2]) {
        int endPoint = indices[1] - 1;
        inText.insert(endPoint, ".");
    }

    duckx::Document& getDoc() {
        return doc;
    }

    std::vector<citation> getCitations() {
        return m_citations;
    }

private:
    std::string m_asset_path;
    duckx::Document doc;

    std::vector<citation> m_citations;
    int m_citationIndex = 0;
};