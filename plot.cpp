#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>

int seed=46;
std::vector<std::pair<int, int>> generate_users(int num_of_users, int area) {
    std::vector<std::pair<int, int>> users;
    std::mt19937 gen(seed);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, area);

    for (int i = 0; i < num_of_users; ++i) {
        int x = round(dis(gen));
        int y = round(dis(gen));
        std::pair<int, int> user(x, y);
        users.push_back(user);
    }

    return users;
}

std::vector<std::pair<int, int>> generate_points(int num_points, int area, int min_distance) {
    std::vector<std::pair<int, int>> points;
     std::mt19937 gen(seed);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, area);

    while (points.size() < num_points) {
        int x = round(dis(gen));
        int y = round(dis(gen));
        std::pair<int, int> point(x, y);

        bool valid = true;
        for (const auto& existing_point : points) {
            double distance = sqrt(pow(point.first - existing_point.first, 2) +
                                   pow(point.second - existing_point.second, 2));
            if (distance < min_distance) {
                valid = false;
                break;
            }
        }

        if (valid) {
            points.push_back(point);
        }
    }
    return points;
}

void save_data(const std::vector<std::pair<int, int>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& point : data) {
            file << point.first << " " << point.second << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    int num_of_users = 1000;
    int num_points = 22;
    int area = 4000;
    int min_distance = 200;

    // Generate users and points
    std::vector<std::pair<int, int>> users = generate_users(num_of_users, area);
    std::vector<std::pair<int, int>> points = generate_points(num_points, area, min_distance);

    // Save data to files
    save_data(users, "users.dat");
    save_data(points, "points.dat");

    return 0;
}
