/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(0.165, -0.133, -0.193, -0.076) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec2(-0.1, -1.2))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec4(1.98, -1.596, -2.316, -0.912) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec2(-0.1, -1.2))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec4(0.693, -0.5586, -0.8106, -0.3192) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec2(-0.42, 0.48))[0]) < 0.001 ? 1 : -1] array2;
float[length(vec4(-0.792, 0.6384, 0.9264, 0.3648) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec2(-0.42, 0.48))[1]) < 0.001 ? 1 : -1] array3;
float[length(vec4(-0.08, 0.015, 0.051, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec2(-0.1, -1.2))[0]) < 0.001 ? 1 : -1] array4;
float[length(vec4(-0.96, 0.18, 0.612, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec2(-0.1, -1.2))[1]) < 0.001 ? 1 : -1] array5;
float[length(vec4(-0.336, 0.063, 0.2142, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec2(-0.42, 0.48))[0]) < 0.001 ? 1 : -1] array6;
float[length(vec4(0.384, -0.072, -0.2448, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec2(-0.42, 0.48))[1]) < 0.001 ? 1 : -1] array7;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length()
                      + array4.length()
                      + array5.length()
                      + array6.length()
                      + array7.length());
}
