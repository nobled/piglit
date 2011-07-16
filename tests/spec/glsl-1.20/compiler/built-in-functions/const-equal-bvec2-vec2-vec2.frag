/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[equal(vec2(-1.5, -1.5), vec2(-1.5, -0.5))[0] ? 1 : -1] array0;
float[equal(vec2(-1.5, -1.5), vec2(-1.5, -0.5))[1] ? -1 : 1] array1;
float[equal(vec2(-1.5, -1.5), vec2(0.5, 1.5))[0] ? -1 : 1] array2;
float[equal(vec2(-1.5, -1.5), vec2(0.5, 1.5))[1] ? -1 : 1] array3;
float[equal(vec2(-0.5, -0.5), vec2(-1.5, -0.5))[0] ? -1 : 1] array4;
float[equal(vec2(-0.5, -0.5), vec2(-1.5, -0.5))[1] ? 1 : -1] array5;
float[equal(vec2(-0.5, -0.5), vec2(0.5, 1.5))[0] ? -1 : 1] array6;
float[equal(vec2(-0.5, -0.5), vec2(0.5, 1.5))[1] ? -1 : 1] array7;
float[equal(vec2(0.5, 0.5), vec2(-1.5, -0.5))[0] ? -1 : 1] array8;
float[equal(vec2(0.5, 0.5), vec2(-1.5, -0.5))[1] ? -1 : 1] array9;
float[equal(vec2(0.5, 0.5), vec2(0.5, 1.5))[0] ? 1 : -1] array10;
float[equal(vec2(0.5, 0.5), vec2(0.5, 1.5))[1] ? -1 : 1] array11;
float[equal(vec2(1.5, 1.5), vec2(-1.5, -0.5))[0] ? -1 : 1] array12;
float[equal(vec2(1.5, 1.5), vec2(-1.5, -0.5))[1] ? -1 : 1] array13;
float[equal(vec2(1.5, 1.5), vec2(0.5, 1.5))[0] ? -1 : 1] array14;
float[equal(vec2(1.5, 1.5), vec2(0.5, 1.5))[1] ? 1 : -1] array15;

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
			+ array11.length()
			+ array12.length()
			+ array13.length()
			+ array14.length()
			+ array15.length());
}
