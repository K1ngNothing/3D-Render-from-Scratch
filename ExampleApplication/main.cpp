#include "Application.h"
#include "Except.h"

int main() {
    try {
        Renderer3D::Application app;
        app.run();
    } catch (...) {
        except::react();
    }
    return 0;
}
