/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(2.56, 2.3409) - matrixCompMult(mat2(1.6, 1.53, 0.76, -1.0), mat2(1.6, 1.53, 0.76, -1.0))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.5776, 1.0) - matrixCompMult(mat2(1.6, 1.53, 0.76, -1.0), mat2(1.6, 1.53, 0.76, -1.0))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec2(-0.208, -2.142) - matrixCompMult(mat2(1.6, 1.53, 0.76, -1.0), mat2(-0.13, -1.4, -0.87, 1.4))[0]) < 0.001 ? 1 : -1] array2;
float[length(vec2(-0.6612, -1.4) - matrixCompMult(mat2(1.6, 1.53, 0.76, -1.0), mat2(-0.13, -1.4, -0.87, 1.4))[1]) < 0.001 ? 1 : -1] array3;
float[length(vec2(-0.208, -2.142) - matrixCompMult(mat2(-0.13, -1.4, -0.87, 1.4), mat2(1.6, 1.53, 0.76, -1.0))[0]) < 0.001 ? 1 : -1] array4;
float[length(vec2(-0.6612, -1.4) - matrixCompMult(mat2(-0.13, -1.4, -0.87, 1.4), mat2(1.6, 1.53, 0.76, -1.0))[1]) < 0.001 ? 1 : -1] array5;
float[length(vec2(0.0169, 1.96) - matrixCompMult(mat2(-0.13, -1.4, -0.87, 1.4), mat2(-0.13, -1.4, -0.87, 1.4))[0]) < 0.001 ? 1 : -1] array6;
float[length(vec2(0.7569, 1.96) - matrixCompMult(mat2(-0.13, -1.4, -0.87, 1.4), mat2(-0.13, -1.4, -0.87, 1.4))[1]) < 0.001 ? 1 : -1] array7;

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
