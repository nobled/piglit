/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(0.1, 1.2) - reflect(vec2(-0.1, -1.2), vec2(-0.0830454798537, -0.996545758245))) < 0.001 ? 1 : -1] array0;
float[length(vec2(-1.20265486726, 0.0601769911504) - reflect(vec2(-0.1, -1.2), vec2(-0.658504607869, 0.752576694707))) < 0.001 ? 1 : -1] array1;
float[length(vec2(-0.493655172414, -0.403862068966) - reflect(vec2(-0.42, 0.48), vec2(-0.0830454798537, -0.996545758245))) < 0.001 ? 1 : -1] array2;
float[length(vec2(0.42, -0.48) - reflect(vec2(-0.42, 0.48), vec2(-0.658504607869, 0.752576694707))) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
