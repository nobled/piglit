/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-0.0830454798537, -0.996545758245) - normalize(vec2(-0.1, -1.2))) < 0.001 ? 1 : -1] array0;
float[length(vec2(-0.658504607869, 0.752576694707) - normalize(vec2(-0.42, 0.48))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
			    + array1.length());
}