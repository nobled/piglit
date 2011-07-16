/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.09, 1.3, 1.25) - transpose(mat3x2(0.09, -1.19, 1.3, 0.08, 1.25, 1.08))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec3(-1.19, 0.08, 1.08) - transpose(mat3x2(0.09, -1.19, 1.3, 0.08, 1.25, 1.08))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec3(-0.36, -1.08, -0.6) - transpose(mat3x2(-0.36, -0.53, -1.08, 0.88, -0.6, -1.79))[0]) < 0.001 ? 1 : -1] array2;
float[length(vec3(-0.53, 0.88, -1.79) - transpose(mat3x2(-0.36, -0.53, -1.08, 0.88, -0.6, -1.79))[1]) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
