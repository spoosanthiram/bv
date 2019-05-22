#include <iostream>
#include <fstream>
#include <string>

int main()
{
  constexpr const char* TEXT_FILE = "model.txt";
  constexpr const char* BINARY_FILE = "model.bin";

  std::ifstream txt_stream{TEXT_FILE};
  if (!txt_stream) {
    std::cerr << "Could not open " << TEXT_FILE << "\n";
    return 1;
  }

  std::ofstream bin_stream{BINARY_FILE, std::ios::binary};
  if (!bin_stream) {
    std::cerr << "Could not create " << BINARY_FILE << "\n";
    return 1;
  }

  // number of vertices
  std::string line;
  std::getline(txt_stream, line);
  uint32_t num_vertices = std::stoi(line);
  bin_stream.write(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));

  // vertices
  for (int i = 0; i < num_vertices; ++i) {
    std::getline(txt_stream, line);
    size_t prev_index = 0;
    size_t index = 0;
    while ((index = line.find(',', prev_index)) != std::string::npos) {
      auto val_str = line.substr(prev_index, index);
      auto val = std::stof(val_str);
      bin_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
      prev_index = index + 1;
    }
  }

  // indices
  std::getline(txt_stream, line);
  uint32_t num_triangles = std::stoi(line);
  bin_stream.write(reinterpret_cast<char*>(&num_triangles), sizeof(num_triangles));

  for (int i = 0; i < num_triangles; ++i) {
    std::getline(txt_stream, line);
    size_t prev_index = 0;
    size_t index = 0;
    while ((index = line.find(',', prev_index)) != std::string::npos) {
      auto val_str = line.substr(prev_index, index);
      auto val = std::stoi(val_str);
      bin_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
      prev_index = index + 1;
    }
  }

  return 0;
}
