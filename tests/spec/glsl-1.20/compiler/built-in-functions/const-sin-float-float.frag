/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(-1.22464679915e-16 - sin(-3.14159265359)) < 0.001 ? 1 : -1] array0;
float[length(-0.866025403784 - sin(-1.0471975512)) < 0.001 ? 1 : -1] array1;
float[length(0.866025403784 - sin(1.0471975512)) < 0.001 ? 1 : -1] array2;
float[length(1.22464679915e-16 - sin(3.14159265359)) < 0.001 ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
