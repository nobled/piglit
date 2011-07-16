/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-0.1, -1.2)) < 1.20515945788 ? 1 : -1] array0;
float[1.20315945788 < length(vec2(-0.1, -1.2)) ? 1 : -1] array1;
float[length(vec2(-0.42, 0.48)) < 0.638808748764 ? 1 : -1] array2;
float[0.636808748764 < length(vec2(-0.42, 0.48)) ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length());
}
