#pragma once
#include <string>

class citation {
public:
    citation(std::string name, int indices[2], int index) : m_name(name), m_ID(index) {
        for (int i = 0; i < 2; i++) {
            m_indices[i] = indices[i];
        }
    }

    std::string getName() const {
        return m_name;
    }

    int getIndexBegin() const {
        return m_indices[0];
    }

    int getIndexEnd() const {
        return m_indices[1];
    }

    void printIndices() {
        for (auto i : m_indices) {
            std::cout << "Indices: " << i << std::endl;
        }
    }

    int getIndex() const {
        return m_ID;
    }

private:
    std::string m_name;
    int m_indices[2];
    int m_ID = -1;
};