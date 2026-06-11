#include "VertexArray.h"
#include "Engine/Platform/OpenGL/OpenGLVertexArray.h"

Ref<Firebox::VertexArray> Firebox::VertexArray::Create()
{
    return CreateRef<OpenGLVertexArray>();
}
