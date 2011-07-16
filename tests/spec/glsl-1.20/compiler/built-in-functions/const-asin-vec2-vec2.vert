/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-1.57079632679, -0.339836909454) - asin(vec2(-1.0, -0.333333333333))) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.339836909454, 1.57079632679) - asin(vec2(0.333333333333, 1.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length());
}
