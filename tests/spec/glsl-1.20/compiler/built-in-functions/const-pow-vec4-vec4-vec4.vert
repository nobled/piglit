/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(0.0, 0.0, 2.25, 1.3103706971) - pow(vec4(0.0, 0.0, 0.666666666667, 0.666666666667), vec4(0.666666666667, 2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array0;
float[length(vec4(0.763142828369, 0.444444444444, 0.5625, 0.825481812224) - pow(vec4(0.666666666667, 0.666666666667, 1.33333333333, 1.33333333333), vec4(0.666666666667, 2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array1;
float[length(vec4(1.21141372855, 1.77777777778, 0.25, 0.629960524947) - pow(vec4(1.33333333333, 1.33333333333, 2.0, 2.0), vec4(0.666666666667, 2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array2;
float[length(vec4(1.58740105197, 4.0, 0.0, 0.0) - pow(vec4(2.0, 2.0, 0.0, 0.0), vec4(0.666666666667, 2.0, 0.666666666667, 2.0))) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
