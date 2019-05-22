import numpy as np

if __name__ == "__main__":
  vertices = np.load("vertex_buffer.p", allow_pickle=True)
  indices = np.load("index_buffer.p", allow_pickle=True)

  with open("model.txt", "w") as file:
    file.write(str(vertices.size))
    file.write("\n")
    for vertex in vertices:
      for item in vertex:
        for val in item:
          file.write(str(val))
          file.write(",")
      file.write("\n")

    file.write(str(indices.shape[0]))
    file.write("\n")
    for index in indices:
      for val in index:
        file.write(str(val))
        file.write(",")
      file.write("\n")
