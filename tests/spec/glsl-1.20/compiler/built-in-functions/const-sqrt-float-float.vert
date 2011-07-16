/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(0.0 - sqrt(0.0)) < 0.001 ? 1 : -1] array0;
float[length(0.816496580928 - sqrt(0.666666666667)) < 0.001 ? 1 : -1] array1;
float[length(1.15470053838 - sqrt(1.33333333333)) < 0.001 ? 1 : -1] array2;
float[length(1.41421356237 - sqrt(2.0)) < 0.001 ? 1 : -1] array3;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
