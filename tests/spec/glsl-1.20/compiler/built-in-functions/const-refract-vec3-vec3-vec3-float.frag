/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.02366537095, 0.670518843584, 0.741514956434) - refract(vec3(-0.02366537095, -0.670518843584, -0.741514956434), vec3(-0.02366537095, -0.670518843584, -0.741514956434), 0.5)) < 0.001 ? 1 : -1] array0;
float[length(vec3(0.02366537095, 0.670518843584, 0.741514956434) - refract(vec3(-0.02366537095, -0.670518843584, -0.741514956434), vec3(-0.02366537095, -0.670518843584, -0.741514956434), 2.0)) < 0.001 ? 1 : -1] array1;
float[length(vec3(-0.383910464938, -0.482308125053, -0.787395470789) - refract(vec3(-0.02366537095, -0.670518843584, -0.741514956434), vec3(0.644149390691, 0.254574010692, 0.721293030295), 0.5)) < 0.001 ? 1 : -1] array2;
float[length(vec3(-0, -0, -0) - refract(vec3(-0.02366537095, -0.670518843584, -0.741514956434), vec3(0.644149390691, 0.254574010692, 0.721293030295), 2.0)) < 0.001 ? 1 : -1] array3;
float[length(vec3(0.335744441526, 0.514596480468, 0.788965228812) - refract(vec3(0.644149390691, 0.254574010692, 0.721293030295), vec3(-0.02366537095, -0.670518843584, -0.741514956434), 0.5)) < 0.001 ? 1 : -1] array4;
float[length(vec3(0.0, 0.0, 0.0) - refract(vec3(0.644149390691, 0.254574010692, 0.721293030295), vec3(-0.02366537095, -0.670518843584, -0.741514956434), 2.0)) < 0.001 ? 1 : -1] array5;
float[length(vec3(-0.644149390691, -0.254574010692, -0.721293030295) - refract(vec3(0.644149390691, 0.254574010692, 0.721293030295), vec3(0.644149390691, 0.254574010692, 0.721293030295), 0.5)) < 0.001 ? 1 : -1] array6;
float[length(vec3(-0.644149390691, -0.254574010692, -0.721293030295) - refract(vec3(0.644149390691, 0.254574010692, 0.721293030295), vec3(0.644149390691, 0.254574010692, 0.721293030295), 2.0)) < 0.001 ? 1 : -1] array7;

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