vertexes_.emplace_back(std::vector<float>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 3}));
vertexes_.emplace_back(std::vector<float>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.55, 2.3}));
vertexes_.emplace_back(std::vector<float>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.55, 2.3}));
vertexes_.emplace_back(std::vector<float>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.55, 2.3}));
vertexes_.emplace_back(std::vector<float>({7.6, 6.7, 0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.55, 2.3}));

edges_.emplace_back(&vertexes_[0], &vertexes_[1], 0.5);
edges_.emplace_back(&vertexes_[0], &vertexes_[2], 0.5);
edges_.emplace_back(&vertexes_[0], &vertexes_[3], 0.5);
edges_.emplace_back(&vertexes_[2], &vertexes_[3], 0.5);
edges_.emplace_back(&vertexes_[4], &vertexes_[0], 0.5);
edges_.emplace_back(&vertexes_[2], &vertexes_[4], 0.5);
