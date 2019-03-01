#include "stdafx.h"
#include "CppUnitTest.h"

#include <strsafe.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MazeMapTests
{
    TEST_CLASS(ArenaTests)
    {
    public:

        TEST_METHOD(TestCreateMap)
        {
            map* map = CreateMap();

            Assert::IsNotNull(map);
            Assert::AreEqual(1, map->max_number);
            Assert::IsNull(map->floor);
            Assert::IsNull(map->robot_tile);
        }

        TEST_METHOD(TestInitializeRobot100) {
            wchar_t status[1024];

            for (int i=0; i<100; i++) {
                map* map = CreateMap();
                InitializeRobotTile(map);


                if (map->robot_tile->tile->X != 0) {
                    StringCbPrintfW(status, 2048, L"Current run: %i", i);

                }
                
                Assert::AreEqual(0, map->robot_tile->tile->X, status);
                Assert::AreEqual(0, map->robot_tile->tile->Y, status);
            }

        }

        TEST_METHOD(CreateNodeOnPosition) {
            wchar_t status[1024];

            for (int i = 0; i < 5; i++) {
                //map *map = CreateMap();

                node*n = CreateMapNodeOnPosition(0, 0);

                if (n->tile->X != 0 || n->tile->Y != 0) {
                    StringCbPrintfW(status, 2048, L"Current run: %i", i);

                }
                Assert::AreEqual(0, n->tile->X, status);
                Assert::AreEqual(0, n->tile->Y, status);
            }
        }

    };
}