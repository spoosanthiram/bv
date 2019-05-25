#pragma once

#include "GeometryTypes.h"
#include "RenderObject.h"

class ShaderProgram;

class GraphicsObject
{
public:
  GraphicsObject(const std::string& file_path);
  ~GraphicsObject() = default;

  void render(const std::unique_ptr<ShaderProgram>& shader_program) const;

private:
  GraphicsGeometry read_model(const std::string& file_path) const;

private:
  RenderObject render_object_;
  RenderObject render_object2_;
};
