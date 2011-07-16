/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(3.14159265359, 1.91063323625, 1.23095941734) - acos(vec3(-1.0, -0.333333333333, 0.333333333333))) < 0.001 ? 1 : -1] array0;
float[length(vec3(0.0, 3.14159265359, 1.91063323625) - acos(vec3(1.0, -1.0, -0.333333333333))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length());
}
