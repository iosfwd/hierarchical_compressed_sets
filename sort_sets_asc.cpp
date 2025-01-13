#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>

#include <cstdint>

template<typename T>
std::vector<std::tuple<std::size_t, std::size_t>> get_color_set_lengths_and_indices(const char* input_filename) {
    std::vector<std::tuple<std::size_t, std::size_t>> cs_indices;

    std::ifstream ifs(input_filename, std::ios::binary);
    const auto begin = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    const auto end = ifs.tellg();
    const std::size_t file_length = end - begin;
    ifs.seekg(0);
    const std::size_t text_length = file_length / sizeof(T);

    std::size_t i = 0;
    while (i < text_length) {
        std::size_t cs_sz = 0;
        ifs.read(reinterpret_cast<char*>(&cs_sz), sizeof(T));
        cs_indices.push_back({cs_sz, i});
        ++i;
        T elem = 0;
        for (std::size_t j = 0; j < cs_sz; ++j) {
            ifs.read(reinterpret_cast<char*>(&elem), sizeof(T));
            ++i;
        }
    }
    ifs.close();

    return cs_indices;
}

template<typename T>
void write_sets_asc(const char* input_filename, const char* output_filename) {
    std::ifstream ifs(input_filename, std::ios::binary);
    std::ofstream ofs(output_filename, std::ios::binary);

    auto len_idx_vec = get_color_set_lengths_and_indices<std::uint32_t>(input_filename);
    std::sort(len_idx_vec.begin(), len_idx_vec.end(), std::less<std::tuple<std::size_t, std::size_t>>());

    for (std::size_t i = 0; i < len_idx_vec.size(); ++i) {
        const auto& [len, idx] = len_idx_vec[i];
        ifs.seekg(idx * sizeof(T));
        T color_set_sz = 0;
        ifs.read(reinterpret_cast<char*>(&color_set_sz), sizeof(T));
        std::vector<T> color_set(color_set_sz, 0);
        ifs.read(reinterpret_cast<char*>(color_set.data()), sizeof(T) * color_set_sz);
        ofs.write(reinterpret_cast<char*>(&color_set_sz), sizeof(T));
        ofs.write(reinterpret_cast<char*>(color_set.data()), sizeof(T) * color_set_sz);
    }
    ifs.close();
    ofs.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::fprintf(stderr, "usage: %s [input file] [output file]\n", argv[0]);
        std::exit(EXIT_FAILURE);
    }

    write_sets_asc<std::uint32_t>(argv[1], argv[2]);
}
