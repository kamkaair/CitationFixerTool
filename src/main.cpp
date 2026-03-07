#include <iostream>
#include <duckx.hpp>
#include <windows.h>
using namespace std;

int main() {
    // UTF8 text format
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    duckx::Document doc(ASSET_DIR + std::string("/my_test.docx"));
    doc.open();
    std::string textCache;

    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        for (auto r = p.runs(); r.has_next(); r.next()) {
            //textCache += r.get_text();
            textCache += r.getAll_text();
        }   
        textCache += '\n';     
    }

    cout << textCache << endl;
    return 0;
}
