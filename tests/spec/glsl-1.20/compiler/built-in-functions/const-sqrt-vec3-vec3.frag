/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.0, 0.816496580928, 1.15470053838) - sqrt(vec3(0.0, 0.666666666667, 1.33333333333))) < 0.001 ? 1 : -1] array0;
float[length(vec3(1.41421356237, 0.0, 0.816496580928) - sqrt(vec3(2.0, 0.0, 0.666666666667))) < 0.001 ? 1 : -1] array1;

main()
{
  gl_FragColor = vec4(array0.length()
			+ array1.length());
}
