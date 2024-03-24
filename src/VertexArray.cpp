#include "VertexArray.h"

#include <GL/glew.h>
#include <vector>

VertexArray::VertexArray()  
{
  glGenVertexArrays(1, &rendererID);
  glBindVertexArray(rendererID);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::bind() const
{
  glBindVertexArray(rendererID);
}

void VertexArray::unbind() const 
{
  glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
  bind();
  vb.bind();
  const std::vector<VertexBufferElement> &elements = layout.getElements();

  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const VertexBufferElement &element = elements.at(i);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
    offset += element.count*VertexBufferElement::getSizeOfType(element.type);
  }
}