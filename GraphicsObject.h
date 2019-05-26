#pragma once

#include "GeometryTypes.h"
#include "RenderObject.h"
#include "RenderObject2.h"

class ShaderProgram;

class GraphicsObject {
public:
  GraphicsObject(const std::string &file_path);
  ~GraphicsObject() = default;

  void set_highlight_color(const Point4f &color) {
    render_object2_.set_color(color);
  }

  void render(const std::unique_ptr<ShaderProgram> &shader_program) const;
  void
  render_highlight(const std::unique_ptr<ShaderProgram> &shader_program) const;

private:
  GraphicsGeometry read_model(const std::string &file_path) const;

private:
  RenderObject render_object_;
  RenderObject2 render_object2_;
};
