/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-4.60517018599, -0.395514777255) - log(vec2(0.01, 0.673333333333))) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.29017895265, 0.69314718056) - log(vec2(1.33666666667, 2.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length());
}
