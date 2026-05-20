class BFS : public PathAlgorithm
{
private:
    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<Vector2i>> parent;
    std::queue<Vector2i> queue;
    Vector2i start, end;

public:
    BFS() {}

    void Init(const Grid &grid, Vector2i start, Vector2i end) override
    {
        this->start = start;
        this->end = end;

        done = false;
        path_found = false;
        
        path_length = 0;
        elapsed_time = 0.0f;
        visited_cells = 0;

        visited = std::vector<std::vector<bool>>(grid.GetSize().y, std::vector<bool>(grid.GetSize().x));
        parent = std::vector<std::vector<Vector2i>>(grid.GetSize().y, std::vector<Vector2i>(grid.GetSize().x));

        queue.push(start);
        visited[start.y][start.x] = true;
    }

    void Step(Grid &grid) override
    {
        if (queue.empty())
        {
            done = true;
            return;
        }

        Vector2i current = queue.front();
        queue.pop();

        grid.SetCell(current.x, current.y, CELL_NONE, explored_color);

        visited_cells++;

        if (current == end)
        {
            path_found = true;
            return;
        }

        for (const auto &direction : directions)
        {
            Vector2i next = current + direction;

            if (next.x < 0 || next.y < 0 || next.x >= grid.GetSize().x || next.y >= grid.GetSize().y)
                continue;

            if (grid.Get(next.x, next.y).type != CELL_WALL && !visited[next.y][next.x])
            {
                grid.SetCell(next.x, next.y, CELL_NONE, frontier_color);
                parent[next.y][next.x] = current;

                visited[next.y][next.x] = true;

                queue.push(next);
            }
        }
    }

    std::vector<Vector2i> ConstructPath() override
    {
        std::vector<Vector2i> path;
        Vector2i current = end;

        while (current != start)
        {
            current = parent[current.y][current.x];
            if (current == start)
                break;
            path.push_back(current);
        }

        std::reverse(path.begin(), path.end());
        path_length = path.size();
        return path;
    }
};