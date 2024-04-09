#include <application.h>
#include <except.h>

int main() {
    try {
        render_app::Application app;
        app.run();
    } catch (...) {
        except::react();
    }
    return 0;
}
