#version 460 core
		
    layout(location = 0) in vec3 aPos;
    layout(location = 2) in vec2 aTexCoords;
        
    uniform mat4 u_ViewProjection;
    uniform mat4 u_Model;

    out vec2 TexCoords;

    void main() 
    {	
        TexCoords = aTexCoords;
        gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    }