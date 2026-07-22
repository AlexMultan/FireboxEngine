#include "VertexArray.h"
#include "Rendering/Backends/OpenGL/OpenGLVertexArray.h"

Ref<Firebox::VertexArray> Firebox::VertexArray::Create()
{
    return CreateRef<OpenGLVertexArray>();
}
