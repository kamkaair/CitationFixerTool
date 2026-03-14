#pragma once

class utils {
public:
	utils::utils(std::string path) : asset_path(path) {
        doc = duckx::Document(asset_path);
    };

    // Get the characters inside a citation
    int get_letters(std::string par, std::string& container, int index) {
        if (par[index] == '[')
            return index;

        container += par[index];
        return get_letters(par, container, index - 1);
    }

    // Check if the citation should have a dot or not.
    bool is_citation_eligible(std::string par, int index) {
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

        return is_citation_eligible(par, index - 1);
    }

    void read_paragraph(std::string par, int indices[], std::string& container, bool& citationEligible) {

        bool whileLoop = true;

        if (par.find(']') == std::string::npos)
            return;

        for (int i = par.size(); whileLoop; i--) {
            if (par[i] == ']') {
                for (int j = 0; j < 2; j++) {
                    indices[j] = i;
                }

                indices[1] = get_letters(par, container, indices[1] - 1);     // Go through all the letters from ']' onwards
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

    void insert_char(std::string& inText, int indices[2]) {
        int endPoint = indices[1] - 1;
        inText.insert(endPoint, ".");
    }

    duckx::Document& getDoc() {
        return doc;
    }

private:
    std::string asset_path;
    duckx::Document doc;
};