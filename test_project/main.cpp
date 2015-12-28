//
//  main.cpp
//  test_project
//
//  Created by 安田洋介 on 11/15/15.
//  Copyright © 2015 安田洋介. All rights reserved.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "scc.h"

using namespace std;

TEST_CASE("scc"){
    vector<vector<int>> sccs = exec_scc("SCC.txt");
    REQUIRE(sccs[0].size() == 434821);
    REQUIRE(sccs[1].size() == 968);
    REQUIRE(sccs[2].size() == 459);
    REQUIRE(sccs[3].size() == 313);
    REQUIRE(sccs[4].size() == 211);
}