/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(-1.22464679915e-16, -0.866025403784, 0.866025403784) - sin(vec3(-3.14159265359, -1.0471975512, 1.0471975512))) < 0.001 ? 1 : -1] array0;
float[length(vec3(1.22464679915e-16, -1.22464679915e-16, -0.866025403784) - sin(vec3(3.14159265359, -3.14159265359, -1.0471975512))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			    + array1.length());
}