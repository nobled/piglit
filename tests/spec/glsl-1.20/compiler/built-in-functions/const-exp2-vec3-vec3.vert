/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.25, 0.629960524947, 1.58740105197) - exp2(vec3(-2.0, -0.666666666667, 0.666666666667))) < 0.001 ? 1 : -1] array0;
float[length(vec3(4.0, 0.25, 0.629960524947) - exp2(vec3(2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			    + array1.length());
}