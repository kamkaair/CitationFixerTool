#include <iostream>
#include <duckx.hpp>
using namespace std;

int main() {
    duckx::Document doc(ASSET_DIR + std::string("/my_test.docx"));
    doc.open();

    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        for (auto r = p.runs(); r.has_next(); r.next()) {
            cout << r.get_text() << endl;
        }
    }

    return 0;
}
