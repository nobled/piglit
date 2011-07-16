/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(0.003, 0.036) - outerProduct(vec2(-0.1, -1.2), vec3(-0.03, -0.85, -0.94))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.085, 1.02) - outerProduct(vec2(-0.1, -1.2), vec3(-0.03, -0.85, -0.94))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec2(0.094, 1.128) - outerProduct(vec2(-0.1, -1.2), vec3(-0.03, -0.85, -0.94))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec2(-0.167, -2.004) - outerProduct(vec2(-0.1, -1.2), vec3(1.67, 0.66, 1.87))[0]) < 0.001 ? 1 : -1] array3;
float[length(vec2(-0.066, -0.792) - outerProduct(vec2(-0.1, -1.2), vec3(1.67, 0.66, 1.87))[1]) < 0.001 ? 1 : -1] array4;
float[length(vec2(-0.187, -2.244) - outerProduct(vec2(-0.1, -1.2), vec3(1.67, 0.66, 1.87))[2]) < 0.001 ? 1 : -1] array5;
float[length(vec2(0.0126, -0.0144) - outerProduct(vec2(-0.42, 0.48), vec3(-0.03, -0.85, -0.94))[0]) < 0.001 ? 1 : -1] array6;
float[length(vec2(0.357, -0.408) - outerProduct(vec2(-0.42, 0.48), vec3(-0.03, -0.85, -0.94))[1]) < 0.001 ? 1 : -1] array7;
float[length(vec2(0.3948, -0.4512) - outerProduct(vec2(-0.42, 0.48), vec3(-0.03, -0.85, -0.94))[2]) < 0.001 ? 1 : -1] array8;
float[length(vec2(-0.7014, 0.8016) - outerProduct(vec2(-0.42, 0.48), vec3(1.67, 0.66, 1.87))[0]) < 0.001 ? 1 : -1] array9;
float[length(vec2(-0.2772, 0.3168) - outerProduct(vec2(-0.42, 0.48), vec3(1.67, 0.66, 1.87))[1]) < 0.001 ? 1 : -1] array10;
float[length(vec2(-0.7854, 0.8976) - outerProduct(vec2(-0.42, 0.48), vec3(1.67, 0.66, 1.87))[2]) < 0.001 ? 1 : -1] array11;

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
