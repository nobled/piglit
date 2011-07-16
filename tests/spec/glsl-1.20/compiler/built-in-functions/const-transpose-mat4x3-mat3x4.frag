/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(1.42, -0.86, 0.27) - transpose(mat3x4(1.42, 1.8, -1.88, 1.37, -0.86, -1.74, -0.37, 1.9, 0.27, 0.04, 0.43, 0.71))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec3(1.8, -1.74, 0.04) - transpose(mat3x4(1.42, 1.8, -1.88, 1.37, -0.86, -1.74, -0.37, 1.9, 0.27, 0.04, 0.43, 0.71))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec3(-1.88, -0.37, 0.43) - transpose(mat3x4(1.42, 1.8, -1.88, 1.37, -0.86, -1.74, -0.37, 1.9, 0.27, 0.04, 0.43, 0.71))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec3(1.37, 1.9, 0.71) - transpose(mat3x4(1.42, 1.8, -1.88, 1.37, -0.86, -1.74, -0.37, 1.9, 0.27, 0.04, 0.43, 0.71))[3]) < 0.001 ? 1 : -1] array3;
float[length(vec3(-1.72, 0.09, 0.45) - transpose(mat3x4(-1.72, -0.31, 0.14, 0.4, 0.09, -1.58, 0.18, -0.77, 0.45, 1.92, -0.56, 1.76))[0]) < 0.001 ? 1 : -1] array4;
float[length(vec3(-0.31, -1.58, 1.92) - transpose(mat3x4(-1.72, -0.31, 0.14, 0.4, 0.09, -1.58, 0.18, -0.77, 0.45, 1.92, -0.56, 1.76))[1]) < 0.001 ? 1 : -1] array5;
float[length(vec3(0.14, 0.18, -0.56) - transpose(mat3x4(-1.72, -0.31, 0.14, 0.4, 0.09, -1.58, 0.18, -0.77, 0.45, 1.92, -0.56, 1.76))[2]) < 0.001 ? 1 : -1] array6;
float[length(vec3(0.4, -0.77, 1.76) - transpose(mat3x4(-1.72, -0.31, 0.14, 0.4, 0.09, -1.58, 0.18, -0.77, 0.45, 1.92, -0.56, 1.76))[3]) < 0.001 ? 1 : -1] array7;

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
