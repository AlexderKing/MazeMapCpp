  // Copyright 2019 Alexander Procelewski
#include "stdafx.h"
#include <corecrt_wstdio.h>
#include <stdio.h>

SimulationArena::SimulationArena(const std::string path) {
    std::ifstream in(path);

    InitializeArena(in);
    ReadArena(in);  // Fill in data from stream
    in.close();
    DumpSimpleArena();  // Print out Arena
    ConvertIntoArena(true);
}

SimulationArena::~SimulationArena() {
    // Clean arenas
    for (auto i = 0; i < arena_x_size_; i++) {
        delete[] arena_[i];
    }
    delete[] arena_;

    for (auto i = 0; i < simple_arena_size_; i++) {
        delete[] simple_arena_[i];
    }
    delete[] simple_arena_;
}

boolean* SimulationArena::ScanWalls(const int x, const int y) const {
    return arena_[x][y].walls_;
}

boolean SimulationArena::InitializeArena(std::ifstream &stream) {
    stream >> arena_x_size_ >> arena_y_size_;
    simple_arena_size_ = arena_x_size_ * 2 + 1;
    // Handle Sizes

    arena_ = new TestArenaTile*[arena_x_size_];
    for (auto i = 0; i < arena_x_size_; i++) {
        arena_[i] = new TestArenaTile[arena_y_size_];
    }

    return b_true;
}

void SimulationArena::ReadArena(std::ifstream &stream) {
    simple_arena_ = new char*[simple_arena_size_+1];
    
    for (auto i = 0; i < simple_arena_size_; i++) {
        simple_arena_[i] = new char[arena_y_size_+1];
    }

    auto x = 0, y = 0;
    char c;
    while (stream.get(c)) {
        if (c == '#') c = ' ';
        if (c == '\n' || c == '\r') {
            continue;
        }
        simple_arena_[x++][y] = c;
        if (x == simple_arena_size_) {
            x = 0;
            y++;
        }
    }
}

void SimulationArena::DumpSimpleArena() const {
    FILE *f;
      auto err = fopen_s(&f, "c:\\Users\\Alex\\MazeMap\\MazeMapTests\\output.txt", "w");
      for (auto y = 0; y < arena_y_size_; y++) {
        for (auto x = 0; x < simple_arena_size_; x++) {
            // std::cout << (simple_arena_[x][y]);
            fprintf(f, "%c", simple_arena_[x][y]);
        }
        // std::cout << std::endl;
        fprintf(f, "\n");
    }
      fclose(f);
}

void SimulationArena::ModifyArena(const int x, const int y,
                                  const TestArenaTile value) const {
    if (x >= arena_x_size_) {
        std::cout << "X out of range: " << x;
    } else if (y >= arena_y_size_) {
        std::cout << "Y out of range: " << y;
    } else {
        arena_[x][y] = value;
    }
}

void SimulationArena::ConvertIntoArena(bool print_out_walls) const {
    boolean walls[4];
    for (auto y = 0; y < arena_y_size_; y++) {
        for (auto x = 0; x < arena_x_size_; x++) {
            walls[0] = (simple_arena_[2*x + 1][y] == '_');
            walls[1] = (simple_arena_[2*x + 2][y + 1] == '|');
            walls[2] = (simple_arena_[2*x + 1][y + 1] == '_');
            walls[3] = (simple_arena_[2*x][y+1] == '|');

            if (print_out_walls) {
                auto wall_sum = 0;
                for (auto test = 0; test < 4; test++) {
                    if (walls[test]) {
                        std::cout << "1";
                        wall_sum++;
                    } else {
                        std::cout << "0";
                    }
                }
                std::cout << "\t\t" << wall_sum << "\t\t"
                                    << x << "|" << y << std::endl;
            }

            ModifyArena(x, y, TestArenaTile(walls));
        }
    }
}
