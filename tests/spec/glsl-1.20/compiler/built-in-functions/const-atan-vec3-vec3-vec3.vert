/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(-2.35619449019, -1.57079632679, -0.785398163397) - atan(vec3(-2.0, -2.0, -2.0), vec3(-2.0, 0.0, 2.0))) < 0.001 ? 1 : -1] array0;
float[length(vec3(3.14159265359, 0.0, 2.35619449019) - atan(vec3(0.0, 0.0, 2.0), vec3(-2.0, 2.0, -2.0))) < 0.001 ? 1 : -1] array1;
float[length(vec3(1.57079632679, 0.785398163397, -2.35619449019) - atan(vec3(2.0, 2.0, -2.0), vec3(0.0, 2.0, -2.0))) < 0.001 ? 1 : -1] array2;

main()
{
  gl_Position  = vec4(array0.length()
                      + array1.length()
                      + array2.length());
}
