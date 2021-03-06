#version 330

// Fragment shader

uniform vec3 ambientReflectionCoeff;
uniform vec3 ambientLightIntensity;
uniform sampler2D _normalMap;

in vec3 position_world, normal_world;

uniform vec3 eye_world;

uniform int hasTexture;
uniform vec4 materialColor;
uniform sampler2D textureSampler;
in vec2 texture_coordinates;

// Light Position in world coordinates
vec3 lightPosition = eye_world + vec3(-20, 20, 20);

// This is an out variable for the final color we want to render this fragment.
out vec4 fragColor;

vec3 orenNayar(vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float albedo) {
    float sigma2 = roughness * roughness;
    float pi = 3.1415926535;
    vec3 L = lightDirection;
    vec3 V = viewDirection;
    vec3 N = surfaceNormal;

    float A = (1 - 0.5 * (sigma2 / (sigma2 + 0.33)) + 0.17 * albedo * sigma2 / (sigma2 + 0.13)) / pi;
    float B = 0.45*(sigma2 / (sigma2 + 0.09)) / pi;
    
    float s = dot(L, V) - dot(N, L) * dot(N, V);
    float t = mix(1.0, max(dot(N, L), dot(N, V)), step(0.0, s));
    
    return vec3(albedo * dot(N, L) * (A + B * s / t));
}

void main () {
    


    vec4 color = materialColor * (1 - hasTexture) + hasTexture * texture(textureSampler, texture_coordinates );

    // vec4 color = texture(textureSampler, texture_coordinates );
    // vec4 color = materialColor;

    vec3 newNormal = texture(_normalMap, texture_coordinates).rgb;

    vec3 L = normalize(position_world - lightPosition);
    vec3 H = normalize(L + normalize(eye_world - position_world));
    
    vec3 E = normalize(eye_world - position_world);
    // vec3 N = normalize(normalize(normal_world) + normalize(newNormal));
    vec3 N = normalize(normal_world);
    // Ambient

    vec3 ambient = ambientReflectionCoeff * ambientLightIntensity;
    vec3 diffuse = orenNayar(L, E, N, 5, 0.8);
    
    // materialColor = ambient + diffuse;    


    fragColor = mix(vec4(ambient + diffuse, 1.0), color, 0.4);
    
    // vec4(ambient + diffuse, color.a);
	
}

