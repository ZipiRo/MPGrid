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
    std::string abbr, name, desc, complexity, complete, weighted, optimal, data_structure, expands, hdocument;
    std::function<std::unique_ptr<PathAlgorithm>()> Get;
};

#include "Depth-FirstSearch.h"
#include "Breadth-FirstSearch.h"
#include "RandomDFS.h"

std::vector<PathAlgoithmEntry> GetPathAlgorithms()
{
    std::vector<PathAlgoithmEntry> algorithms;
    PathAlgoithmEntry algorithm_entry; 
    
    algorithm_entry.abbr = "DFS";
    algorithm_entry.name = "Depth-First Search";
    algorithm_entry.desc = "Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along one branch before backtracking.";
    algorithm_entry.complexity = "Time Complexity: O(C + E) \nSpace Complexity O(C) \nC - cells \nE - connections";
    algorithm_entry.complete = "Sometimes";
    algorithm_entry.weighted = "No";
    algorithm_entry.optimal = "No";
    algorithm_entry.data_structure = "Stack / Recursion";
    algorithm_entry.expands = "Deep-first";
    algorithm_entry.hdocument = "DFS_Algo";
    algorithm_entry.Get = []() { return std::make_unique<DFS>(); };
    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = "BFS";
    algorithm_entry.name = "Breadth-First Search";
    algorithm_entry.desc = "Breadth-First Search (BFS) is a graph traversal algorithm that explores nodes level by level, visiting all neighbors of a node before moving deeper.";
    algorithm_entry.complexity = "Time Complexity: O(C + E) \nSpace Complexity O(C) \nC - cells \nE - connections";
    algorithm_entry.complete = "Yes";
    algorithm_entry.weighted = "No";
    algorithm_entry.optimal = "Yes (unweighted graphs)";
    algorithm_entry.data_structure = "Queue";
    algorithm_entry.expands = "Uniformly";
    algorithm_entry.hdocument = "BFS_Algo";
    algorithm_entry.Get = []() { return std::make_unique<BFS>(); };
    algorithms.push_back(algorithm_entry);

    algorithm_entry.abbr = "RDFS";
    algorithm_entry.name = "Random Depth-First Search";
    algorithm_entry.desc = "Random Direction DFS (RDFS) is a variation of Depth-First Search where, instead of visiting neighbors in a fixed order, the algorithm chooses a random order each time.";
    algorithm_entry.complexity = "Time Complexity: O(C + E) \nSpace Complexity O(C) \nC - cells \nE - connections";
    algorithm_entry.complete = "Sometimes";
    algorithm_entry.weighted = "No";
    algorithm_entry.optimal = "No (Random)";
    algorithm_entry.data_structure = "Stack / Recursion";
    algorithm_entry.expands = "Deep-first (Random)";
    algorithm_entry.hdocument = "RDFS_Algo";
    algorithm_entry.Get = []() { return std::make_unique<RandomDFS>(); };
    algorithms.push_back(algorithm_entry);

    return algorithms;
} 
