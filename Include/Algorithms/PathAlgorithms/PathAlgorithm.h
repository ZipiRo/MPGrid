struct PathAlgorithm
{
    bool done = false;
    bool path_found = false;

    int path_length = 0;
    int visited_cells = 0;
    float elapsed_time = 0.0f;

    Color explored_color;
    Color frontier_color;
    Color backtrack_color;

    virtual void Init(const Grid &grid, Vector2i start, Vector2i end) = 0;
    virtual void Step(Grid &grid) = 0;
    virtual std::vector<Vector2i> ConstructPath() = 0;
};

struct PathAlgoithmEntry
{
    std::string abbr, name, desc, complexity, complete, weighted, optimal, data_structure, expands;
    std::function<std::unique_ptr<PathAlgorithm>()> Get;
};

#include "Depth-FirstSearch.h"
#include "Breadth-FirstSearch.h"
#include "RandomDFS.h"

std::vector<PathAlgoithmEntry> GetPathAlgorithms()
{
    std::vector<PathAlgoithmEntry> algorithms;
    PathAlgoithmEntry algorithm_entry; 

    algorithm_entry.abbr = DFS::abbr;
    algorithm_entry.name = DFS::name;
    algorithm_entry.desc = DFS::desc;
    algorithm_entry.complexity = DFS::complexity;
    algorithm_entry.complete = DFS::complete;
    algorithm_entry.weighted = DFS::weighted;
    algorithm_entry.optimal = DFS::optimal;
    algorithm_entry.data_structure = DFS::data_structure;
    algorithm_entry.expands = DFS::expands;
    algorithm_entry.Get = []() { return std::make_unique<DFS>(); };

    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = BFS::abbr;
    algorithm_entry.name = BFS::name;
    algorithm_entry.desc = BFS::desc;
    algorithm_entry.complexity = BFS::complexity;
    algorithm_entry.complete = BFS::complete;
    algorithm_entry.weighted = BFS::weighted;
    algorithm_entry.optimal = BFS::optimal;
    algorithm_entry.data_structure = BFS::data_structure;
    algorithm_entry.expands = BFS::expands;

    algorithm_entry.Get = []() { return std::make_unique<BFS>(); };

    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = RandomDFS::abbr;
    algorithm_entry.name = RandomDFS::name;
    algorithm_entry.desc = RandomDFS::desc;
    algorithm_entry.complexity = RandomDFS::complexity;
    algorithm_entry.complete = RandomDFS::complete;
    algorithm_entry.weighted = RandomDFS::weighted;
    algorithm_entry.optimal = RandomDFS::optimal;
    algorithm_entry.data_structure = RandomDFS::data_structure;
    algorithm_entry.expands = RandomDFS::expands;
    algorithm_entry.Get = []() { return std::make_unique<RandomDFS>(); };

    algorithms.push_back(algorithm_entry);

    return algorithms;
} 
