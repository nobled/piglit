/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(1.0, 1.0, 1.0) - step(vec3(-2.0, -2.0, -2.0), vec3(-2.0, -0.666666666667, 0.666666666667))) < 0.001 ? 1 : -1] array0;
float[length(vec3(1.0, 0.0, 1.0) - step(vec3(-2.0, -0.666666666667, -0.666666666667), vec3(2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array1;
float[length(vec3(1.0, 1.0, 0.0) - step(vec3(-0.666666666667, -0.666666666667, 0.666666666667), vec3(0.666666666667, 2.0, -2.0))) < 0.001 ? 1 : -1] array2;
float[length(vec3(0.0, 1.0, 1.0) - step(vec3(0.666666666667, 0.666666666667, 0.666666666667), vec3(-0.666666666667, 0.666666666667, 2.0))) < 0.001 ? 1 : -1] array3;
float[length(vec3(0.0, 0.0, 0.0) - step(vec3(2.0, 2.0, 2.0), vec3(-2.0, -0.666666666667, 0.666666666667))) < 0.001 ? 1 : -1] array4;
float[length(vec3(1.0, 1.0, 1.0) - step(vec3(2.0, -2.0, -2.0), vec3(2.0, -2.0, -0.666666666667))) < 0.001 ? 1 : -1] array5;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length()
                      + array2.length()
                      + array3.length()
                      + array4.length()
                      + array5.length());
}
