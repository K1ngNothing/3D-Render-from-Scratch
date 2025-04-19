#include <iostream>

namespace except {

inline void react() {
    try {
        throw;
    } catch (std::exception& e) {
        std::cerr << "Uncaught exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Uncaught non-standard exception\n";
    }
}

}  // namespace except
