#include "Renderer.h"

Renderer::Renderer()
{
  glEnable(GL_DEPTH_TEST);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer &ib, const Shader &shader) const
{
  shader.bind();
  va.bind();
  ib.bind();

  glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}