/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(-6.64385618977 - log2(0.01)) < 0.001 ? 1 : -1] array0;
float[length(-0.570607207744 - log2(0.673333333333)) < 0.001 ? 1 : -1] array1;
float[length(0.418639735959 - log2(1.33666666667)) < 0.001 ? 1 : -1] array2;
float[length(1.0 - log2(2.0)) < 0.001 ? 1 : -1] array3;

main()
{
  gl_FragColor = vec4(array0.length()
			    + array1.length()
			    + array2.length()
			    + array3.length());
}