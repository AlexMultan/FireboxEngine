#version 460 core
		
    in vec2 coords;
    in vec3 camPos;
    in float cellSize;
    out vec4 FragColor;

    const float gridSize = 100.0;

    float subcellSize = cellSize * 0.1;

    const vec3 subGridColor = vec3(0.3, 0.3, 0.3);
    const vec3 mainGridColor = vec3(0.55, 0.55, 0.55);

    const float maxFadeDistance = 25.0;

    void main() 
    {		
        float camDist = length(coords - camPos.xz);
        float opacityFalloff = smoothstep(1.0, 0.0, camDist / maxFadeDistance);

        vec2 cellUV = mod(coords, cellSize);
        vec2 subUV = mod(cellUV, subcellSize);

        float mainGridThickness = cellSize * 0.008;
        float subGridThickness = cellSize * 0.003;

        float mainLineX = step(cellUV.x, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.x);
        float mainLineY = step(cellUV.y, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.y);
        float isMainGrid = clamp(mainLineX + mainLineY, 0.0, 1.0);

        float subLineX = step(subUV.x, subGridThickness) + step(subcellSize - subGridThickness, subUV.x);
        float subLineY = step(subUV.y, subGridThickness) + step(subcellSize - subGridThickness, subUV.y);
        float isSubGrid = clamp(subLineX + subLineY, 0.0, 1.0);

        vec3 gridRGB = mix(subGridColor, mainGridColor, isMainGrid);
        float gridAlpha = clamp(isMainGrid + isSubGrid, 0.0, 0.2);
        
        FragColor = vec4(gridRGB * opacityFalloff, gridAlpha);
    }