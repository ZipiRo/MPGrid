struct MazeAlgorithm
{
    bool done = false;

    Color primary_color;
    Color secondary_color;

    float elapsed_time = 0.0f;
    int carved_added_walls = 0;

    virtual void Init(const Grid &grid, Vector2i start) = 0;
    virtual void Step(Grid &grid) = 0;
};

struct MazeAlgorithmEntry
{
    std::string abbr, name, desc, rules, complexity, maze_type, perfect_maze, use_random, growth_style, bias, data_structure;
    std::function<std::unique_ptr<MazeAlgorithm>()> Get;
};

#include "RecursiveBactracking.h"
#include "RecursiveDivision.h"
#include "Prim.h"

std::vector<MazeAlgorithmEntry> GetMazeAlgorithms()
{
    std::vector<MazeAlgorithmEntry> algorithms;
    MazeAlgorithmEntry algorithm_entry; 

    algorithm_entry.abbr = RB::abbr;
    algorithm_entry.name = RB::name;
    algorithm_entry.desc = RB::desc;
    algorithm_entry.rules = RB::rules;
    algorithm_entry.complexity = RB::complexity;
    algorithm_entry.maze_type = RB::maze_type;
    algorithm_entry.perfect_maze = RB::perfect_maze;
    algorithm_entry.use_random = RB::use_random;
    algorithm_entry.growth_style = RB::growth_style;
    algorithm_entry.bias = RB::bias;
    algorithm_entry.data_structure = RB::data_structure;
    algorithm_entry.Get = [](){ return std::make_unique<RB>(); };

    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = RD::abbr;
    algorithm_entry.name = RD::name;
    algorithm_entry.desc = RD::desc;
    algorithm_entry.rules = RD::rules;
    algorithm_entry.complexity = RD::complexity;
    algorithm_entry.maze_type = RD::maze_type;
    algorithm_entry.perfect_maze = RD::perfect_maze;
    algorithm_entry.use_random = RD::use_random;
    algorithm_entry.growth_style = RD::growth_style;
    algorithm_entry.bias = RD::bias;
    algorithm_entry.data_structure = RD::data_structure;
    algorithm_entry.Get = [](){ return std::make_unique<RD>(); };

    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = Prim::abbr;
    algorithm_entry.name = Prim::name;
    algorithm_entry.desc = Prim::desc;
    algorithm_entry.rules = Prim::rules;
    algorithm_entry.complexity = Prim::complexity;
    algorithm_entry.maze_type = Prim::maze_type;
    algorithm_entry.perfect_maze = Prim::perfect_maze;
    algorithm_entry.use_random = Prim::use_random;
    algorithm_entry.growth_style = Prim::growth_style;
    algorithm_entry.bias = Prim::bias;
    algorithm_entry.data_structure = Prim::data_structure;
    algorithm_entry.Get = [](){ return std::make_unique<Prim>(); };

    algorithms.push_back(algorithm_entry);

    return algorithms;
} 
