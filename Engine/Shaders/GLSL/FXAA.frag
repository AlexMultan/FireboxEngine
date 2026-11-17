#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D u_SceneColor;     // output of your lighting pass (LDR, gamma-corrected)
uniform float u_FXAASubpixShift = 1.0 / 4.0;
uniform float u_FXAASpanMax     = 8.0;
uniform float u_FXAAReduceMul   = 1.0 / 8.0;

#define FXAA_REDUCE_MIN (1.0 / 128.0)

vec3 FxaaPixelShader(sampler2D tex, vec2 uv, vec2 rcpFrame)
{
    // Offset UV to the north-west corner (replaces posPos.zw from the vertex shader).
    vec2 uvNW = uv - rcpFrame * (0.5 + u_FXAASubpixShift);

    vec3 rgbNW = textureLod(tex, uvNW, 0.0).rgb;
    vec3 rgbNE = textureLodOffset(tex, uvNW, 0.0, ivec2(1, 0)).rgb;
    vec3 rgbSW = textureLodOffset(tex, uvNW, 0.0, ivec2(0, 1)).rgb;
    vec3 rgbSE = textureLodOffset(tex, uvNW, 0.0, ivec2(1, 1)).rgb;
    vec3 rgbM  = textureLod(tex, uv, 0.0).rgb;

    const vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));

    float dirReduce = max(
        (lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * u_FXAAReduceMul),
        FXAA_REDUCE_MIN);
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

    dir = clamp(dir * rcpDirMin, vec2(-u_FXAASpanMax), vec2(u_FXAASpanMax)) * rcpFrame;

    vec3 rgbA = 0.5 * (
        textureLod(tex, uv + dir * (1.0 / 3.0 - 0.5), 0.0).rgb +
        textureLod(tex, uv + dir * (2.0 / 3.0 - 0.5), 0.0).rgb);

    vec3 rgbB = rgbA * 0.5 + 0.25 * (
        textureLod(tex, uv + dir * (0.0 / 3.0 - 0.5), 0.0).rgb +
        textureLod(tex, uv + dir * (3.0 / 3.0 - 0.5), 0.0).rgb);

    float lumaB = dot(rgbB, luma);
    if (lumaB < lumaMin || lumaB > lumaMax)
        return rgbA;
    return rgbB;
}

void main()
{
    vec2 rcpFrame = 1.0 / vec2(textureSize(u_SceneColor, 0));
    FragColor = vec4(FxaaPixelShader(u_SceneColor, TexCoords, rcpFrame), 1.0);
}