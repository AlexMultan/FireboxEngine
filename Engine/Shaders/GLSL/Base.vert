#version 460 core

// Base.vert - shared vertex stage for all fullscreen/deferred passes.
// Do not add per-shader variants; extend the fragment shader instead.

    layout (location = 0) in vec3 aPos;
    layout (location = 2) in vec2 aTexCoords;
    
    out vec2 TexCoords;

    void main()
    {
        TexCoords = aTexCoords;
        gl_Position = vec4(aPos, 1.0);
    }