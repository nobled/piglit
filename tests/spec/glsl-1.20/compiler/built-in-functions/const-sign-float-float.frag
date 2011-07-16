/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(-1.0 - sign(-1.5)) < 0.001 ? 1 : -1] array0;
float[length(-1.0 - sign(-0.75)) < 0.001 ? 1 : -1] array1;
float[length(0.0 - sign(0.0)) < 0.001 ? 1 : -1] array2;
float[length(1.0 - sign(0.75)) < 0.001 ? 1 : -1] array3;
float[length(1.0 - sign(1.5)) < 0.001 ? 1 : -1] array4;

main()
{
  gl_FragColor = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length()
			+ array4.length());
}
