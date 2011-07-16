/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(-0.27, -1.38, -1.41, -0.12) - transpose(mat4x3(-0.27, -0.17, -1.85, -1.38, -0.56, -1.29, -1.41, 1.47, 1.77, -0.12, 1.86, 0.01))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec4(-0.17, -0.56, 1.47, 1.86) - transpose(mat4x3(-0.27, -0.17, -1.85, -1.38, -0.56, -1.29, -1.41, 1.47, 1.77, -0.12, 1.86, 0.01))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec4(-1.85, -1.29, 1.77, 0.01) - transpose(mat4x3(-0.27, -0.17, -1.85, -1.38, -0.56, -1.29, -1.41, 1.47, 1.77, -0.12, 1.86, 0.01))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec4(-0.47, -0.15, 1.97, -1.05) - transpose(mat4x3(-0.47, -0.2, -1.39, -0.15, 0.53, -0.19, 1.97, -1.82, 1.62, -1.05, -1.41, 1.58))[0]) < 0.001 ? 1 : -1] array3;
float[length(vec4(-0.2, 0.53, -1.82, -1.41) - transpose(mat4x3(-0.47, -0.2, -1.39, -0.15, 0.53, -0.19, 1.97, -1.82, 1.62, -1.05, -1.41, 1.58))[1]) < 0.001 ? 1 : -1] array4;
float[length(vec4(-1.39, -0.19, 1.62, 1.58) - transpose(mat4x3(-0.47, -0.2, -1.39, -0.15, 0.53, -0.19, 1.97, -1.82, 1.62, -1.05, -1.41, 1.58))[2]) < 0.001 ? 1 : -1] array5;

main()
{
  gl_FragColor = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length()
			+ array4.length()
			+ array5.length());
}
