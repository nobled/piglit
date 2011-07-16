/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(1.6, 0.76) - transpose(mat2(1.6, 1.53, 0.76, -1.0))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec2(1.53, -1.0) - transpose(mat2(1.6, 1.53, 0.76, -1.0))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec2(-0.13, -0.87) - transpose(mat2(-0.13, -1.4, -0.87, 1.4))[0]) < 0.001 ? 1 : -1] array2;
float[length(vec2(-1.4, 1.4) - transpose(mat2(-0.13, -1.4, -0.87, 1.4))[1]) < 0.001 ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
