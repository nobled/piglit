/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(1.2321, 0.0169, 0.3136) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec3(2.7889, 1.1881, 0.9025) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec3(0.1681, 0.0004, 0.0576) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec3(1.8759, -0.1417, -0.8568) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[0]) < 0.001 ? 1 : -1] array3;
float[length(vec3(-0.7682, 1.9075, -0.665) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[1]) < 0.001 ? 1 : -1] array4;
float[length(vec3(0.0738, -0.04, -0.3528) - matrixCompMult(mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[2]) < 0.001 ? 1 : -1] array5;
float[length(vec3(1.8759, -0.1417, -0.8568) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[0]) < 0.001 ? 1 : -1] array6;
float[length(vec3(-0.7682, 1.9075, -0.665) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[1]) < 0.001 ? 1 : -1] array7;
float[length(vec3(0.0738, -0.04, -0.3528) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.11, 0.13, 0.56, 1.67, 1.09, 0.95, -0.41, -0.02, 0.24))[2]) < 0.001 ? 1 : -1] array8;
float[length(vec3(2.8561, 1.1881, 2.3409) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[0]) < 0.001 ? 1 : -1] array9;
float[length(vec3(0.2116, 3.0625, 0.49) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[1]) < 0.001 ? 1 : -1] array10;
float[length(vec3(0.0324, 4.0, 2.1609) - matrixCompMult(mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47), mat3(-1.69, -1.09, -1.53, -0.46, 1.75, -0.7, -0.18, 2.0, -1.47))[2]) < 0.001 ? 1 : -1] array11;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length()
                      + array4.length()
                      + array5.length()
                      + array6.length()
                      + array7.length()
                      + array8.length()
                      + array9.length()
                      + array10.length()
                      + array11.length());
}
