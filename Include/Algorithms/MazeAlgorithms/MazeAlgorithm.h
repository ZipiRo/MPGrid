struct MazeAlgorithm
{
    bool done = false;

    Color primary_color;
    Color secondary_color;

    float elapsed_time = 0.0f;

    virtual void Init(const Grid &grid, Vector2i start) = 0;
    virtual void Step(Grid &grid) = 0;
};

struct MazeAlgorithmEntry
{
    std::string abbr, name, desc, rules, complexity, maze_type, perfect_maze, use_random, growth_style, bias, data_structure, hdocument;
    std::function<std::unique_ptr<MazeAlgorithm>()> Get;
};

#include "RecursiveBactracking.h"
#include "RecursiveDivision.h"
#include "Prim.h"

std::vector<MazeAlgorithmEntry> GetMazeAlgorithms()
{
    std::vector<MazeAlgorithmEntry> algorithms;
    MazeAlgorithmEntry algorithm_entry;      

    algorithm_entry.abbr = "RB";
    algorithm_entry.name = "Recursive Backtrack";
    algorithm_entry.desc = "Recursive Backtracker (RB) is a depth-first maze generation algorithm that moves forward through random unvisited neighbors, carving paths, and backtracks when it hits a dead end until all cells are visited.";
    algorithm_entry.rules = "1.Use a filled grid (all walls) for the algorithm to work";
    algorithm_entry.complexity = "Time Complexity: O(C + E) \nSpace Complexity: O(C) \nC - cells \nE - connections";
    algorithm_entry.maze_type = "DFS-based";
    algorithm_entry.perfect_maze = "Yes";
    algorithm_entry.use_random = "Yes";
    algorithm_entry.growth_style = "Deep path carving";
    algorithm_entry.bias = "Long corridors";
    algorithm_entry.data_structure = "Stack / Recursion";
    algorithm_entry.hdocument = "RB_Algo";
    algorithm_entry.Get = [](){ return std::make_unique<RB>(); };
    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = "RD";
    algorithm_entry.name = "Recursive Division";
    algorithm_entry.desc = "Recursive Division (RD) is a maze generation algorithm that repeatedly splits an area with walls, places a single passage through each wall, and recursively applies the same process to the resulting sub-sections until the maze is fully partitioned.";
    algorithm_entry.rules = "1.Use a clear grid (no walls) for the algorithm to work";
    algorithm_entry.complexity = "Time Complexity: O(C * logC) \nSpace Complexity: O(logC) \nC - cells \nE - connections";
    algorithm_entry.maze_type = "Divide-and-conquer";
    algorithm_entry.perfect_maze = "Yes";
    algorithm_entry.use_random = "Yes (Wall/Door Placemant)";
    algorithm_entry.growth_style = "Spliting regions with walls";
    algorithm_entry.bias = "Structured";
    algorithm_entry.data_structure = "Stack (Regions)";
    algorithm_entry.hdocument = "RD_Algo";
    algorithm_entry.Get = [](){ return std::make_unique<RD>(); };
    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = "Prim";
    algorithm_entry.name = "Prim";
    algorithm_entry.desc = "Prim's algorithm (Prim) is a method for building a maze by starting from a cell and gradually expanding outward, always choosing the next cell through the smallest available connection until the whole area is connected.";
    algorithm_entry.rules = "1.Use a filled grid (all walls) for the algorithm to work";
    algorithm_entry.complexity = "Time Complexity: O(E * logC) \nSpace Complexity: O(C) \nC - cells \nE - connections";
    algorithm_entry.maze_type = "Randomized";
    algorithm_entry.perfect_maze = "Yes";
    algorithm_entry.use_random = "Yes";
    algorithm_entry.growth_style = "Outward from frontier";
    algorithm_entry.bias = "Balanced";
    algorithm_entry.data_structure = "Priority queue";
    algorithm_entry.hdocument = "PRIM_Algo";
    algorithm_entry.Get = [](){ return std::make_unique<Prim>(); };
    algorithms.push_back(algorithm_entry);

    return algorithms;
} 
