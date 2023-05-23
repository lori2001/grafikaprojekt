#version 330 core

// pipeline-ból bejövő per-fragment attribútumok
in vec3 vs_out_pos;
in vec3 vs_out_norm;
in vec2 vs_out_tex;

// kimenő érték - a fragment színe
out vec4 fs_out_col;

// irány fényforrás: fény iránya
uniform vec3 light_dir = vec3(-1,-1,-1);

// fénytulajdonságok: ambiens, diffúz, spekuláris
uniform vec3 La = vec3(0.4, 0.4, 0.4);
uniform vec3 Ld = vec3(0.4, 0.6, 0.6);
uniform vec3 Ls = vec3(0.9, 0.9, 0.9);

// anyagtulajdonságok: ambiens, diffúz, spekuláris
uniform vec3 Ka = vec3(0.2, 0.4, 0.6);
uniform vec3 Kd = vec3(0.2, 0.4, 0.6);
uniform vec3 Ks = vec3(0.4, 0.8, 1.0);

uniform vec3 eye = vec3(1, 1, 1);

uniform sampler2D texImage;

void main()
{	
	//
	// ambiens szín számítása
	//
	// ez ejjel legyen kekes, nappal feher, este voroses
	vec3 ambient = La * Ka;

	//
	// diffúz szín számítása
	//	
	/* segítség:
	    - normalizálás: http://www.opengl.org/sdk/docs/manglsl/xhtml/normalize.xml
	    - skaláris szorzat: http://www.opengl.org/sdk/docs/manglsl/xhtml/dot.xml
	    - clamp: http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml
	*/

	vec3 to_light = normalize(-light_dir);
	float di = clamp(dot(to_light, vs_out_norm), 0.0, 1.0);
	vec3 diffuse = di * Ld * Ld;

	//
	// fényfoltképző szín
	//
	/* segítség:
		- reflect: http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml
				reflect(beérkező_vektor, normálvektor);
		- pow: http://www.opengl.org/sdk/docs/manglsl/xhtml/pow.xml
				pow(alap, kitevő);
	*/
	
	vec3 e = normalize(eye - vs_out_pos);
	vec3 r = normalize(reflect(light_dir, vs_out_norm));
	float si = pow(clamp(dot(e, r), 0.0, 1.0), 2);
	vec3 specular = si * Ls * Ks;
	
	//
	// a fragment végső színének meghatározása
	//

	// felületi normális
	//fs_out_col = vec4(vs_out_norm, 1);
	// + specular
	//fs_out_col = vec4(ambient + diffuse + specular, 1);

	// textúrával
	vec4 textureColor = texture(texImage, vs_out_tex);
	fs_out_col = vec4(ambient + diffuse + specular, 1) * textureColor;
}
