#version 330

// Fragment shader


// These get passed in from the vertex shader and are interpolated (varying) properties,
// so they change for each pixel across the triangle:
in vec4 interpSurfPosition;
in vec3 interpSurfNormal;

// Light Position in world coordinates
uniform vec4 lightPosition;

//Textures
uniform samplerCube environmentMap;

// Material Properties
uniform float eta; // The eta value to use initially. This reflects all light wavelengths in the same direction
uniform vec3 glassEta; // Contains one eta for each color channel (use eta.r, eta.g, eta.b in your code)
uniform float glassR0; // The Fresnel reflectivity when the incident angle is 0

uniform vec3 eye_world;

// This is an out variable for the final color we want to render this fragment.
out vec4 fragColor;


float orenNayar(vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float albedo) {
    float sigma2 = roughness * roughness;

    float A = 1 - 0.5 * (sigma2 / (sigma2 + 0.33));
    float B = 0.45*(sigma2 / (sigma2 + 0.09));
}

void main() {

	// TODO: fill this in

    vec4 refractedColor = vec4(0);

	vec3 n = normalize(interpSurfNormal);
	vec3 e = normalize(eye_world - vec3(interpSurfPosition));
	vec3 rRefractedTexCoord = normalize(refract(-e, n, glassEta.r));
    vec3 gRefractedTexCoord = normalize(refract(-e, n, glassEta.g));
    vec3 bRefractedTexCoord = normalize(refract(-e, n, glassEta.b));
	refractedColor.r = texture(environmentMap, rRefractedTexCoord).r;
    refractedColor.g = texture(environmentMap, gRefractedTexCoord).g;
    refractedColor.b = texture(environmentMap, bRefractedTexCoord).b;

    // vec3 refractedTexCoord = normalize(refract(-e, n, et))

    vec3 direction = reflect(-e, interpSurfNormal);
    vec4 reflectedColor = texture(environmentMap, direction);

    float f = glassR0 + (1 - glassR0) * pow((1 - clamp(dot(normalize(vec3(interpSurfPosition)), normalize(interpSurfNormal)), 0, 1)), 5);

	fragColor = mix(reflectedColor, refractedColor, f);

}
