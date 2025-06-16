#include "consumer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <stdexcept>



struct Node {
    std::array<double, 3> coords;  // Fixed-size container for {x, y, z}

    Node(const double x, const double y, const double z) : coords{x, y, z} {}

    double& x() { return coords[0]; }
    double& y() { return coords[1]; }
    double& z() { return coords[2]; }

    [[nodiscard]] const double& x() const { return coords[0]; }
    [[nodiscard]] const double& y() const { return coords[1]; }
    [[nodiscard]] const double& z() const { return coords[2]; }
};

struct Element {
    std::array<int, 4> elem;

    Element(const int n1, const int n2, const int n3, const int n4) : elem{n1, n2, n3, n4} {}
};

struct Mesh {
    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::vector<double> property;
};

template<typename T>
bool parse_line_data(std::istringstream& line_iss, int line_number, T& result);

// Specialization for Node
template<>
bool parse_line_data<Node>(std::istringstream& line_iss, int line_number, Node& result) {
    float x, y, z;
    if (!(line_iss >> line_number >> x >> y >> z)) {
        return false;
    }
    result = Node(x, y, z);
    return true;
}

// Specialization for Element
template<>
bool parse_line_data<Element>(std::istringstream& line_iss, int line_number, Element& result) {
    // Assuming Element has different parsing logic
    int node1, node2, node3, node4;
    if (!(line_iss >> line_number >> node1 >> node2 >> node3 >> node4)) {
        return false;
    }
    result = Element(node1, node2, node3, node4);
    return true;
}

// Specialization for double
template<>
bool parse_line_data<double>(std::istringstream& line_iss, int line_number, double& result) {
    if (!(line_iss >> result)) {  // No line_number for simple values
        return false;
    }
    return true;
}


template <typename T>
void read_lines(std::ifstream& file, std::vector<T>& my_array, int array_size) {
    std::string line;
    
    // Reserve space for efficiency
    my_array.reserve(array_size);

    // Parse the nodes
    for (int i = 0; i < array_size; ++i) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Unexpected end of file while reading nodes");
        }

        std::istringstream line_iss(line);
        int line_number;
        T item;

        if (!parse_line_data(line_iss, line_number, item)) {
            throw std::runtime_error("Failed to parse node data at line " + std::to_string(i + 1));
        }

        // Verify node number is sequential starting from 1
        if (line_number != i + 1) {
            throw std::runtime_error("Line number mismatch: expected " + std::to_string(i + 1) +
                                    ", got " + std::to_string(line_number));
        }

        // Store coordinates (not the node number)
        my_array.emplace_back(std::move(item));
    }
}

Mesh work_parser(const std::string& file_path) {
    Mesh mesh{};

    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    std::string line;

    // Look for the RZ keyword line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        int first_param, node_count;

        if (iss >> keyword >> first_param >> node_count) {
            if (keyword == "RZ" && first_param == 1) {
                std::cout << "Found RZ section with " << node_count << " nodes" << std::endl;

                read_lines(file, mesh.nodes, node_count);

                std::cout << "Successfully parsed " << mesh.nodes.size() << " nodes" << std::endl;
                break; // Found and processed RZ section
            }
        }
    }

    if (mesh.nodes.empty()) {
        std::cout << "Warning: No RZ section found in file: " << file_path << std::endl;
    }

    file.close();
    return mesh;
}

void work_3d_image_generator(const Mesh& mesh, std::byte* buffer) {
    std::cout << "Mesh: " << mesh.nodes.size() << std::endl;
    std::cout << "Buffer: " << buffer << std::endl;
}

void png_image_saver(const std::string& file_path, const std::byte* buffer) {
    std::cout << "Saving file: " << file_path << std::endl;
    std::cout << "Buffer: " << buffer << std::endl;
}

namespace list {
    void work_consumer(WorkQueue& queue) {
        std::string file_path{};
        // make a waiting pop from the queue
        while (queue.pop(file_path)) {
            std::cout << "work_consumer - pop new file path: " << file_path << std::endl;
            try {
                Mesh mesh = work_parser(file_path);
                std::byte buffer[1024];
                work_3d_image_generator(mesh, buffer);
                png_image_saver(file_path, buffer);
            } catch (const std::exception& e) {
                std::cerr << "Error processing file " << file_path << ": " << e.what() << std::endl;
            }
        }
        std::cout << "work_consumer - end of cycle with value: " << file_path << std::endl;
    }
}