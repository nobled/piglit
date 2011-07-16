/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec2(0.0830454798537, 0.996545758245) - refract(vec2(-0.0830454798537, -0.996545758245), vec2(-0.0830454798537, -0.996545758245), 0.5)) < 0.001 ? 1 : -1] array0;
float[length(vec2(0.0830454798537, 0.996545758245) - refract(vec2(-0.0830454798537, -0.996545758245), vec2(-0.0830454798537, -0.996545758245), 2.0)) < 0.001 ? 1 : -1] array1;
float[length(vec2(0.344065828392, -0.938945528629) - refract(vec2(-0.0830454798537, -0.996545758245), vec2(-0.658504607869, 0.752576694707), 0.5)) < 0.001 ? 1 : -1] array2;
float[length(vec2(-0, -0) - refract(vec2(-0.0830454798537, -0.996545758245), vec2(-0.658504607869, 0.752576694707), 2.0)) < 0.001 ? 1 : -1] array3;
float[length(vec2(-0.280624872479, 0.959817524817) - refract(vec2(-0.658504607869, 0.752576694707), vec2(-0.0830454798537, -0.996545758245), 0.5)) < 0.001 ? 1 : -1] array4;
float[length(vec2(-0, 0.0) - refract(vec2(-0.658504607869, 0.752576694707), vec2(-0.0830454798537, -0.996545758245), 2.0)) < 0.001 ? 1 : -1] array5;
float[length(vec2(0.658504607869, -0.752576694707) - refract(vec2(-0.658504607869, 0.752576694707), vec2(-0.658504607869, 0.752576694707), 0.5)) < 0.001 ? 1 : -1] array6;
float[length(vec2(0.658504607869, -0.752576694707) - refract(vec2(-0.658504607869, 0.752576694707), vec2(-0.658504607869, 0.752576694707), 2.0)) < 0.001 ? 1 : -1] array7;

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
