  // Copyright 2019 Alexander Procelewski
#pragma once
#ifndef C__USERS_ALEX_SOURCE_REPOS_MAPTESTER_SIMULATIONARENA_H_
#define C__USERS_ALEX_SOURCE_REPOS_MAPTESTER_SIMULATIONARENA_H_

#include <string>

/* Single Tile
 */
struct TestArenaTile final {
    boolean walls_[4]{};

    TestArenaTile();
    explicit TestArenaTile(const boolean walls[4]);
};

/**
 * Test class for simulating an arena
 */
class SimulationArena {
 public:
    explicit SimulationArena(std::string path);
    ~SimulationArena();

    boolean* ScanWalls(int x, int y) const;

 private:
    int arena_x_size_;
    int arena_y_size_;
    int simple_arena_size_;
    char** simple_arena_ = nullptr;
    TestArenaTile **arena_ = nullptr;

    boolean InitializeArena(std::ifstream &stream);
    void ReadArena(std::ifstream &stream);
    void DumpSimpleArena() const;
    void ModifyArena(int x, int y, TestArenaTile value) const;
    void ConvertIntoArena(bool print_out_walls = false) const;
};
#endif  // C__USERS_ALEX_SOURCE_REPOS_MAPTESTER_SIMULATIONARENA_H_
