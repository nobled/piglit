/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(-1.0, 0.5) - cos(vec2(-3.14159265359, -1.0471975512))) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.5, -1.0) - cos(vec2(1.0471975512, 3.14159265359))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_FragColor = vec4(array0.length()
                      + array1.length());
}
