#include <filesystem>

#include "Game.h"

int main() {
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path().parent_path());

    Game game;
    game.run();
    return 0;
}
