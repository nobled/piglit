/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-2.0, -1.0) - floor(vec2(-2.0, -0.666666666667))) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.0, 2.0) - floor(vec2(0.666666666667, 2.0))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length());
}
