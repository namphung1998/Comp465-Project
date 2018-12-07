#version 330

// Fragment shader

// Textures
uniform sampler2D tex;

uniform vec3 eye_world;

// reflection coefficients
uniform vec3 ambientReflectionCoeff;
uniform vec3 diffuseReflectionCoeff;
uniform vec3 specularReflectionCoeff;
uniform float specularExponent;

// light intensity
uniform vec3 ambientLightIntensity;
uniform vec3 diffuseLightIntensity;
uniform vec3 specularLightIntensity;

uniform vec4 lightPosition;
// These get passed in from the vertex shader and are interpolated (varying) properties
// change for each pixel across the triangle:
in vec4 interpSurfPosition;
in vec3 interpSurfNormal;



// This is an out variable for the final color we want to render this fragment.
out vec4 fragColor;


void main() {

    // Start with black and then add lighting to the final color as we calculate it
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	vec3 L = normalize(vec3(lightPosition - interpSurfPosition));
	vec3 H = normalize(L + normalize(eye_world - vec3(interpSurfPosition)));
    // TODO: Calculate ambient, diffuse, and specular lighting for this pixel based on its position, normal, etc.
	vec3 ambient = ambientReflectionCoeff * ambientLightIntensity;

	vec4 color = texture(tex, vec2(clamp(dot(interpSurfNormal, L), 0, 1), 0));

	vec3 diffuse = diffuseReflectionCoeff * diffuseLightIntensity * vec3(color);

	color = texture(tex, vec2(clamp(pow(dot(H, interpSurfNormal), specularExponent), 0, 1)));

	vec3 specular = specularReflectionCoeff * specularLightIntensity * vec3(color);
    
	finalColor += ambient + diffuse + specular;
    
	
    fragColor.rgb = finalColor;
	// fragColor.rgb = mix(finalColor.rgb, color.rgb, 1.0);
    
	// Tell OpenGL to use the r,g,b compenents of finalColor for the color of this fragment (pixel).
	// fragColor.rgb = finalColor.rgb;

	// And, set the alpha component to 1.0 (completely opaque, no transparency).
	fragColor.a = 1.0;
}
