#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int count) 
: count(count)
{
  glGenBuffers(1, &rendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void IndexBuffer::unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}