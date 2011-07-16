/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(8.7939 - dot(vec4(-1.65, 1.33, 1.93, 0.76), vec4(-1.65, 1.33, 1.93, 0.76))) < 0.001 ? 1 : -1] array0;
float[length(-2.5038 - dot(vec4(-1.65, 1.33, 1.93, 0.76), vec4(0.8, -0.15, -0.51, 0.0))) < 0.001 ? 1 : -1] array1;
float[length(-2.5038 - dot(vec4(0.8, -0.15, -0.51, 0.0), vec4(-1.65, 1.33, 1.93, 0.76))) < 0.001 ? 1 : -1] array2;
float[length(0.9226 - dot(vec4(0.8, -0.15, -0.51, 0.0), vec4(0.8, -0.15, -0.51, 0.0))) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
