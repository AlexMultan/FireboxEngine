#version 460 core
		
    layout(location = 0) in vec3 aPos;

    const float gridSize = 100.0;
        
    uniform mat4 u_ViewProjection;
    uniform mat4 u_Model;
    uniform vec3 u_CamPos;
    uniform float u_CellSize;
    out vec2 coords;
    out vec3 camPos;
    out float cellSize;

    void main() 
    {	
        vec4 worldPos = vec4(aPos, 1.0);
        worldPos.xyz *= gridSize;
        worldPos.xz += u_CamPos.xz;

        gl_Position = u_ViewProjection * u_Model * worldPos;
        coords = worldPos.xz;
        camPos = u_CamPos;
        cellSize = u_CellSize;
    }