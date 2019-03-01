#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdio>
#include <corecrt_memcpy_s.h>
#include <stdio.h>
#include <cstdarg>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MazeMapTests
{		
	TEST_CLASS(GeneralTests)
	{
    private:

        SimulationArena *arena = nullptr;
        map* robot_map;

        FILE *f;
        const char *OutputFile = "c:\\Users\\Alex\\MazeMap\\MazeMapTests\\test_output.txt";
        const char *Maze1 = "c:\\Users\\Alex\\MazeMap\\MazeMapTests\\maze1.txt";

        void LogInfo(char const* const Format, ...) {
            va_list vl;
            __crt_va_start(vl, Format);
            fopen_s(&f, OutputFile, "a+");
            vfprintf(f, Format, vl);
            __crt_va_end(vl);
            fclose(f);
        }

	public:
		TEST_METHOD_INITIALIZE(TestInitialize) {
            fopen_s(&f, OutputFile, "w");
            fclose(f);

            robot_map = CreateMap();
            InitializeRobotTile(robot_map);
		}

#pragma region TestFullArena
  //      void UpdateTileWalls(SimulationArena &arena, int x, int y) const {

  //          UpdateTile(robot_map->robot_tile->tile, arena.ScanWalls(x, y));
  //      }

  //      void UpdateRobotPosition(int &x, int &y, const direction new_direction) {

  //          LogInfo("(x=%i, y=%i) (rx=%i, ry=%i) (dir=%i)\n", 
  //              x, 
  //              y, 
  //              robot_map->robot_tile->tile->X, 
  //              robot_map->robot_tile->tile->Y, 
  //              new_direction);

  //          x = XInDirection(x, (direction)(new_direction & ~override));
  //          y = YInDirection(y, (direction)(new_direction & ~override));

		//}

  //      void CreateNewTileUnderRobot(int x, int y, direction direction) {
		// 
  //          tile *t = CreateMapTile();
  //          t->X = x;
  //          t->Y = y;

  //          node *n = CreateNode(standard_tile, t);
  //          const bool result = AddTileInDirection(robot_map, direction, n);
  //          if (result == false) {
  //              // Clean up the mess
  //              DestroyNode(n); n = NULL;
  //              DestroyTile(t); t = NULL;
  //          }
		//}

  //      void MoveRobotIntoNewPosition(direction d) {
		//    
  //          d = (direction)(d & ~override);
  //          robot_map->robot_tile = robot_map->robot_tile->tile->neighbors[d];
		//}

        boolean *ScanWalls(int x, int y) {
            return arena->ScanWalls(x, y);
		}

#pragma endregion

		TEST_METHOD(TestFullArena)
		{
			// TODO: Testcode hier eingeben
            arena = new SimulationArena(Maze1);

            auto robot_x = 0, robot_y = 0;
            int steps = 0;
            do {
                MoveRobotToNextPosition(robot_map, arena->ScanWalls(robot_x, robot_y));

                LogInfo("(%d, %d) -> (%d, %d)\n",
                    robot_x, robot_y,
                    robot_map->robot_tile->tile->X,
                    robot_map->robot_tile->tile->Y);

                robot_x = robot_map->robot_tile->tile->X;
                robot_y = robot_map->robot_tile->tile->Y;

            } while ((robot_x != 0 || robot_y != 0) && ++steps < 200);

            Assert::AreNotEqual(200, steps, L"Steps limit exceeded!");

            Assert::AreEqual(0, robot_x);
            Assert::AreEqual(0, robot_y);
            fclose(f);
		}

	};
}