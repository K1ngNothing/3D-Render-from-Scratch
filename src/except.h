#include <iostream>

namespace except {

inline void react() {
    try {
        throw;
    } catch (std::exception& e) {
        std::cerr << "Uncaught exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Uncaught unknown exception\n";
    }
}

}  // namespace except
