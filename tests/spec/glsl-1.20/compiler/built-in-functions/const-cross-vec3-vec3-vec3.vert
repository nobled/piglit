/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.0, 0.0, 0.0) - cross(vec3(-0.03, -0.85, -0.94), vec3(-0.03, -0.85, -0.94))) < 0.001 ? 1 : -1] array0;
float[length(vec3(-0.9691, -1.5137, 1.3997) - cross(vec3(-0.03, -0.85, -0.94), vec3(1.67, 0.66, 1.87))) < 0.001 ? 1 : -1] array1;
float[length(vec3(0.9691, 1.5137, -1.3997) - cross(vec3(1.67, 0.66, 1.87), vec3(-0.03, -0.85, -0.94))) < 0.001 ? 1 : -1] array2;
float[length(vec3(0.0, 0.0, 0.0) - cross(vec3(1.67, 0.66, 1.87), vec3(1.67, 0.66, 1.87))) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
			    + array1.length()
			    + array2.length()
			    + array3.length());
}