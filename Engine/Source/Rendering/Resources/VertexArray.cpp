#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Ref<Firebox::VertexArray> Firebox::VertexArray::Create()
{
    return CreateRef<OpenGLVertexArray>();
}
