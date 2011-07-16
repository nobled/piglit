/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(-4.60517018599 - log(0.01)) < 0.001 ? 1 : -1] array0;
float[length(-0.395514777255 - log(0.673333333333)) < 0.001 ? 1 : -1] array1;
float[length(0.29017895265 - log(1.33666666667)) < 0.001 ? 1 : -1] array2;
float[length(0.69314718056 - log(2.0)) < 0.001 ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length());
}
