cmake_minimum_required(VERSION 3.27)
project(PC_template)

set(CMAKE_CXX_STANDARD 20)

include_directories(templates)

add_executable(PC_template
        templates/digital_dp.cpp
        templates/FenwickTree.h
        main.cpp
        templates/SegmentTree.h
        templates/Prime.h
        templates/pc.h
        templates/Trie.h
        templates/LCA.h
        templates/Flow.h
        templates/Fraction.h
        templates/Bit.h
        templates/ShortestPath.h
        templates/SafeCal.h
        templates/matrix.h
        templates/exmath.h
        templates/Zfunc.h
        templates/DSU.h
        templates/SCC.h
        templates/hash.h
        templates/KMP.h
        templates/LinearBasis.h
)
